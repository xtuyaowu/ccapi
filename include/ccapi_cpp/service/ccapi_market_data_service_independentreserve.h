#ifndef INCLUDE_CCAPI_CPP_SERVICE_CCAPI_MARKET_DATA_SERVICE_INDEPENDENTRESERVE_H_
#define INCLUDE_CCAPI_CPP_SERVICE_CCAPI_MARKET_DATA_SERVICE_INDEPENDENTRESERVE_H_
#ifdef CCAPI_ENABLE_SERVICE_MARKET_DATA
#ifdef CCAPI_ENABLE_EXCHANGE_INDEPENDENTRESERVE
#include "ccapi_cpp/service/ccapi_market_data_service.h"
namespace ccapi {
class MarketDataServiceIndependentreserve : public MarketDataService {
 public:
  MarketDataServiceIndependentreserve(std::function<void(Event&, Queue<Event>*)> eventHandler, SessionOptions sessionOptions, SessionConfigs sessionConfigs,
                          std::shared_ptr<ServiceContext> serviceContextPtr)
      : MarketDataService(eventHandler, sessionOptions, sessionConfigs, serviceContextPtr) {
    this->exchangeName = CCAPI_EXCHANGE_NAME_INDEPENDENTRESERVE;
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

  struct OrderBookPoint
  {
    std::string guid;
    std::string price;
    std::string volume;
  };
  std::map<std::string, OrderBookPoint> mapOfBuyOrders;
  std::map<std::string, OrderBookPoint> mapOfSellOrders;

  virtual ~MarketDataServiceIndependentreserve() {}
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
    rj::Document document;
    document.SetObject();
    rj::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("Event", rj::Value("Subscribe").Move(), allocator);
    for (const auto& subscriptionListByChannelIdSymbolId : this->subscriptionListByConnectionIdChannelIdSymbolIdMap.at(wsConnection.id)) {
      auto channelId = subscriptionListByChannelIdSymbolId.first;
      rj::Value data(rj::kArrayType);
      for (const auto& subscriptionListBySymbolId : subscriptionListByChannelIdSymbolId.second) {
        std::string symbolId = subscriptionListBySymbolId.first;
        std::string exchangeSubscriptionId = channelId + "-" + symbolId;
        this->channelIdSymbolIdByConnectionIdExchangeSubscriptionIdMap[wsConnection.id][exchangeSubscriptionId][CCAPI_CHANNEL_ID] = channelId;
        this->channelIdSymbolIdByConnectionIdExchangeSubscriptionIdMap[wsConnection.id][exchangeSubscriptionId][CCAPI_SYMBOL_ID] = symbolId;
        data.PushBack(rj::Value(exchangeSubscriptionId.c_str(), allocator).Move(), allocator);
      }
      document.AddMember("Data", data, allocator);
    }
    rj::StringBuffer stringBuffer;
    rj::Writer<rj::StringBuffer> writer(stringBuffer);
    document.Accept(writer);
    std::string sendString = stringBuffer.GetString();
    sendStringList.push_back(sendString);
    return sendStringList;
  }
  void processTextMessage(WsConnection& wsConnection, wspp::connection_hdl hdl, const std::string& textMessage, const TimePoint& timeReceived, Event& event,
                          std::vector<MarketDataMessage>& marketDataMessageList) override {
    rj::Document document;
    document.Parse<rj::kParseNumbersAsStringsFlag>(textMessage.c_str());
    std::string event_type = document["Event"].GetString();
    auto now = UtilTime::now();
      if(event_type == "NewOrder" || event_type == "OrderChanged" || event_type == "OrderCanceled") {
        std::string exchangeSubscriptionId = document["Channel"].GetString();
        auto channel_split = UtilString::split(exchangeSubscriptionId, "-");
        std::string channelId = channel_split.at(0);
        std::string symbolId = channel_split.at(1) + "-" + channel_split.at(2);

        std::map<Decimal, std::string>& snapshotBid = this->snapshotBidByConnectionIdChannelIdSymbolIdMap[wsConnection.id][channelId][symbolId];
        std::map<Decimal, std::string>& snapshotAsk = this->snapshotAskByConnectionIdChannelIdSymbolIdMap[wsConnection.id][channelId][symbolId];
        if (snapshotAsk.size() == 0 && snapshotBid.size() == 0) {
          auto const host = "api.independentreserve.com";
          auto const path = "/Public/GetAllOrders?primaryCurrencyCode=" + channel_split.at(1) + "&secondaryCurrencyCode=" + channel_split.at(2) + "";
          auto const port = "443";
          boost::asio::io_service svc;
          ssl::context ctx(ssl::context::sslv23_client);
          ssl::stream<boost::asio::ip::tcp::socket> ssocket = {svc, ctx};
          boost::asio::ip::tcp::resolver resolver(svc);
          auto it = resolver.resolve(host, port);
          boost::asio::connect(ssocket.lowest_layer(), it);
          ssocket.handshake(ssl::stream_base::handshake_type::client);
          http::request<http::string_body> req{http::verb::get, path, 11};
          req.set(http::field::host, host);
          http::write(ssocket, req);
          http::response<http::string_body> res;
          boost::beast::flat_buffer buffer;
          http::read(ssocket, buffer, res);
          // std::cout << "Headers" << std::endl;
          // std::cout << res.base() << std::endl << std::endl;
          // std::cout << "Body" << std::endl;
          // std::cout << res.body() << std::endl << std::endl;
          rj::Document orderbook_snapshot;
          orderbook_snapshot.Parse<rj::kParseNumbersAsStringsFlag>(res.body().c_str());

          MarketDataMessage marketDataMessage;
          marketDataMessage.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_MARKET_DEPTH;
          marketDataMessage.recapType = MarketDataMessage::RecapType::SOLICITED;
          marketDataMessage.exchangeSubscriptionId = exchangeSubscriptionId;
          marketDataMessage.tp = UtilTime::parse(std::string(orderbook_snapshot["CreatedTimestampUtc"].GetString()));

          for (const auto& x : orderbook_snapshot["BuyOrders"].GetArray()) {
            MarketDataMessage::TypeForDataPoint dataPoint;
            dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(x["Price"].GetString())});
            dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(x["Volume"].GetString())});
            marketDataMessage.data[MarketDataMessage::DataType::BID].emplace_back(std::move(dataPoint));

