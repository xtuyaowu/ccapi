#ifndef INCLUDE_CCAPI_CPP_SERVICE_CCAPI_MARKET_DATA_SERVICE_INDODAX_H_
#define INCLUDE_CCAPI_CPP_SERVICE_CCAPI_MARKET_DATA_SERVICE_INDODAX_H_
#ifdef CCAPI_ENABLE_SERVICE_MARKET_DATA
#ifdef CCAPI_ENABLE_EXCHANGE_INDODAX
#include <chrono>
#include <thread>
#include "ccapi_cpp/service/ccapi_market_data_service.h"
namespace ccapi {
class MarketDataServiceIndodax : public MarketDataService {
 public:
  MarketDataServiceIndodax(std::function<void(Event&, Queue<Event>*)> eventHandler, SessionOptions sessionOptions, SessionConfigs sessionConfigs,
                          std::shared_ptr<ServiceContext> serviceContextPtr)
      : MarketDataService(eventHandler, sessionOptions, sessionConfigs, serviceContextPtr) {
    this->exchangeName = CCAPI_EXCHANGE_NAME_INDODAX;
    this->baseUrl = sessionConfigs.getUrlWebsocketBase().at(this->exchangeName);
    this->baseUrlRest = sessionConfigs.getUrlRestBase().at(this->exchangeName);
    this->setHostRestFromUrlRest(this->baseUrlRest);
    try {
      this->tcpResolverResultsRest = this->resolver.resolve(this->hostRest, this->portRest);
    } catch (const std::exception& e) {
      CCAPI_LOGGER_FATAL(std::string("e.what() = ") + e.what());
    }
    this->getRecentTradesTarget = "/api/pro/v1/trades";
    this->getInstrumentTarget = "/api/pro/v1/products";
    this->getInstrumentsTarget = "/api/pro/v1/products";
  }
  virtual ~MarketDataServiceIndodax() {}
#ifndef CCAPI_EXPOSE_INTERNAL

 private:
#endif
  bool doesHttpBodyContainError(const Request& request, const std::string& body) override { return body.find(R"("code":0)") == std::string::npos; }
  void prepareSubscriptionDetail(std::string& channelId, std::string& symbolId, const std::string& field, const WsConnection& wsConnection,
                                 const std::map<std::string, std::string> optionMap) override {
    auto marketDepthRequested = std::stoi(optionMap.at(CCAPI_MARKET_DEPTH_MAX));
  }
  void pingOnApplicationLevel(wspp::connection_hdl hdl, ErrorCode& ec) override {
    // this->send(hdl, R"({ "op": "ping" })", wspp::frame::opcode::text, ec);
  }
  std::vector<std::string> createSendStringList(const WsConnection& wsConnection) override {
    std::vector<std::string> sendStringList;
    for (const auto& subscriptionListByChannelIdSymbolId : this->subscriptionListByConnectionIdChannelIdSymbolIdMap.at(wsConnection.id)) {
      auto channelId = subscriptionListByChannelIdSymbolId.first;
      for (const auto& subscriptionListBySymbolId : subscriptionListByChannelIdSymbolId.second) {
        std::string symbolId = subscriptionListBySymbolId.first;
        std::string exchangeSubscriptionId = symbolId + "." + channelId;
        this->channelIdSymbolIdByConnectionIdExchangeSubscriptionIdMap[wsConnection.id][exchangeSubscriptionId][CCAPI_CHANNEL_ID] = channelId;
        this->channelIdSymbolIdByConnectionIdExchangeSubscriptionIdMap[wsConnection.id][exchangeSubscriptionId][CCAPI_SYMBOL_ID] = symbolId;
        rj::Document document;
        document.SetObject();
        rj::Document::AllocatorType& allocator = document.GetAllocator();
        document.AddMember("id", 1, allocator);
        document.AddMember("method", 1, allocator);
        rapidjson::Value params(rapidjson::kObjectType);
        params.AddMember("channel",rj::Value(exchangeSubscriptionId.c_str(), allocator).Move(), allocator);
        document.AddMember("params", params, allocator);
        rj::StringBuffer stringBuffer;
        rj::Writer<rj::StringBuffer> writer(stringBuffer);
        document.Accept(writer);
        std::string sendString = stringBuffer.GetString();
        sendStringList.push_back(sendString);
      }
    }
    return sendStringList;
  }

