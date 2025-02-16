#include "ccapi_cpp/ccapi_session.h"
namespace ccapi {
Logger* Logger::logger = nullptr;  // This line is needed.
class MyEventHandler : public EventHandler {
 public:
  bool processEvent(const Event& event, Session* session) override {
    if (event.getType() == Event::Type::SUBSCRIPTION_DATA) {
      std::cout << "  " + toString(event) << std::endl;
      for (const auto& message : event.getMessageList()) {
        std::cout << std::string("Best bid and ask at ") + UtilTime::getISOTimestamp(message.getTime()) + " are:" << std::endl;
        for (const auto& element : message.getElementList()) {
          const std::map<std::string, std::string>& elementNameValueMap = element.getNameValueMap();
          std::cout << "  " + toString(elementNameValueMap) << std::endl;
        }
      }
    }
    return true;
  }
};
} /* namespace ccapi */
using ::ccapi::MyEventHandler;
using ::ccapi::Session;
using ::ccapi::SessionConfigs;
using ::ccapi::SessionOptions;
using ::ccapi::Subscription;
using ::ccapi::toString;

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

  SessionOptions sessionOptions;
  SessionConfigs sessionConfigs;
  MyEventHandler eventHandler;
  Session session(sessionOptions, sessionConfigs, &eventHandler);

  std::vector<Subscription> subscription;
  // 1、orderbook
   Subscription subscription1("gateio-perpetual-futures", "ETH_USDT", "MARKET_DEPTH", "MARKET_DEPTH_MAX=20","ETH_USDT|orderbook");
   Subscription subscription2("gateio-perpetual-futures", "BTC_USDT", "MARKET_DEPTH", "MARKET_DEPTH_MAX=20","BTC_USDT|orderbook");

   // 2、trade
   Subscription subscription3("gateio-perpetual-futures", "ETH_USDT", "TRADE","", "ETH_USDT|trade");
   Subscription subscription4("gateio-perpetual-futures", "BTC_USDT", "TRADE", "","BTC_USDT|trade");

   // 3、kline
   // Subscription subscription("coinbase", "BTC-USD", "TRADE", "CONFLATE_INTERVAL_MILLISECONDS=300&CONFLATE_GRACE_PERIOD_MILLISECONDS=0");

   subscription.push_back(subscription1);
   subscription.push_back(subscription2);
   subscription.push_back(subscription3);
   subscription.push_back(subscription4);

  session.subscribe(subscription);
  while(true)
  {
    if (stoped)
    {
      break;
    }
  }
  //std::this_thread::sleep_for(std::chrono::seconds(10));
  session.stop();
  std::cout << "Bye" << std::endl;
  return EXIT_SUCCESS;
}