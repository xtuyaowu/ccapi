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
