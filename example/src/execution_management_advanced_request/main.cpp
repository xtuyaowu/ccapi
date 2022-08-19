#include "ccapi_cpp/ccapi_session.h"
namespace ccapi {
Logger* Logger::logger = nullptr;  // This line is needed.
class MyEventHandler : public EventHandler {
 public:
  bool processEvent(const Event& event, Session* session) override {
    std::cout << "Received an event:\n" + event.toStringPretty(2, 2) << std::endl;
    return true;
  }
};
} /* namespace ccapi */
using ::ccapi::MyEventHandler;
using ::ccapi::Request;
using ::ccapi::Session;
using ::ccapi::SessionConfigs;
using ::ccapi::SessionOptions;
using ::ccapi::UtilSystem;
using ::ccapi::Subscription;

bool stoped = false;
void signal_handler(int signal)
{
  std::cout << "signal_handler:" << signal << std::endl;
  if (signal == SIGINT || signal == SIGKILL)
  {
    stoped = true;
  }
}

int main(int argc, char** argv) {

  std::signal(SIGINT, signal_handler);
  std::signal(SIGKILL, signal_handler);

  if (UtilSystem::getEnvAsString("BINANCE_US_API_KEY").empty()) {
    std::cerr << "Please set environment variable BINANCE_US_API_KEY" << std::endl;
    return EXIT_FAILURE;
  }
  if (UtilSystem::getEnvAsString("BINANCE_US_API_SECRET").empty()) {
    std::cerr << "Please set environment variable BINANCE_US_API_SECRET" << std::endl;
    return EXIT_FAILURE;
  }

  SessionOptions sessionOptionsUpdate;
  SessionConfigs sessionConfigsUpdate;
  MyEventHandler eventHandlerUpdate;
  Session sessionUpdate(sessionOptionsUpdate, sessionConfigsUpdate, &eventHandlerUpdate);
  // ORDER_UPDATE
  Subscription subscriptionUpdate("binance-us", "BTCUSD", "ORDER_UPDATE");
  sessionUpdate.subscribe(subscriptionUpdate);
  std::this_thread::sleep_for(std::chrono::seconds(10));

  SessionOptions sessionOptions;
  SessionConfigs sessionConfigs;
  MyEventHandler eventHandler;
  Session session(sessionOptions, sessionConfigs, &eventHandler);
  std::cout << "place order time: "+ ccapi::UtilTime::getISOTimestamp(ccapi::UtilTime::now()) << std::endl;
  Request request(Request::Operation::CREATE_ORDER, "binance-us", "BTCUSD");
  request.appendParam({
      {"side", "SELL"},
      {"type", "STOP_LOSS_LIMIT"},
      {"quantity", "0.0005"},
      {"stopPrice", "20001"},
      {"price", "20000"},
      {"timeInForce", "GTC"},
  });
  session.sendRequest(request);
  std::this_thread::sleep_for(std::chrono::seconds(10));

  while(true)
  {
    if (stoped)
    {
      break;
    }
  }
  //std::this_thread::sleep_for(std::chrono::seconds(10));
  session.stop();
  sessionUpdate.stop();
  std::cout << "Bye" << std::endl;
  return EXIT_SUCCESS;
}