  void subscribeToExchange(const WsConnection& wsConnection) override{
    CCAPI_LOGGER_INFO("exchange is " + this->exchangeName);
    std::vector<std::string> sendStringList;
    if (this->correlationIdByConnectionIdMap.find(wsConnection.id) == this->correlationIdByConnectionIdMap.end()) {
      sendStringList = this->createSendStringList(wsConnection);
    } else {
      auto subscription = wsConnection.subscriptionList.at(0);
      sendStringList = std::vector<std::string>(1, subscription.getRawOptions());
    }
    ErrorCode ec;
    this->send(wsConnection.hdl, "{\"params\":{\"token\":\"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxIiwiaW5mbyI6eyJuYW1lIjoiUHVibGljIn19.VJAHTrrfwxceSITpuPBl75LVM5bgojKGiUTOwCZxw-k\",\"name\":\"js\"},\"id\":1}", wspp::frame::opcode::text, ec);
    if (ec) {
      this->onError(Event::Type::SUBSCRIPTION_STATUS, Message::Type::SUBSCRIPTION_FAILURE, ec, "subscribe");
    }
  }

  void _subscribeToExchange(const WsConnection& wsConnection) {
    CCAPI_LOGGER_INFO("exchange is " + this->exchangeName);
    std::vector<std::string> sendStringList;
    if (this->correlationIdByConnectionIdMap.find(wsConnection.id) == this->correlationIdByConnectionIdMap.end()) {
      sendStringList = this->createSendStringList(wsConnection);
    } else {
      auto subscription = wsConnection.subscriptionList.at(0);
      sendStringList = std::vector<std::string>(1, subscription.getRawOptions());
    }
    for (const auto& sendString : sendStringList) {
      CCAPI_LOGGER_INFO("sendString = " + sendString);
      ErrorCode ec;
      this->send(wsConnection.hdl, sendString, wspp::frame::opcode::text, ec);
      if (ec) {
        this->onError(Event::Type::SUBSCRIPTION_STATUS, Message::Type::SUBSCRIPTION_FAILURE, ec, "subscribe");
      }
    }
  }

