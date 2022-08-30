#ifndef INCLUDE_CCAPI_CPP_SERVICE_CCAPI_MARKET_DATA_SERVICE_BITTREX_H_
#define INCLUDE_CCAPI_CPP_SERVICE_CCAPI_MARKET_DATA_SERVICE_BITTREX_H_
#ifdef CCAPI_ENABLE_SERVICE_MARKET_DATA
#ifdef CCAPI_ENABLE_EXCHANGE_BITTREX
#include "ccapi_cpp/service/ccapi_market_data_service.h"
namespace ccapi {
class MarketDataServiceBittrex : public MarketDataService {
 public:
  MarketDataServiceBittrex(std::function<void(Event&, Queue<Event>*)> eventHandler, SessionOptions sessionOptions, SessionConfigs sessionConfigs,
                          std::shared_ptr<ServiceContext> serviceContextPtr)
      : MarketDataService(eventHandler, sessionOptions, sessionConfigs, serviceContextPtr) {
    this->exchangeName = CCAPI_EXCHANGE_NAME_BITTREX;
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
  virtual ~MarketDataServiceBittrex() {}
#ifndef CCAPI_EXPOSE_INTERNAL

 private:
#endif
  bool doesHttpBodyContainError(const Request& request, const std::string& body) override { return body.find(R"("code":0)") == std::string::npos; }
  void prepareSubscriptionDetail(std::string& channelId, std::string& symbolId, const std::string& field, const WsConnection& wsConnection,
                                 const std::map<std::string, std::string> optionMap) override {
    auto marketDepthRequested = std::stoi(optionMap.at(CCAPI_MARKET_DEPTH_MAX));
  }
  void pingOnApplicationLevel(wspp::connection_hdl hdl, ErrorCode& ec) override { this->send(hdl, R"({"H":"c3","M":"Subscribe","A":[["heartbeat"]],"I":1})", wspp::frame::opcode::text, ec); }
  std::vector<std::string> createSendStringList(const WsConnection& wsConnection) override {
    std::vector<std::string> sendStringList;
    rj::Document document;
    document.SetObject();
    rj::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("H", rj::Value("c3").Move(), allocator);
    document.AddMember("M", rj::Value("Subscribe").Move(), allocator);
    for (const auto& subscriptionListByChannelIdSymbolId : this->subscriptionListByConnectionIdChannelIdSymbolIdMap.at(wsConnection.id)) {
      auto channelId = subscriptionListByChannelIdSymbolId.first;
      rj::Value data(rj::kArrayType);
      for (const auto& subscriptionListBySymbolId : subscriptionListByChannelIdSymbolId.second) {
        std::string symbolId = subscriptionListBySymbolId.first;
        std::string exchangeSubscriptionId = channelId + ":" + symbolId;
        this->channelIdSymbolIdByConnectionIdExchangeSubscriptionIdMap[wsConnection.id][exchangeSubscriptionId][CCAPI_CHANNEL_ID] = channelId;
        this->channelIdSymbolIdByConnectionIdExchangeSubscriptionIdMap[wsConnection.id][exchangeSubscriptionId][CCAPI_SYMBOL_ID] = symbolId;
        std::string sendString;
        if(channelId == "orderBook"){
          std::string orderbook_sub = "orderbook_"+symbolId+"_25";
          data.PushBack(rj::Value(orderbook_sub.c_str(), allocator).Move(), allocator);
        } else if(channelId == "trade"){
          std::string trade_sub = "trade_"+symbolId;
          data.PushBack(rj::Value(trade_sub.c_str(), allocator).Move(), allocator);
        }
      }
      rj::Value A(rj::kArrayType);
      A.PushBack(data, allocator);;
      document.AddMember("A", A, allocator);
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
    if (document.HasMember("M")) {
      for (const auto& x : document["M"].GetArray()) {
        std::string M = x["M"].GetString();
        std::string channelId = M;
        auto now = UtilTime::now();
        if (M == "orderBook") {
//          {"marketSymbol":"BTC-USD","depth":25,"sequence":11800407,
//           "bidDeltas": [{"quantity":"0.29000000","rate":"24056.253000000000"},{"quantity":"0","rate":"23926.271000000000"}],
//           "askDeltas":[]
//          }

          std::string A = x["A"][0].GetString();
          const std::string a_decode =  websocketpp::base64_decode(A);
          char *buf = (char*)malloc(a_decode.size() * 10);
          int dstLen = a_decode.size() * 10;
          int ec = gzdecompress((&a_decode[0]),a_decode.size(),buf, dstLen);
          std::string decompressed(buf);
          free(buf);

          rj::Document orderbook_payload;
          orderbook_payload.Parse<rj::kParseNumbersAsStringsFlag>(decompressed.c_str());
          std::string symbolId = orderbook_payload["marketSymbol"].GetString();
          std::string exchangeSubscriptionId = channelId + ":" + symbolId;

          std::map<Decimal, std::string>& snapshotBid = this->snapshotBidByConnectionIdChannelIdSymbolIdMap[wsConnection.id][channelId][symbolId];
          std::map<Decimal, std::string>& snapshotAsk = this->snapshotAskByConnectionIdChannelIdSymbolIdMap[wsConnection.id][channelId][symbolId];
          if(snapshotAsk.size() == 0 && snapshotBid.size() == 0) {
            auto const host = "api.bittrex.com";
            auto const path = "/v3/markets/"+symbolId+"/orderbook?depth=25";
            auto const port = "443";
            boost::asio::io_service svc;
            ssl::context ctx(ssl::context::sslv23_client);
            ssl::stream<boost::asio::ip::tcp::socket> ssocket = { svc, ctx };
            boost::asio::ip::tcp::resolver resolver(svc);
            auto it = resolver.resolve(host, port);
            boost::asio::connect(ssocket.lowest_layer(), it);
            ssocket.handshake(ssl::stream_base::handshake_type::client);
            http::request<http::string_body> req{ http::verb::get, path, 11 };
            req.set(http::field::host, host);
            http::write(ssocket, req);
            http::response<http::string_body> res;
            boost::beast::flat_buffer buffer;
            http::read(ssocket, buffer, res);
//            std::cout << "Headers" << std::endl;
//            std::cout << res.base() << std::endl << std::endl;
//            std::cout << "Body" << std::endl;
//            std::cout << res.body() << std::endl << std::endl;
            rj::Document orderbook_snapshot;
            orderbook_snapshot.Parse<rj::kParseNumbersAsStringsFlag>(res.body().c_str());

            MarketDataMessage marketDataMessage;
            marketDataMessage.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_MARKET_DEPTH;
            marketDataMessage.recapType = MarketDataMessage::RecapType::SOLICITED;
            marketDataMessage.exchangeSubscriptionId = exchangeSubscriptionId;
            marketDataMessage.tp = now;

            for (const auto& x : orderbook_snapshot["bid"].GetArray()) {
              MarketDataMessage::TypeForDataPoint dataPoint;
              dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(x["rate"].GetString())});
              dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(x["quantity"].GetString())});
              marketDataMessage.data[MarketDataMessage::DataType::BID].emplace_back(std::move(dataPoint));
            }
            for (const auto& x : orderbook_snapshot["ask"].GetArray()) {
              MarketDataMessage::TypeForDataPoint dataPoint;
              dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(x["rate"].GetString())});
              dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(x["quantity"].GetString())});
              marketDataMessage.data[MarketDataMessage::DataType::ASK].emplace_back(std::move(dataPoint));
            }
            marketDataMessageList.emplace_back(std::move(marketDataMessage));
          } else {
            MarketDataMessage marketDataMessage;
            marketDataMessage.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_MARKET_DEPTH;
            marketDataMessage.recapType = MarketDataMessage::RecapType::NONE;
            marketDataMessage.exchangeSubscriptionId = exchangeSubscriptionId;
            marketDataMessage.tp = now;

            for (const auto& x : orderbook_payload["bidDeltas"].GetArray()) {
              MarketDataMessage::TypeForDataPoint dataPoint;
              dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(x["rate"].GetString())});
              dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(x["quantity"].GetString())});
              marketDataMessage.data[MarketDataMessage::DataType::BID].emplace_back(std::move(dataPoint));
            }
            for (const auto& x : orderbook_payload["askDeltas"].GetArray()) {
              MarketDataMessage::TypeForDataPoint dataPoint;
              dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(x["rate"].GetString())});
              dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(x["quantity"].GetString())});
              marketDataMessage.data[MarketDataMessage::DataType::ASK].emplace_back(std::move(dataPoint));
            }
            marketDataMessageList.emplace_back(std::move(marketDataMessage));
          }
        } else if (M == "trade") {
//          {"deltas":[{"id":"4b944279-7209-48d5-90b6-f5fc088e7439","executedAt":"2022-08-15T09:14:14.57Z","quantity":"0.00299460","rate":"24043.160000000000","takerSide":"BUY"},
//                     {"id":"f033a333-7203-436f-96b6-c4c408507354","executedAt":"2022-08-15T09:14:14.57Z","quantity":"0.00000001","rate":"24043.160000000000","takerSide":"BUY"}
//                    ],
//           "sequence":49114,
//           "marketSymbol":"BTC-USD"}

          std::string A = x["A"][0].GetString();
          const std::string a_decode =  websocketpp::base64_decode(A);
          char *buf = (char*)malloc(a_decode.size() * 10);
          int dstLen = a_decode.size() * 10;
          int ec = gzdecompress((&a_decode[0]),a_decode.size(),buf, dstLen);
          std::string decompressed(buf);
          free(buf);

          rj::Document trade_payload;
          trade_payload.Parse<rj::kParseNumbersAsStringsFlag>(decompressed.c_str());
          std::string symbolId = trade_payload["marketSymbol"].GetString();
          std::string exchangeSubscriptionId = channelId + ":" + symbolId;

          for (const auto& x : trade_payload["deltas"].GetArray()) {
            MarketDataMessage marketDataMessage;
            marketDataMessage.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_TRADE;
            marketDataMessage.recapType = MarketDataMessage::RecapType::NONE;
            std::string exchangeSubscriptionId = channelId + ":" + symbolId;
            marketDataMessage.exchangeSubscriptionId = exchangeSubscriptionId;
            marketDataMessage.tp = UtilTime::parse(std::string(x["executedAt"].GetString()));
            MarketDataMessage::TypeForDataPoint dataPoint;
            dataPoint.insert({MarketDataMessage::DataFieldType::PRICE, UtilString::normalizeDecimalString(std::string(x["rate"].GetString()))});
            dataPoint.insert({MarketDataMessage::DataFieldType::SIZE, UtilString::normalizeDecimalString(std::string(x["quantity"].GetString()))});
            dataPoint.insert({MarketDataMessage::DataFieldType::TRADE_ID, std::string(x["id"].GetString())});
            dataPoint.insert({MarketDataMessage::DataFieldType::IS_BUYER_MAKER, std::string(x["takerSide"].GetString()) == "BUY" ? "1" : "0"});
            marketDataMessage.data[MarketDataMessage::DataType::TRADE].emplace_back(std::move(dataPoint));
            marketDataMessageList.emplace_back(std::move(marketDataMessage));
          }
        } else if (M == "heartbeat") {
          ErrorCode ec;
          this->send(hdl, R"({"H":"c3","M":"Subscribe","A":[["heartbeat"]],"I":1})", wspp::frame::opcode::text, ec);
          if (ec) {
            this->onError(Event::Type::SUBSCRIPTION_STATUS, Message::Type::GENERIC_ERROR, ec, "pong");
          }
        }
      }
    } else if (document.HasMember("R")) {
      for (const auto& x : document["R"].GetArray()) {
        bool success = x["Success"].GetBool();
        if (success) {
          event.setType(Event::Type::SUBSCRIPTION_STATUS);
          std::vector<Message> messageList;
          Message message;
          message.setTimeReceived(timeReceived);
          std::vector<std::string> correlationIdList;
//          if (this->correlationIdListByConnectionIdChannelIdSymbolIdMap.find(wsConnection.id) != this->correlationIdListByConnectionIdChannelIdSymbolIdMap.end()) {
//            int id = std::stoi(document["id"].GetString());
//            if (this->exchangeSubscriptionIdListByExchangeJsonPayloadIdMap.find(id) != this->exchangeSubscriptionIdListByExchangeJsonPayloadIdMap.end()) {
//              for (const auto& exchangeSubscriptionId : this->exchangeSubscriptionIdListByExchangeJsonPayloadIdMap.at(id)) {
//                std::string channelId = this->channelIdSymbolIdByConnectionIdExchangeSubscriptionIdMap[wsConnection.id][exchangeSubscriptionId][CCAPI_CHANNEL_ID];
//                std::string symbolId = this->channelIdSymbolIdByConnectionIdExchangeSubscriptionIdMap[wsConnection.id][exchangeSubscriptionId][CCAPI_SYMBOL_ID];
//                if (this->correlationIdListByConnectionIdChannelIdSymbolIdMap.at(wsConnection.id).find(channelId) !=
//                    this->correlationIdListByConnectionIdChannelIdSymbolIdMap.at(wsConnection.id).end()) {
//                  if (this->correlationIdListByConnectionIdChannelIdSymbolIdMap.at(wsConnection.id).at(channelId).find(symbolId) !=
//                      this->correlationIdListByConnectionIdChannelIdSymbolIdMap.at(wsConnection.id).at(channelId).end()) {
//                    std::vector<std::string> correlationIdList_2 =
//                        this->correlationIdListByConnectionIdChannelIdSymbolIdMap.at(wsConnection.id).at(channelId).at(symbolId);
//                    correlationIdList.insert(correlationIdList.end(), correlationIdList_2.begin(), correlationIdList_2.end());
//                  }
//                }
//              }
//            }
//          }
          message.setCorrelationIdList(correlationIdList);
          message.setType(Message::Type::SUBSCRIPTION_STARTED);
          Element element;
          element.insert(CCAPI_INFO_MESSAGE, textMessage);
          message.setElementList({element});
          messageList.emplace_back(std::move(message));
          event.setMessageList(messageList);
        } else {
          // TODO(cryptochassis): implement
        }
      }
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

  // okcoin
  int gzdecompress(const char *zdata, long nzdata, const char *data, int &ndata)
  {
    int err = 0;
    z_stream d_stream = {0}; /* decompression stream */
    static char dummy_head[2] = {
        0x8 + 0x7 * 0x10,
        (((0x8 + 0x7 * 0x10) * 0x100 + 30) / 31 * 31) & 0xFF,
    };
    d_stream.zalloc = NULL;
    d_stream.zfree = NULL;
    d_stream.opaque = NULL;
    d_stream.next_in = (Bytef *)zdata;
    d_stream.avail_in = 0;
    d_stream.next_out = (Bytef *)data;
    if (inflateInit2(&d_stream, -MAX_WBITS) != Z_OK)
    {
      return -1;
    }
    // if(inflateInit2(&d_stream, 47) != Z_OK) return -1;
    while (d_stream.total_out < ndata && d_stream.total_in < nzdata)
    {
      d_stream.avail_in = d_stream.avail_out = 1; /* force small buffers */
      if ((err = inflate(&d_stream, Z_NO_FLUSH)) == Z_STREAM_END)
        break;
      if (err != Z_OK)
      {
        if (err == Z_DATA_ERROR)
        {
          d_stream.next_in = (Bytef *)dummy_head;
          d_stream.avail_in = sizeof(dummy_head);
          if ((err = inflate(&d_stream, Z_NO_FLUSH)) != Z_OK)
          {
            return -1;
          }
        }
        else
        {
          return -1;
        }
      }
    }
    if (inflateEnd(&d_stream) != Z_OK)
      return -1;
    ndata = d_stream.total_out;
    return 0;
  }
};
} /* namespace ccapi */
#endif
#endif
#endif  // INCLUDE_CCAPI_CPP_SERVICE_CCAPI_MARKET_DATA_SERVICE_BITTREX_H_