//// huobi
//int main(int argc, char** argv) {
//
//  std::signal(SIGINT, signal_handler);
//  std::signal(SIGKILL, signal_handler);
//
//  if (UtilSystem::getEnvAsString("HUOBI_API_KEY").empty()) {
//    std::cerr << "Please set environment variable BINANCE_US_API_KEY" << std::endl;
//    return EXIT_FAILURE;
//  }
//  if (UtilSystem::getEnvAsString("HUOBI_API_SECRET").empty()) {
//    std::cerr << "Please set environment variable BINANCE_US_API_SECRET" << std::endl;
//    return EXIT_FAILURE;
//  }
//
//  SessionOptions sessionOptionsUpdate;
//  SessionConfigs sessionConfigsUpdate;
//  MyEventHandler eventHandlerUpdate;
//  Session sessionUpdate(sessionOptionsUpdate, sessionConfigsUpdate, &eventHandlerUpdate);
//  // ORDER_UPDATE
//  Subscription subscriptionUpdate("huobi", "btcusdt", "ORDER_UPDATE");
//  sessionUpdate.subscribe(subscriptionUpdate);
//  std::this_thread::sleep_for(std::chrono::seconds(10));
//
//  SessionOptions sessionOptions;
//  SessionConfigs sessionConfigs;
//  MyEventHandler eventHandler;
//  Session session(sessionOptions, sessionConfigs, &eventHandler);
//  Request request(Request::Operation::CREATE_ORDER, "huobi", "btcusdt"); // GET_ACCOUNTS CREATE_ORDER
//  request.appendParam({
//      {"account-id", "2769564"},
//      {"client-order-id", "rwr2fg2e22r23455678789987"},
//      {"type", "sell-ioc"},
//      {"amount", "0.001"},
//      {"price", "25000"}
//  });
//  std::cout << "place order time: "+ ccapi::UtilTime::getISOTimestamp(ccapi::UtilTime::now()) << std::endl;
//  session.sendRequest(request);
//  std::this_thread::sleep_for(std::chrono::seconds(10));
//
//  while(true)
//  {
//    if (stoped)
//    {
//      break;
//    }
//  }
//  //std::this_thread::sleep_for(std::chrono::seconds(10));
//  session.stop();
//  sessionUpdate.stop();
//  std::cout << "Bye" << std::endl;
//  return EXIT_SUCCESS;
//}
//
//
//// kucoin
//int main(int argc, char** argv) {
//
//  std::signal(SIGINT, signal_handler);
//  std::signal(SIGKILL, signal_handler);
//
//  if (UtilSystem::getEnvAsString("KUCOIN_API_KEY").empty()) {
//    std::cerr << "Please set environment variable KUCOIN_API_KEY" << std::endl;
//    return EXIT_FAILURE;
//  }
//  if (UtilSystem::getEnvAsString("KUCOIN_API_SECRET").empty()) {
//    std::cerr << "Please set environment variable KUCOIN_API_SECRET" << std::endl;
//    return EXIT_FAILURE;
//  }
//
//  SessionOptions sessionOptionsUpdate;
//  SessionConfigs sessionConfigsUpdate;
//  MyEventHandler eventHandlerUpdate;
//  Session sessionUpdate(sessionOptionsUpdate, sessionConfigsUpdate, &eventHandlerUpdate);
//  // ORDER_UPDATE
//  Subscription subscriptionUpdate("kucoin", "BTCUSDT", "ORDER_UPDATE");
//  sessionUpdate.subscribe(subscriptionUpdate);
//  std::this_thread::sleep_for(std::chrono::seconds(10));
//
//  SessionOptions sessionOptions;
//  SessionConfigs sessionConfigs;
//  MyEventHandler eventHandler;
//  Session session(sessionOptions, sessionConfigs, &eventHandler);
//  Request request(Request::Operation::CREATE_ORDER, "kucoin", "BTCUSDT");
//  request.appendParam({
//      {CCAPI_EM_ORDER_SIDE, "sell"},
//      {CCAPI_EM_ORDER_QUANTITY, "0.001"},
//      {CCAPI_EM_ORDER_LIMIT_PRICE, "25000"},
//      {CCAPI_EM_CLIENT_ORDER_ID, "7876544678865"},
//  });
//  std::cout << "place order time: "+ ccapi::UtilTime::getISOTimestamp(ccapi::UtilTime::now()) << std::endl;
//  session.sendRequest(request);
//  std::this_thread::sleep_for(std::chrono::seconds(10));
//
//  while(true)
//  {
//    if (stoped)
//    {
//      break;
//    }
//  }
//  //std::this_thread::sleep_for(std::chrono::seconds(10));
//  session.stop();
//  sessionUpdate.stop();
//  std::cout << "Bye" << std::endl;
//  return EXIT_SUCCESS;
//}