  void processTextMessage(WsConnection& wsConnection, wspp::connection_hdl hdl, const std::string& textMessage, const TimePoint& timeReceived, Event& event,
                          std::vector<MarketDataMessage>& marketDataMessageList) override {
    rj::Document document;
    document.Parse<rj::kParseNumbersAsStringsFlag>(textMessage.c_str());

    std::string error_code = "";
    std::string error_message = "";
    if (document.HasMember("error")) {
      // "{\"id\":1,\"error\":{\"code\":101,\"message\":\"unauthorized\"}}\n"
      const rj::Value& error_object = document["error"];
      error_code = error_object["code"].GetString();;
      error_message = error_object["message"].GetString();
      CCAPI_LOGGER_FATAL("indodax error: " + error_code + " code is: "+ error_message);
    } else {
      std::string channel = "";
      std::string channelId = "";
      std::string symbolId = "";
      const rj::Value& result = document["result"];
      if (!result.ObjectEmpty()) {
        if (result.HasMember("channel")) {
          channel = result["channel"].GetString();
          auto pos = channel.find_last_of(".");
          symbolId = channel.substr(0, pos);
          channelId = channel.substr(pos + 1);
        } else if (result.HasMember("client")) { // auth response
          _subscribeToExchange(wsConnection);
        }
      }
      auto now = UtilTime::now();
      if (channelId == "depth") {
        const rj::Value& data_up = result["data"];
        const rj::Value& data = data_up["data"];
        MarketDataMessage marketDataMessage;
        marketDataMessage.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_MARKET_DEPTH;
        marketDataMessage.recapType = MarketDataMessage::RecapType::SOLICITED;
        marketDataMessage.exchangeSubscriptionId = channel;
        marketDataMessage.tp = now;
        for (const auto& x : data["bid"].GetArray()) {
          MarketDataMessage::TypeForDataPoint dataPoint;
          dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(x["price"].GetString())});
          dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(x["order"].GetString())});
          marketDataMessage.data[MarketDataMessage::DataType::BID].emplace_back(std::move(dataPoint));
        }
        for (const auto& x : data["ask"].GetArray()) {
          MarketDataMessage::TypeForDataPoint dataPoint;
          dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(x["price"].GetString())});
          dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(x["order"].GetString())});
          marketDataMessage.data[MarketDataMessage::DataType::ASK].emplace_back(std::move(dataPoint));
        }
        marketDataMessageList.emplace_back(std::move(marketDataMessage));
      } else if (channelId == "trade") {
        const rj::Value& data_up = result["data"];
        const rj::Value& data = data_up["data"];
        MarketDataMessage marketDataMessage;
        marketDataMessage.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_TRADE;
        marketDataMessage.recapType = MarketDataMessage::RecapType::NONE;
        marketDataMessage.exchangeSubscriptionId = channel;
        TimePoint ts = TimePoint(std::chrono::milliseconds(std::stoll(data["trade_time"].GetString())));
        marketDataMessage.tp = ts;
        MarketDataMessage::TypeForDataPoint dataPoint;
        dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(std::string(data["amount_base"].GetString()))});
        dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(std::string(data["amount_trade"].GetString()))});
        dataPoint.insert({MarketDataMessage::DataFieldType::TRADE_ID, std::string(data["Id"].GetString())});
        dataPoint.insert({MarketDataMessage::DataFieldType::IS_BUYER_MAKER, std::string(data["direction"].GetString()) == "1" ? "1" : "0"});
        marketDataMessage.data[MarketDataMessage::DataType::TRADE].emplace_back(std::move(dataPoint));
        marketDataMessageList.emplace_back(std::move(marketDataMessage));
      } else if (result.ObjectEmpty()) {
        event.setType(Event::Type::SUBSCRIPTION_STATUS);
        std::vector<Message> messageList;
        Message message;
        message.setTimeReceived(timeReceived);
        std::vector<std::string> correlationIdList;
        if (this->correlationIdListByConnectionIdChannelIdSymbolIdMap.find(wsConnection.id) != this->correlationIdListByConnectionIdChannelIdSymbolIdMap.end()) {
          int id = std::stoi(document["id"].GetString());
          if (this->exchangeSubscriptionIdListByExchangeJsonPayloadIdMap.find(id) != this->exchangeSubscriptionIdListByExchangeJsonPayloadIdMap.end()) {
            for (const auto& exchangeSubscriptionId : this->exchangeSubscriptionIdListByExchangeJsonPayloadIdMap.at(id)) {
              std::string channelId = this->channelIdSymbolIdByConnectionIdExchangeSubscriptionIdMap[wsConnection.id][exchangeSubscriptionId][CCAPI_CHANNEL_ID];
              std::string symbolId = this->channelIdSymbolIdByConnectionIdExchangeSubscriptionIdMap[wsConnection.id][exchangeSubscriptionId][CCAPI_SYMBOL_ID];
              if (this->correlationIdListByConnectionIdChannelIdSymbolIdMap.at(wsConnection.id).find(channelId) !=
                  this->correlationIdListByConnectionIdChannelIdSymbolIdMap.at(wsConnection.id).end()) {
                if (this->correlationIdListByConnectionIdChannelIdSymbolIdMap.at(wsConnection.id).at(channelId).find(symbolId) !=
                    this->correlationIdListByConnectionIdChannelIdSymbolIdMap.at(wsConnection.id).at(channelId).end()) {
                  std::vector<std::string> correlationIdList_2 =
                      this->correlationIdListByConnectionIdChannelIdSymbolIdMap.at(wsConnection.id).at(channelId).at(symbolId);
                  correlationIdList.insert(correlationIdList.end(), correlationIdList_2.begin(), correlationIdList_2.end());
                }
              }
            }
          }
        }
        message.setCorrelationIdList(correlationIdList);
        message.setType(Message::Type::SUBSCRIPTION_STARTED);
        Element element;
        element.insert(CCAPI_INFO_MESSAGE, textMessage);
        message.setElementList({element});
        messageList.emplace_back(std::move(message));
        event.setMessageList(messageList);
      }