            OrderBookPoint orderBookBid;
            orderBookBid.guid = x["Guid"].GetString();
            orderBookBid.price = x["Price"].GetString();
            orderBookBid.volume = x["Volume"].GetString();
            mapOfBuyOrders.insert(std::make_pair(x["Guid"].GetString(), orderBookBid));
          }
          for (const auto& x : orderbook_snapshot["SellOrders"].GetArray()) {
            MarketDataMessage::TypeForDataPoint dataPoint;
            dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(x["Price"].GetString())});
            dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(x["Volume"].GetString())});
            marketDataMessage.data[MarketDataMessage::DataType::ASK].emplace_back(std::move(dataPoint));

            OrderBookPoint orderBookAsk;
            orderBookAsk.guid = x["Guid"].GetString();
            orderBookAsk.price = x["Price"].GetString();
            orderBookAsk.volume = x["Volume"].GetString();
            mapOfSellOrders.insert(std::make_pair(x["Guid"].GetString(), orderBookAsk));
          }
          marketDataMessageList.emplace_back(std::move(marketDataMessage));
        } else {
          if (event_type == "NewOrder") {
              const rj::Value& data = document["Data"];
              std::string orderType = data["OrderType"].GetString();
              MarketDataMessage marketDataMessage;
              marketDataMessage.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_MARKET_DEPTH;
              marketDataMessage.recapType = MarketDataMessage::RecapType::NONE;
              marketDataMessage.exchangeSubscriptionId = exchangeSubscriptionId;
              marketDataMessage.tp = now;
              if (orderType == "LimitBid") {
                MarketDataMessage::TypeForDataPoint dataPoint;
                dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(data["Price"].GetString())});
                dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(data["Volume"].GetString())});
                marketDataMessage.data[MarketDataMessage::DataType::BID].emplace_back(std::move(dataPoint));

                OrderBookPoint orderBookBid;
                orderBookBid.guid = data["OrderGuid"].GetString();
                orderBookBid.price = data["Price"].GetString();
                orderBookBid.volume = data["Volume"].GetString();
                mapOfBuyOrders.insert(std::make_pair(data["OrderGuid"].GetString(), orderBookBid));
              } else if (orderType == "LimitOffer") {
                MarketDataMessage::TypeForDataPoint dataPoint;
                dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(data["Price"].GetString())});
                dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(data["Volume"].GetString())});
                marketDataMessage.data[MarketDataMessage::DataType::ASK].emplace_back(std::move(dataPoint));

                OrderBookPoint orderBookAsk;
                orderBookAsk.guid = data["OrderGuid"].GetString();
                orderBookAsk.price = data["Price"].GetString();
                orderBookAsk.volume = data["Volume"].GetString();
                mapOfSellOrders.insert(std::make_pair(data["OrderGuid"].GetString(), orderBookAsk));
              }
              marketDataMessageList.emplace_back(std::move(marketDataMessage));
            } else if (event_type == "OrderChanged") {
              const rj::Value& data = document["Data"];
              std::string orderType = data["OrderType"].GetString();
              MarketDataMessage marketDataMessage;
              marketDataMessage.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_MARKET_DEPTH;
              marketDataMessage.recapType = MarketDataMessage::RecapType::NONE;
              marketDataMessage.exchangeSubscriptionId = exchangeSubscriptionId;
              marketDataMessage.tp = now;
              if (orderType == "LimitBid") {
                MarketDataMessage::TypeForDataPoint dataPoint;
                dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(data["Price"].GetString())});
                dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(data["Volume"].GetString())});
                marketDataMessage.data[MarketDataMessage::DataType::BID].emplace_back(std::move(dataPoint));

                if(data["Price"].GetString() == "0"){
                  mapOfBuyOrders.erase(data["OrderGuid"].GetString());
                } else {
                  OrderBookPoint orderBookBid;
                  orderBookBid.guid = data["OrderGuid"].GetString();
                  orderBookBid.price = data["Price"].GetString();
                  orderBookBid.volume = data["Volume"].GetString();
                  mapOfBuyOrders.insert(std::make_pair(data["OrderGuid"].GetString(), orderBookBid));
                }
              } else if (orderType == "LimitOffer") {
                MarketDataMessage::TypeForDataPoint dataPoint;
                dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(data["Price"].GetString())});
                dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(data["Volume"].GetString())});
                marketDataMessage.data[MarketDataMessage::DataType::ASK].emplace_back(std::move(dataPoint));

                if(data["Price"].GetString() == "0"){
                  mapOfSellOrders.erase(data["OrderGuid"].GetString());
                } else {
                  OrderBookPoint orderBookAsk;
                  orderBookAsk.guid = data["OrderGuid"].GetString();
                  orderBookAsk.price = data["Price"].GetString();
                  orderBookAsk.volume = data["Volume"].GetString();
                  mapOfSellOrders.insert(std::make_pair(data["OrderGuid"].GetString(), orderBookAsk));
                }
              }
              marketDataMessageList.emplace_back(std::move(marketDataMessage));
            } else if (event_type == "OrderCanceled") {
              const rj::Value& data = document["Data"];
              std::string orderType = data["OrderType"].GetString();
              MarketDataMessage marketDataMessage;
              marketDataMessage.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_MARKET_DEPTH;
              marketDataMessage.recapType = MarketDataMessage::RecapType::NONE;
              marketDataMessage.exchangeSubscriptionId = exchangeSubscriptionId;
              marketDataMessage.tp = now;
              if (orderType == "LimitBid") {
                std::map<std::string, OrderBookPoint>::iterator it = mapOfBuyOrders.begin();
                OrderBookPoint orderBookBid;
                while(it != mapOfBuyOrders.end())
                {
                  if(it->first == data["OrderGuid"].GetString()){
                    orderBookBid = it->second;
                    break;
                  }
                  it++;
                }
                MarketDataMessage::TypeForDataPoint dataPoint;
                dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(orderBookBid.price)});
                dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString("0")});
                marketDataMessage.data[MarketDataMessage::DataType::BID].emplace_back(std::move(dataPoint));
                mapOfBuyOrders.erase(data["OrderGuid"].GetString());
              } else if (orderType == "LimitOffer") {
                std::map<std::string, OrderBookPoint>::iterator it = mapOfSellOrders.begin();
                OrderBookPoint orderBookAsk;
                while(it != mapOfSellOrders.end())
                {
                  if(it->first == data["OrderGuid"].GetString()){
                    orderBookAsk = it->second;
                    break;
                  }
                  it++;
                }
                MarketDataMessage::TypeForDataPoint dataPoint;
                dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(orderBookAsk.price)});
                dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString("0")});
                marketDataMessage.data[MarketDataMessage::DataType::ASK].emplace_back(std::move(dataPoint));
                mapOfSellOrders.erase(data["OrderGuid"].GetString());
              }
              marketDataMessageList.emplace_back(std::move(marketDataMessage));
            }
      }
    } else if (event_type == "Trade") {
      std::string exchangeSubscriptionId = document["Channel"].GetString();
      auto channel_split = UtilString::split(exchangeSubscriptionId, "-");
      std::string channelId = channel_split.at(0);
      std::string symbolId = channel_split.at(1)+"-"+channel_split.at(2);
      const rj::Value& data = document["Data"];
      MarketDataMessage marketDataMessage;
      marketDataMessage.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_TRADE;
      marketDataMessage.recapType = MarketDataMessage::RecapType::NONE;
      marketDataMessage.exchangeSubscriptionId = exchangeSubscriptionId;
      marketDataMessage.tp = UtilTime::parse(std::string(data["TradeDate"].GetString()));
      MarketDataMessage::TypeForDataPoint dataPoint;
      dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(std::string(data["Price"].GetString()))});
      dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(std::string(data["Volume"].GetString()))});
      dataPoint.insert({MarketDataMessage::DataFieldType::TRADE_ID, std::string(data["TradeGuid"].GetString())});
      dataPoint.insert({MarketDataMessage::DataFieldType::IS_BUYER_MAKER, std::string(data["Side"].GetString()) == "Buy" ? "1" : "0"});
      marketDataMessage.data[MarketDataMessage::DataType::TRADE].emplace_back(std::move(dataPoint));
      marketDataMessageList.emplace_back(std::move(marketDataMessage));
    } else if (event_type == "Heartbeat") {
      CCAPI_LOGGER_DEBUG(textMessage.c_str());
    } else if (event_type == "Subscriptions") {
      event.setType(Event::Type::SUBSCRIPTION_STATUS);
      std::vector<Message> messageList;
      Message message;
      message.setTimeReceived(timeReceived);
      std::vector<std::string> correlationIdList;
      for (const auto& x : document["Data"].GetArray()) {
        std::string channelId = this->channelIdSymbolIdByConnectionIdExchangeSubscriptionIdMap[wsConnection.id][x[0].GetString()][CCAPI_CHANNEL_ID];
        std::string symbolId = this->channelIdSymbolIdByConnectionIdExchangeSubscriptionIdMap[wsConnection.id][x[0].GetString()][CCAPI_SYMBOL_ID];
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
      message.setCorrelationIdList(correlationIdList);
      message.setType(Message::Type::SUBSCRIPTION_STARTED);
      Element element;
      element.insert(CCAPI_INFO_MESSAGE, textMessage);
      message.setElementList({element});
      messageList.emplace_back(std::move(message));
      event.setMessageList(messageList);
    } else if (event_type == "Error") {
      // TODO(cryptochassis): implement
      std::string error_reason = document["Data"].GetString();
      CCAPI_LOGGER_FATAL("INDEPENDENTRESERVE Error reason: " + error_reason);
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
#endif  // INCLUDE_CCAPI_CPP_SERVICE_CCAPI_MARKET_DATA_SERVICE_INDEPENDENTRESERVE_H_