// commont ping
//      if (channelId == "1000") {
//        ErrorCode ec;
//        this->send(hdl, R"({ "op": "pong" })", wspp::frame::opcode::text, ec);
//        if (ec) {
//          this->onError(Event::Type::SUBSCRIPTION_STATUS, Message::Type::GENERIC_ERROR, ec, "pong");
//        }
//      }
      
    }
  }
  void convertRequestForRest(http::request<http::string_body>& req, const Request& request, const TimePoint& now, const std::string& symbolId,
                             const std::map<std::string, std::string>& credential) override {
    switch (request.getOperation()) {
      case Request::Operation::GENERIC_PUBLIC_REQUEST: {
        MarketDataService::convertRequestForRestGenericPublicRequest(req, request, now, symbolId, credential);
      } break;
      case Request::Operation::GET_RECENT_TRADES: {
        req.method(http::verb::get);
        auto target = this->getRecentTradesTarget;
        std::string queryString;
        const std::map<std::string, std::string> param = request.getFirstParamWithDefault();
        this->appendParam(queryString, param,
                          {
                              {CCAPI_LIMIT, "n"},
                          });
        this->appendSymbolId(queryString, symbolId, "symbol");
        req.target(target + "?" + queryString);
      } break;
      case Request::Operation::GET_INSTRUMENT: {
        req.method(http::verb::get);
        auto target = this->getInstrumentTarget;
        std::string queryString;
        const std::map<std::string, std::string> param = request.getFirstParamWithDefault();
        this->appendSymbolId(queryString, symbolId, "symbol");
        req.target(target + "?" + queryString);
      } break;
      case Request::Operation::GET_INSTRUMENTS: {
        req.method(http::verb::get);
        auto target = this->getInstrumentsTarget;
        req.target(target);
      } break;
      default:
        this->convertRequestForRestCustom(req, request, now, symbolId, credential);
    }
  }
  void extractInstrumentInfo(Element& element, const rj::Value& x) {
    element.insert(CCAPI_INSTRUMENT, x["symbol"].GetString());
    element.insert(CCAPI_BASE_ASSET, x["baseAsset"].GetString());
    element.insert(CCAPI_QUOTE_ASSET, x["quoteAsset"].GetString());
    element.insert(CCAPI_ORDER_PRICE_INCREMENT, x["tickSize"].GetString());
    element.insert(CCAPI_ORDER_QUANTITY_INCREMENT, x["lotSize"].GetString());
    element.insert(CCAPI_ORDER_PRICE_TIMES_QUANTITY_MIN, x["minNotional"].GetString());
  }
  void convertTextMessageToMarketDataMessage(const Request& request, const std::string& textMessage, const TimePoint& timeReceived, Event& event,
                                             std::vector<MarketDataMessage>& marketDataMessageList) override {
    rj::Document document;
    document.Parse<rj::kParseNumbersAsStringsFlag>(textMessage.c_str());
    switch (request.getOperation()) {
      case Request::Operation::GET_RECENT_TRADES: {
        for (const auto& x : document["data"].GetArray()) {
          MarketDataMessage marketDataMessage;
          marketDataMessage.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_TRADE;
          marketDataMessage.tp = TimePoint(std::chrono::milliseconds(std::stoll(x["ts"].GetString())));
          MarketDataMessage::TypeForDataPoint dataPoint;
          dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(std::string(x["p"].GetString()))});
          dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(std::string(x["q"].GetString()))});
          dataPoint.insert({MarketDataMessage::DataFieldType::TRADE_ID, std::string(x["seqnum"].GetString())});
          dataPoint.insert({MarketDataMessage::DataFieldType::IS_BUYER_MAKER, x["bm"].GetBool() ? "1" : "0"});
          marketDataMessage.data[MarketDataMessage::DataType::TRADE].emplace_back(std::move(dataPoint));
          marketDataMessageList.emplace_back(std::move(marketDataMessage));
        }
      } break;
      case Request::Operation::GET_INSTRUMENT: {
        Message message;
        message.setTimeReceived(timeReceived);
        message.setType(this->requestOperationToMessageTypeMap.at(request.getOperation()));
        for (const auto& x : document["data"].GetArray()) {
          if (std::string(x["symbol"].GetString()) == request.getInstrument()) {
            Element element;
            this->extractInstrumentInfo(element, x);
            message.setElementList({element});
            break;
          }
        }
        message.setCorrelationIdList({request.getCorrelationId()});
        event.addMessages({message});
      } break;
      case Request::Operation::GET_INSTRUMENTS: {
        Message message;
        message.setTimeReceived(timeReceived);
        message.setType(this->requestOperationToMessageTypeMap.at(request.getOperation()));
        std::vector<Element> elementList;
        for (const auto& x : document["data"].GetArray()) {
          Element element;
          this->extractInstrumentInfo(element, x);
          elementList.emplace_back(std::move(element));
        }
        message.setElementList(elementList);
        message.setCorrelationIdList({request.getCorrelationId()});
        event.addMessages({message});
      } break;
      default:
        CCAPI_LOGGER_FATAL(CCAPI_UNSUPPORTED_VALUE);
    }
  }
};
} /* namespace ccapi */
#endif
#endif
#endif  // INCLUDE_CCAPI_CPP_SERVICE_CCAPI_MARKET_DATA_SERVICE_INDODAX_H_