#ifndef INCLUDE_CCAPI_CPP_CCAPI_MACRO_H_
#define INCLUDE_CCAPI_CPP_CCAPI_MACRO_H_
#ifdef SWIG
#ifndef CCAPI_FINAL
#define CCAPI_FINAL
#endif
#else
#ifndef CCAPI_FINAL
#define CCAPI_FINAL final
#endif
#endif
#ifndef CCAPI_PRINT_DOUBLE_PRECISION_DEFAULT
#define CCAPI_PRINT_DOUBLE_PRECISION_DEFAULT 10
#endif
#ifndef CCAPI_DOUBLE_ERROR_DEFAULT
#define CCAPI_DOUBLE_ERROR_DEFAULT 1e-10
#endif
#ifndef CCAPI_GENERIC_PUBLIC_SUBSCRIPTION
#define CCAPI_GENERIC_PUBLIC_SUBSCRIPTION "GENERIC_PUBLIC_SUBSCRIPTION"
#endif
#ifndef CCAPI_MARKET_DEPTH
#define CCAPI_MARKET_DEPTH "MARKET_DEPTH"
#endif
#ifndef CCAPI_TRADE
#define CCAPI_TRADE "TRADE"
#endif
#ifndef CCAPI_AGG_TRADE
#define CCAPI_AGG_TRADE "AGG_TRADE"
#endif
#ifndef CCAPI_MARKET_DEPTH_MAX
#define CCAPI_MARKET_DEPTH_MAX CCAPI_MARKET_DEPTH "_MAX"
#endif
#define CCAPI_MARKET_DEPTH_SUBSCRIBED_TO_EXCHANGE CCAPI_MARKET_DEPTH "_SUBSCRIBED_TO_EXCHANGE"
#define CCAPI_MARKET_DEPTH_MAX_DEFAULT "1"
#ifndef CCAPI_CONFLATE_INTERVAL_MILLISECONDS
#define CCAPI_CONFLATE_INTERVAL_MILLISECONDS "CONFLATE_INTERVAL_MILLISECONDS"
#endif
#define CCAPI_CONFLATE_INTERVAL_MILLISECONDS_DEFAULT "0"
#ifndef CCAPI_CONFLATE_GRACE_PERIOD_MILLISECONDS
#define CCAPI_CONFLATE_GRACE_PERIOD_MILLISECONDS "CONFLATE_GRACE_PERIOD_MILLISECONDS"
#endif
#define CCAPI_CONFLATE_GRACE_PERIOD_MILLISECONDS_DEFAULT "-1"
#ifndef CCAPI_MARKET_DEPTH_RETURN_UPDATE
#define CCAPI_MARKET_DEPTH_RETURN_UPDATE "MARKET_DEPTH_RETURN_UPDATE"
#endif
#define CCAPI_MARKET_DEPTH_RETURN_UPDATE_DEFAULT "0"
#define CCAPI_MARKET_DEPTH_RETURN_UPDATE_ENABLE "1"
#ifndef CCAPI_EXCHANGE_NAME_OKCOIN
#define CCAPI_EXCHANGE_NAME_OKCOIN "okcoin"
#endif
#ifndef CCAPI_EXCHANGE_NAME_COINBASE
#define CCAPI_EXCHANGE_NAME_COINBASE "coinbase"
#endif
#ifndef CCAPI_EXCHANGE_NAME_GEMINI
#define CCAPI_EXCHANGE_NAME_GEMINI "gemini"
#endif
#ifndef CCAPI_EXCHANGE_NAME_KRAKEN
#define CCAPI_EXCHANGE_NAME_KRAKEN "kraken"
#endif
#ifndef CCAPI_EXCHANGE_NAME_KRAKEN_FUTURES
#define CCAPI_EXCHANGE_NAME_KRAKEN_FUTURES "kraken-futures"
#endif
#ifndef CCAPI_EXCHANGE_NAME_BITSTAMP
#define CCAPI_EXCHANGE_NAME_BITSTAMP "bitstamp"
#endif
#ifndef CCAPI_EXCHANGE_NAME_BITFINEX
#define CCAPI_EXCHANGE_NAME_BITFINEX "bitfinex"
#endif
#ifndef CCAPI_EXCHANGE_NAME_BITMEX
#define CCAPI_EXCHANGE_NAME_BITMEX "bitmex"
#endif
#ifndef CCAPI_EXCHANGE_NAME_BINANCE_US
#define CCAPI_EXCHANGE_NAME_BINANCE_US "binance-us"
#endif
#ifndef CCAPI_EXCHANGE_NAME_BINANCE
#define CCAPI_EXCHANGE_NAME_BINANCE "binance"
#endif
#ifndef CCAPI_EXCHANGE_NAME_BINANCE_USDS_FUTURES
#define CCAPI_EXCHANGE_NAME_BINANCE_USDS_FUTURES "binance-usds-futures"
#endif
#ifndef CCAPI_EXCHANGE_NAME_BINANCE_COIN_FUTURES
#define CCAPI_EXCHANGE_NAME_BINANCE_COIN_FUTURES "binance-coin-futures"
#endif
#ifndef CCAPI_EXCHANGE_NAME_HUOBI
#define CCAPI_EXCHANGE_NAME_HUOBI "huobi"
#endif
#ifndef CCAPI_EXCHANGE_NAME_HUOBI_USDT_SWAP
#define CCAPI_EXCHANGE_NAME_HUOBI_USDT_SWAP "huobi-usdt-swap"
#endif
#ifndef CCAPI_EXCHANGE_NAME_HUOBI_COIN_SWAP
#define CCAPI_EXCHANGE_NAME_HUOBI_COIN_SWAP "huobi-coin-swap"
#endif
#ifndef CCAPI_EXCHANGE_NAME_OKEX
#define CCAPI_EXCHANGE_NAME_OKEX "okex"
#endif
#ifndef CCAPI_EXCHANGE_NAME_ERISX
#define CCAPI_EXCHANGE_NAME_ERISX "erisx"
#endif
#ifndef CCAPI_EXCHANGE_NAME_KUCOIN
#define CCAPI_EXCHANGE_NAME_KUCOIN "kucoin"
#endif
#ifndef CCAPI_EXCHANGE_NAME_KUCOIN_FUTURES
#define CCAPI_EXCHANGE_NAME_KUCOIN_FUTURES "kucoin-futures"
#endif
#ifndef CCAPI_EXCHANGE_NAME_FTX
#define CCAPI_EXCHANGE_NAME_FTX "ftx"
#endif
#ifndef CCAPI_EXCHANGE_NAME_FTX_US
#define CCAPI_EXCHANGE_NAME_FTX_US "ftx-us"
#endif
#ifndef CCAPI_EXCHANGE_NAME_DERIBIT
#define CCAPI_EXCHANGE_NAME_DERIBIT "deribit"
#endif
#ifndef CCAPI_EXCHANGE_NAME_GATEIO
#define CCAPI_EXCHANGE_NAME_GATEIO "gateio"
#endif
#ifndef CCAPI_EXCHANGE_NAME_GATEIO_PERPETUAL_FUTURES
#define CCAPI_EXCHANGE_NAME_GATEIO_PERPETUAL_FUTURES "gateio-perpetual-futures"
#endif
#ifndef CCAPI_EXCHANGE_NAME_CRYPTOCOM
#define CCAPI_EXCHANGE_NAME_CRYPTOCOM "cryptocom"
#endif
#ifndef CCAPI_EXCHANGE_NAME_BYBIT
#define CCAPI_EXCHANGE_NAME_BYBIT "bybit"
#endif
// #ifndef CCAPI_EXCHANGE_NAME_BYBIT_USDT_PERPETUAL
// #define CCAPI_EXCHANGE_NAME_BYBIT_USDT_PERPETUAL "bybit-usdt-perpetual"
// #endif
// #ifndef CCAPI_EXCHANGE_NAME_BYBIT_INVERSE_PERPETUAL
// #define CCAPI_EXCHANGE_NAME_BYBIT_INVERSE_PERPETUAL "bybit-inverse-perpetual"
// #endif
#ifndef CCAPI_EXCHANGE_NAME_ASCENDEX
#define CCAPI_EXCHANGE_NAME_ASCENDEX "ascendex"
#endif
#ifndef CCAPI_LAST_PRICE
#define CCAPI_LAST_PRICE "LAST_PRICE"
#endif
#ifndef CCAPI_LAST_SIZE
#define CCAPI_LAST_SIZE "LAST_SIZE"
#endif
#ifndef CCAPI_TRADE_ID
#define CCAPI_TRADE_ID "TRADE_ID"
#endif
#ifndef CCAPI_AGG_TRADE_ID
#define CCAPI_AGG_TRADE_ID "AGG_TRADE_ID"
#endif
#ifndef CCAPI_IS_BUYER_MAKER
#define CCAPI_IS_BUYER_MAKER "IS_BUYER_MAKER"
#endif
#ifndef CCAPI_SEQUENCE_NUMBER
#define CCAPI_SEQUENCE_NUMBER "SEQUENCE_NUMBER"
#endif
#ifndef CCAPI_IS_MAKER
#define CCAPI_IS_MAKER "IS_MAKER"
#endif
#ifndef CCAPI_BEST_BID_N_PRICE
#define CCAPI_BEST_BID_N_PRICE "BID_PRICE"
#endif
#ifndef CCAPI_BEST_BID_N_PRICE_EMPTY
#define CCAPI_BEST_BID_N_PRICE_EMPTY ""
#endif
#ifndef CCAPI_BEST_BID_N_SIZE
#define CCAPI_BEST_BID_N_SIZE "BID_SIZE"
#endif
#ifndef CCAPI_BEST_BID_N_SIZE_EMPTY
#define CCAPI_BEST_BID_N_SIZE_EMPTY ""
#endif
#ifndef CCAPI_BEST_ASK_N_PRICE
#define CCAPI_BEST_ASK_N_PRICE "ASK_PRICE"
#endif
#ifndef CCAPI_BEST_ASK_N_PRICE_EMPTY
#define CCAPI_BEST_ASK_N_PRICE_EMPTY ""
#endif
#ifndef CCAPI_BEST_ASK_N_SIZE
#define CCAPI_BEST_ASK_N_SIZE "ASK_SIZE"
#endif
#ifndef CCAPI_BEST_ASK_N_SIZE_EMPTY
#define CCAPI_BEST_ASK_N_SIZE_EMPTY ""
#endif
#ifndef CCAPI_OHLC_EMPTY
#define CCAPI_OHLC_EMPTY ""
#endif
#ifndef CCAPI_OPEN
#define CCAPI_OPEN "OPEN"
#endif
#ifndef CCAPI_HIGH
#define CCAPI_HIGH "HIGH"
#endif
#ifndef CCAPI_LOW
#define CCAPI_LOW "LOW"
#endif
#ifndef CCAPI_CLOSE
#define CCAPI_CLOSE "CLOSE"
#endif
#ifndef CCAPI_LIMIT
#define CCAPI_LIMIT "LIMIT"
#endif
#ifndef CCAPI_BASE_ASSET
#define CCAPI_BASE_ASSET "BASE_ASSET"
#endif
#ifndef CCAPI_QUOTE_ASSET
#define CCAPI_QUOTE_ASSET "QUOTE_ASSET"
#endif
#ifndef CCAPI_MARGIN_ASSET
#define CCAPI_MARGIN_ASSET "MARGIN_ASSET"
#endif
#ifndef CCAPI_ORDER_PRICE_INCREMENT
#define CCAPI_ORDER_PRICE_INCREMENT "PRICE_INCREMENT"
#endif
#ifndef CCAPI_ORDER_QUANTITY_INCREMENT
#define CCAPI_ORDER_QUANTITY_INCREMENT "QUANTITY_INCREMENT"
#endif
#ifndef CCAPI_ORDER_QUANTITY_MIN
#define CCAPI_ORDER_QUANTITY_MIN "QUANTITY_MIN"
#endif
#ifndef CCAPI_ORDER_PRICE_TIMES_QUANTITY_MIN
#define CCAPI_ORDER_PRICE_TIMES_QUANTITY_MIN "PRICE_TIMES_QUANTITY_MIN"
#endif
#define CCAPI_WEBSOCKET_OKCOIN_CHANNEL_TRADE "spot/trade"
#define CCAPI_WEBSOCKET_OKCOIN_CHANNEL_DEPTH "spot/depth_l2_tbt"
#define CCAPI_WEBSOCKET_COINBASE_CHANNEL_MATCH "matches"
#define CCAPI_WEBSOCKET_COINBASE_CHANNEL_LEVEL2 "level2"
#define CCAPI_WEBSOCKET_GEMINI_PARAMETER_TRADES "trades"
#define CCAPI_WEBSOCKET_GEMINI_PARAMETER_BIDS "bids"
#define CCAPI_WEBSOCKET_GEMINI_PARAMETER_OFFERS "offers"
#define CCAPI_WEBSOCKET_GEMINI_PARAMETER_TOP_OF_BOOK "top_of_book"
#define CCAPI_WEBSOCKET_KRAKEN_CHANNEL_TRADE "trade"
#define CCAPI_WEBSOCKET_KRAKEN_CHANNEL_BOOK "book"
#define CCAPI_WEBSOCKET_KRAKEN_FUTURES_CHANNEL_TRADE "trade"
#define CCAPI_WEBSOCKET_KRAKEN_FUTURES_CHANNEL_BOOK "book"
#define CCAPI_WEBSOCKET_BITSTAMP_CHANNEL_LIVE_TRADES "live_trades"
#define CCAPI_WEBSOCKET_BITSTAMP_CHANNEL_ORDER_BOOK "order_book"
#define CCAPI_WEBSOCKET_BITFINEX_CHANNEL_TRADES "trades"
#define CCAPI_WEBSOCKET_BITFINEX_CHANNEL_BOOK "book"
#define CCAPI_WEBSOCKET_BITMEX_CHANNEL_TRADE "trade"
#define CCAPI_WEBSOCKET_BITMEX_CHANNEL_QUOTE "quote"
#define CCAPI_WEBSOCKET_BITMEX_CHANNEL_ORDER_BOOK_10 "orderBook10"
#define CCAPI_WEBSOCKET_BITMEX_CHANNEL_ORDER_BOOK_L2_25 "orderBookL2_25"
#define CCAPI_WEBSOCKET_BITMEX_CHANNEL_ORDER_BOOK_L2 "orderBookL2"
#define CCAPI_WEBSOCKET_BINANCE_BASE_CHANNEL_TRADE "trade"
#define CCAPI_WEBSOCKET_BINANCE_BASE_CHANNEL_BOOK_TICKER "bookTicker"
#define CCAPI_WEBSOCKET_BINANCE_BASE_CHANNEL_PARTIAL_BOOK_DEPTH "depth"
#define CCAPI_WEBSOCKET_BINANCE_BASE_CHANNEL_AGG_TRADE "aggTrade"
#define CCAPI_WEBSOCKET_HUOBI_CHANNEL_TRADE_DETAIL "market.$symbol.trade.detail"
#define CCAPI_WEBSOCKET_HUOBI_CHANNEL_TRADE_DETAIL_REGEX "market\\.(.+)\\.trade\\.detail"
#define CCAPI_WEBSOCKET_HUOBI_CHANNEL_MARKET_BBO "market.$symbol.bbo"
#define CCAPI_WEBSOCKET_HUOBI_CHANNEL_MARKET_BBO_REGEX "market\\.(.+)\\.bbo"
#define CCAPI_WEBSOCKET_HUOBI_CHANNEL_MARKET_DEPTH "market.$symbol.depth.step0"
#define CCAPI_WEBSOCKET_HUOBI_CHANNEL_MARKET_DEPTH_REGEX "market\\.(.+)\\.depth\\.step0"
#define CCAPI_WEBSOCKET_OKEX_CHANNEL_TRADE "trades"
#define CCAPI_WEBSOCKET_OKEX_CHANNEL_PUBLIC_DEPTH50_L2_TBT "books50-l2-tbt"
#define CCAPI_WEBSOCKET_OKEX_CHANNEL_PUBLIC_DEPTH400_L2_TBT "books-l2-tbt"
#define CCAPI_WEBSOCKET_OKEX_CHANNEL_PUBLIC_DEPTH5 "books5"
#define CCAPI_WEBSOCKET_OKEX_CHANNEL_PUBLIC_DEPTH400 "books"
#define CCAPI_WEBSOCKET_ERISX_CHANNEL_MARKET_DATA_SUBSCRIBE "MarketDataSubscribe"
#define CCAPI_WEBSOCKET_ERISX_CHANNEL_TOP_OF_BOOK_MARKET_DATA_SUBSCRIBE "TopOfBookMarketDataSubscribe"
#define CCAPI_WEBSOCKET_KUCOIN_CHANNEL_MARKET_MATCH "/market/match"
#define CCAPI_WEBSOCKET_KUCOIN_CHANNEL_MARKET_LEVEL2 "/market/level2"
#define CCAPI_WEBSOCKET_KUCOIN_CHANNEL_MARKET_TICKER "/market/ticker"
#define CCAPI_WEBSOCKET_KUCOIN_CHANNEL_MARKET_LEVEL2DEPTH5 "/spotMarket/level2Depth5"
#define CCAPI_WEBSOCKET_KUCOIN_CHANNEL_MARKET_LEVEL2DEPTH50 "/spotMarket/level2Depth50"
#define CCAPI_WEBSOCKET_KUCOIN_FUTURES_CHANNEL_MARKET_MATCH "/contractMarket/execution"
#define CCAPI_WEBSOCKET_KUCOIN_FUTURES_CHANNEL_MARKET_LEVEL2 "/contractMarket/level2"
#define CCAPI_WEBSOCKET_KUCOIN_FUTURES_CHANNEL_MARKET_TICKER "/contractMarket/tickerV2"
#define CCAPI_WEBSOCKET_KUCOIN_FUTURES_CHANNEL_MARKET_LEVEL2DEPTH5 "/contractMarket/level2Depth5"
#define CCAPI_WEBSOCKET_KUCOIN_FUTURES_CHANNEL_MARKET_LEVEL2DEPTH50 "/contractMarket/level2Depth50"
#define CCAPI_WEBSOCKET_FTX_BASE_CHANNEL_TRADES "trades"
#define CCAPI_WEBSOCKET_FTX_BASE_CHANNEL_ORDERBOOKS "orderbook"
#define CCAPI_WEBSOCKET_DERIBIT_CHANNEL_TRADES "trades.{instrument_name}.{interval}"
#define CCAPI_WEBSOCKET_DERIBIT_CHANNEL_BOOK "book.{instrument_name}.{group}.{depth}.{interval}"
#define CCAPI_WEBSOCKET_DERIBIT_CHANNEL_BOOK_TBT "book.{instrument_name}.{interval}"
#define CCAPI_WEBSOCKET_DERIBIT_CHANNEL_QUOTE "quote.{instrument_name}"
#define CCAPI_WEBSOCKET_GATEIO_CHANNEL_TRADES "spot.trades"
#define CCAPI_WEBSOCKET_GATEIO_CHANNEL_BOOK_TICKER "spot.book_ticker"
#define CCAPI_WEBSOCKET_GATEIO_CHANNEL_ORDER_BOOK "spot.order_book"
#define CCAPI_WEBSOCKET_GATEIO_PERPETUAL_FUTURES_CHANNEL_TRADES "futures.trades"
#define CCAPI_WEBSOCKET_GATEIO_PERPETUAL_FUTURES_CHANNEL_BOOK_TICKER "futures.book_ticker"
#define CCAPI_WEBSOCKET_GATEIO_PERPETUAL_FUTURES_CHANNEL_ORDER_BOOK "futures.order_book"
#define CCAPI_WEBSOCKET_CRYPTOCOM_CHANNEL_TRADE "trade.{instrument_name}"
#define CCAPI_WEBSOCKET_CRYPTOCOM_CHANNEL_BOOK "book.{instrument_name}.{depth}"
#define CCAPI_WEBSOCKET_BYBIT_CHANNEL_TRADE "trade"
#define CCAPI_WEBSOCKET_BYBIT_CHANNEL_BOOK_TICKER "bookTicker"
#define CCAPI_WEBSOCKET_BYBIT_CHANNEL_DEPTH "depth"
// #define CCAPI_WEBSOCKET_BYBIT_USDT_PERPETUAL_CHANNEL_TRADE "trade"
// #define CCAPI_WEBSOCKET_BYBIT_USDT_PERPETUAL_CHANNEL_ORDER_BOOK_L2_25 "orderBookL2_25"
// #define CCAPI_WEBSOCKET_BYBIT_USDT_PERPETUAL_CHANNEL_ORDER_BOOK_L2_200 "orderBookL2_200"
// #define CCAPI_WEBSOCKET_BYBIT_INVERSE_PERPETUAL_CHANNEL_TRADE "trade"
// #define CCAPI_WEBSOCKET_BYBIT_INVERSE_PERPETUAL_CHANNEL_ORDER_BOOK_L2_25 "orderBookL2_25"
// #define CCAPI_WEBSOCKET_BYBIT_INVERSE_PERPETUAL_CHANNEL_ORDER_BOOK_L2_200 "orderBookL2_200"
#define CCAPI_WEBSOCKET_ASCENDEX_CHANNEL_TRADES "trades"
#define CCAPI_WEBSOCKET_ASCENDEX_CHANNEL_BBO "bbo"
#define CCAPI_WEBSOCKET_ASCENDEX_CHANNEL_DEPTH "depth"
#ifndef CCAPI_CHANNEL_ID
#define CCAPI_CHANNEL_ID "channelId"
#endif
#ifndef CCAPI_SYMBOL_ID
#define CCAPI_SYMBOL_ID "symbolId"
#endif
#ifndef CCAPI_CONNECTION_ID
#define CCAPI_CONNECTION_ID "CONNECTION_ID"
#endif
#ifndef CCAPI_REASON
#define CCAPI_REASON "REASON"
#endif
#ifndef CCAPI_MARKET_DATA
#define CCAPI_MARKET_DATA "market_data"
#endif
#ifndef CCAPI_EXECUTION_MANAGEMENT
#define CCAPI_EXECUTION_MANAGEMENT "execution_management"
#endif
#ifndef CCAPI_FIX
#define CCAPI_FIX "FIX"
#endif
#ifndef CCAPI_FIX_MARKET_DATA
#define CCAPI_FIX_MARKET_DATA "FIX_MARKET_DATA"
#endif
#ifndef CCAPI_FIX_EXECUTION_MANAGEMENT
#define CCAPI_FIX_EXECUTION_MANAGEMENT "FIX_EXECUTION_MANAGEMENT"
#endif
#ifndef CCAPI_UNKNOWN
#define CCAPI_UNKNOWN "unknown"
#endif
#define CCAPI_EM_ORDER_UPDATE "ORDER_UPDATE"
#define CCAPI_EM_PRIVATE_TRADE "PRIVATE_TRADE"
#ifndef CCAPI_EM_ORDER_SIDE
#define CCAPI_EM_ORDER_SIDE "SIDE"
#endif
#ifndef CCAPI_EM_ORDER_SIDE_BUY
#define CCAPI_EM_ORDER_SIDE_BUY "BUY"
#endif
#ifndef CCAPI_EM_ORDER_SIDE_SELL
#define CCAPI_EM_ORDER_SIDE_SELL "SELL"
#endif
#ifndef CCAPI_EM_ORDER_TYPE
#define CCAPI_EM_ORDER_TYPE "TYPE"
#endif
#ifndef CCAPI_EM_ORDER_QUANTITY
#define CCAPI_EM_ORDER_QUANTITY "QUANTITY"
#endif
#ifndef CCAPI_EM_ORDER_LIMIT_PRICE
#define CCAPI_EM_ORDER_LIMIT_PRICE "LIMIT_PRICE"
#endif
#ifndef CCAPI_EM_ORDER_LAST_EXECUTED_PRICE
#define CCAPI_EM_ORDER_LAST_EXECUTED_PRICE "LAST_EXECUTED_PRICE"
#endif
#ifndef CCAPI_EM_ORDER_LAST_EXECUTED_SIZE
#define CCAPI_EM_ORDER_LAST_EXECUTED_SIZE "LAST_EXECUTED_SIZE"
#endif
#ifndef CCAPI_EM_ORDER_FEE_QUANTITY
#define CCAPI_EM_ORDER_FEE_QUANTITY "FEE_QUANTITY"
#endif
#ifndef CCAPI_EM_ORDER_FEE_ASSET
#define CCAPI_EM_ORDER_FEE_ASSET "FEE_ASSET"
#endif
#ifndef CCAPI_EM_ACCOUNT_ID
#define CCAPI_EM_ACCOUNT_ID "ACCOUNT_ID"
#endif
#ifndef CCAPI_EM_ACCOUNT_TYPE
#define CCAPI_EM_ACCOUNT_TYPE "ACCOUNT_TYPE"
#endif
#ifndef CCAPI_EM_ASSET
#define CCAPI_EM_ASSET "ASSET"
#endif
#ifndef CCAPI_EM_QUANTITY_TOTAL
#define CCAPI_EM_QUANTITY_TOTAL "QUANTITY_TOTAL"
#endif
#ifndef CCAPI_EM_QUANTITY_AVAILABLE_FOR_TRADING
#define CCAPI_EM_QUANTITY_AVAILABLE_FOR_TRADING "QUANTITY_AVAILABLE_FOR_TRADING"
#endif
#ifndef CCAPI_EM_BASE_ASSET_QUANTITY_TOTAL
#define CCAPI_EM_BASE_ASSET_QUANTITY_TOTAL "BASE_ASSET_QUANTITY_TOTAL"
#endif
#ifndef CCAPI_EM_BASE_ASSET_QUANTITY_AVAILABLE_FOR_TRADING
#define CCAPI_EM_BASE_ASSET_QUANTITY_AVAILABLE_FOR_TRADING "BASE_ASSET_QUANTITY_AVAILABLE_FOR_TRADING"
#endif
#ifndef CCAPI_EM_QUOTE_ASSET_QUANTITY_TOTAL
#define CCAPI_EM_QUOTE_ASSET_QUANTITY_TOTAL "QUOTE_ASSET_QUANTITY_TOTAL"
#endif
#ifndef CCAPI_EM_QUOTE_ASSET_QUANTITY_AVAILABLE_FOR_TRADING
#define CCAPI_EM_QUOTE_ASSET_QUANTITY_AVAILABLE_FOR_TRADING "QUOTE_ASSET_QUANTITY_AVAILABLE_FOR_TRADING"
#endif
#ifndef CCAPI_EM_SYMBOL
#define CCAPI_EM_SYMBOL "SYMBOL"
#endif
#ifndef CCAPI_UNDERLYING_SYMBOL
#define CCAPI_UNDERLYING_SYMBOL "UNDERLYING_SYMBOL"
#endif
#ifndef CCAPI_EM_POSITION_SIDE
#define CCAPI_EM_POSITION_SIDE "POSITION_SIDE"
#endif
#ifndef CCAPI_EM_POSITION_QUANTITY
#define CCAPI_EM_POSITION_QUANTITY "QUANTITY"
#endif
#ifndef CCAPI_EM_POSITION_COST
#define CCAPI_EM_POSITION_COST "COST"
#endif
#ifndef CCAPI_EM_PARTY_ID
#define CCAPI_EM_PARTY_ID "PARTY_ID"
#endif
#ifndef CCAPI_EM_ORDER_ID
#define CCAPI_EM_ORDER_ID "ORDER_ID"
#endif
#ifndef CCAPI_EM_CLIENT_ORDER_ID
#define CCAPI_EM_CLIENT_ORDER_ID "CLIENT_ORDER_ID"
#endif
#ifndef CCAPI_EM_ORIGINAL_CLIENT_ORDER_ID
#define CCAPI_EM_ORIGINAL_CLIENT_ORDER_ID "ORIGINAL_CLIENT_ORDER_ID"
#endif
#ifndef CCAPI_EM_ORDER_CUMULATIVE_FILLED_QUANTITY
#define CCAPI_EM_ORDER_CUMULATIVE_FILLED_QUANTITY "CUMULATIVE_FILLED_QUANTITY"
#endif
#ifndef CCAPI_EM_ORDER_REMAINING_QUANTITY
#define CCAPI_EM_ORDER_REMAINING_QUANTITY "REMAINING_QUANTITY"
#endif
#ifndef CCAPI_EM_ORDER_CUMULATIVE_FILLED_PRICE_TIMES_QUANTITY
#define CCAPI_EM_ORDER_CUMULATIVE_FILLED_PRICE_TIMES_QUANTITY "CUMULATIVE_FILLED_PRICE_TIMES_QUANTITY"
#endif
#ifndef CCAPI_EM_ORDER_INSTRUMENT
#define CCAPI_EM_ORDER_INSTRUMENT "INSTRUMENT"
#endif
#ifndef CCAPI_INSTRUMENT_TYPE
#define CCAPI_INSTRUMENT_TYPE "INSTRUMENT_TYPE"
#endif
#ifndef CCAPI_INSTRUMENT
#define CCAPI_INSTRUMENT "INSTRUMENT"
#endif
#ifndef CCAPI_EM_ORDER_STATUS
#define CCAPI_EM_ORDER_STATUS "STATUS"
#endif
#ifndef CCAPI_EM_ORDER_LEVERAGE
#define CCAPI_EM_ORDER_LEVERAGE "LEVERAGE"
#endif
#ifndef CCAPI_EM_POSITION_LEVERAGE
#define CCAPI_EM_POSITION_LEVERAGE "LEVERAGE"
#endif
#ifndef CCAPI_HTTP_STATUS_CODE
#define CCAPI_HTTP_STATUS_CODE "HTTP_STATUS_CODE"
#endif
#ifndef CCAPI_HTTP_PROTOCOL
#define CCAPI_HTTP_PROTOCOL "HTTP_PROTOCOL"
#endif
#ifndef CCAPI_HTTP_HOST
#define CCAPI_HTTP_HOST "HTTP_HOST"
#endif
#ifndef CCAPI_HTTP_PORT
#define CCAPI_HTTP_PORT "HTTP_PORT"
#endif
#ifndef CCAPI_HTTP_PATH
#define CCAPI_HTTP_PATH "HTTP_PATH"
#endif
#ifndef CCAPI_HTTP_METHOD
#define CCAPI_HTTP_METHOD "HTTP_METHOD"
#endif
#ifndef CCAPI_HTTP_HEADERS
#define CCAPI_HTTP_HEADERS "HTTP_HEADERS"
#endif
#ifndef CCAPI_HTTP_BODY
#define CCAPI_HTTP_BODY "HTTP_BODY"
#endif
#ifndef CCAPI_HTTP_QUERY_STRING
#define CCAPI_HTTP_QUERY_STRING "HTTP_QUERY_STRING"
#endif
#ifndef CCAPI_WEBSOCKET_MESSAGE_PAYLOAD
#define CCAPI_WEBSOCKET_MESSAGE_PAYLOAD "WEBSOCKET_MESSAGE_PAYLOAD"
#endif
#ifndef CCAPI_ERROR_MESSAGE
#define CCAPI_ERROR_MESSAGE "ERROR_MESSAGE"
#endif
#ifndef CCAPI_INFO_MESSAGE
#define CCAPI_INFO_MESSAGE "INFO_MESSAGE"
#endif
#define CCAPI_UNSUPPORTED_VALUE "UNSUPPORTED VALUE"
#ifndef CCAPI_CORRELATION_ID_GENERATED_LENGTH
#define CCAPI_CORRELATION_ID_GENERATED_LENGTH 8
#endif
#ifndef CCAPI_CREDENTIAL_DISPLAY_LENGTH
#define CCAPI_CREDENTIAL_DISPLAY_LENGTH 4
#endif

// start: exchange REST urls
#ifndef CCAPI_OKCOIN_URL_REST_BASE
#define CCAPI_OKCOIN_URL_REST_BASE "https://www.okcoin.com/api"
#endif
#ifndef CCAPI_COINBASE_URL_REST_BASE
#define CCAPI_COINBASE_URL_REST_BASE "https://api.pro.coinbase.com"
#endif
#ifndef CCAPI_GEMINI_URL_REST_BASE
#define CCAPI_GEMINI_URL_REST_BASE "https://api.gemini.com"
#endif
#ifndef CCAPI_KRAKEN_URL_REST_BASE
#define CCAPI_KRAKEN_URL_REST_BASE "https://api.kraken.com"
#endif
#ifndef CCAPI_KRAKEN_FUTURES_URL_REST_BASE
#define CCAPI_KRAKEN_FUTURES_URL_REST_BASE "https://futures.kraken.com"
#endif
#ifndef CCAPI_BITSTAMP_URL_REST_BASE
#define CCAPI_BITSTAMP_URL_REST_BASE "https://www.bitstamp.net"
#endif
#ifndef CCAPI_BITFINEX_PUBLIC_URL_REST_BASE
#define CCAPI_BITFINEX_PUBLIC_URL_REST_BASE "https://api-pub.bitfinex.com"
#endif
#ifndef CCAPI_BITFINEX_PRIVATE_URL_REST_BASE
#define CCAPI_BITFINEX_PRIVATE_URL_REST_BASE "https://api.bitfinex.com"
#endif
#ifndef CCAPI_BITFINEX_GET_INSTRUMENTS_PATH
#define CCAPI_BITFINEX_GET_INSTRUMENTS_PATH "/v2/conf/pub:info:pair"  // use conf/pub:info:pair:futures for futures
#endif
#ifndef CCAPI_BITMEX_URL_REST_BASE
#define CCAPI_BITMEX_URL_REST_BASE "https://www.bitmex.com"
#endif
#ifndef CCAPI_BINANCE_US_URL_REST_BASE
#define CCAPI_BINANCE_US_URL_REST_BASE "https://api.binance.us"
#endif
#ifndef CCAPI_BINANCE_US_CREATE_ORDER_PATH
#define CCAPI_BINANCE_US_CREATE_ORDER_PATH "/api/v3/order"
#endif
#ifndef CCAPI_BINANCE_US_LISTEN_KEY_PATH
#define CCAPI_BINANCE_US_LISTEN_KEY_PATH "/api/v3/userDataStream"
#endif
#ifndef CCAPI_BINANCE_URL_REST_BASE
#define CCAPI_BINANCE_URL_REST_BASE "https://api.binance.com"
#endif
#ifndef CCAPI_BINANCE_CREATE_ORDER_PATH
#define CCAPI_BINANCE_CREATE_ORDER_PATH "/api/v3/order"
#endif
#ifndef CCAPI_BINANCE_LISTEN_KEY_PATH
#define CCAPI_BINANCE_LISTEN_KEY_PATH "/api/v3/userDataStream"
#endif
#ifndef CCAPI_BINANCE_USDS_FUTURES_URL_REST_BASE
#define CCAPI_BINANCE_USDS_FUTURES_URL_REST_BASE "https://fapi.binance.com"
#endif
#ifndef CCAPI_BINANCE_USDS_FUTURES_CREATE_ORDER_PATH
#define CCAPI_BINANCE_USDS_FUTURES_CREATE_ORDER_PATH "/fapi/v1/order"
#endif
#ifndef CCAPI_BINANCE_USDS_FUTURES_LISTEN_KEY_PATH
#define CCAPI_BINANCE_USDS_FUTURES_LISTEN_KEY_PATH "/fapi/v1/listenKey"
#endif
#ifndef CCAPI_BINANCE_COIN_FUTURES_URL_REST_BASE
#define CCAPI_BINANCE_COIN_FUTURES_URL_REST_BASE "https://dapi.binance.com"
#endif
#ifndef CCAPI_BINANCE_COIN_FUTURES_CREATE_ORDER_PATH
#define CCAPI_BINANCE_COIN_FUTURES_CREATE_ORDER_PATH "/dapi/v1/order"
#endif
#ifndef CCAPI_BINANCE_COIN_FUTURES_LISTEN_KEY_PATH
#define CCAPI_BINANCE_COIN_FUTURES_LISTEN_KEY_PATH "/dapi/v1/listenKey"
#endif
#ifndef CCAPI_HUOBI_URL_REST_BASE
#define CCAPI_HUOBI_URL_REST_BASE "https://api.huobi.pro"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_URL_REST_BASE
#define CCAPI_HUOBI_USDT_SWAP_URL_REST_BASE "https://api.hbdm.com"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_URL_REST_BASE
#define CCAPI_HUOBI_COIN_SWAP_URL_REST_BASE "https://api.hbdm.com"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_CREATE_ORDER_PATH
#define CCAPI_HUOBI_USDT_SWAP_CREATE_ORDER_PATH "/linear-swap-api/v1/swap_cross_order"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_CREATE_ORDER_PATH
#define CCAPI_HUOBI_COIN_SWAP_CREATE_ORDER_PATH "/swap-api/v1/swap_order"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_CANCEL_ORDER_PATH
#define CCAPI_HUOBI_USDT_SWAP_CANCEL_ORDER_PATH "/linear-swap-api/v1/swap_cross_cancel"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_CANCEL_ORDER_PATH
#define CCAPI_HUOBI_COIN_SWAP_CANCEL_ORDER_PATH "/swap-api/v1/swap_cancel"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_GET_ORDER_PATH
#define CCAPI_HUOBI_USDT_SWAP_GET_ORDER_PATH "/linear-swap-api/v1/swap_cross_order_info"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_GET_ORDER_PATH
#define CCAPI_HUOBI_COIN_SWAP_GET_ORDER_PATH "/swap-api/v1/swap_order_info"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_GET_OPEN_ORDERS_PATH
#define CCAPI_HUOBI_USDT_SWAP_GET_OPEN_ORDERS_PATH "/linear-swap-api/v1/swap_cross_openorders"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_GET_OPEN_ORDERS_PATH
#define CCAPI_HUOBI_COIN_SWAP_GET_OPEN_ORDERS_PATH "/swap-api/v1/swap_openorders"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_CANCEL_ALL_ORDERS_PATH
#define CCAPI_HUOBI_USDT_SWAP_CANCEL_ALL_ORDERS_PATH "/linear-swap-api/v1/swap_cross_cancelall"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_CANCEL_ALL_ORDERS_PATH
#define CCAPI_HUOBI_COIN_SWAP_CANCEL_ALL_ORDERS_PATH "/swap-api/v1/swap_cancelall"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_GET_ACCOUNT_BALANCES_PATH
#define CCAPI_HUOBI_USDT_SWAP_GET_ACCOUNT_BALANCES_PATH "/linear-swap-api/v1/swap_cross_account_info"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_GET_ACCOUNT_BALANCES_PATH
#define CCAPI_HUOBI_COIN_SWAP_GET_ACCOUNT_BALANCES_PATH "/swap-api/v1/swap_account_info"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_GET_ACCOUNT_POSITIONS_PATH
#define CCAPI_HUOBI_USDT_SWAP_GET_ACCOUNT_POSITIONS_PATH "/linear-swap-api/v1/swap_cross_position_info"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_GET_ACCOUNT_POSITIONS_PATH
#define CCAPI_HUOBI_COIN_SWAP_GET_ACCOUNT_POSITIONS_PATH "/swap-api/v1/swap_position_info"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_GET_RECENT_TRADES_PATH
#define CCAPI_HUOBI_USDT_SWAP_GET_RECENT_TRADES_PATH "/linear-swap-ex/market/history/trade"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_GET_RECENT_TRADES_PATH
#define CCAPI_HUOBI_COIN_SWAP_GET_RECENT_TRADES_PATH "/swap-ex/market/history/trade"
#endif
#ifndef CCAPI_OKEX_URL_REST_BASE
#define CCAPI_OKEX_URL_REST_BASE "https://www.okex.com"
#endif
#ifndef CCAPI_ERISX_URL_REST_BASE
#define CCAPI_ERISX_URL_REST_BASE "https://trade-api.erisx.com"
#endif
#ifndef CCAPI_KUCOIN_URL_REST_BASE
#define CCAPI_KUCOIN_URL_REST_BASE "https://api.kucoin.com"
#endif
#ifndef CCAPI_KUCOIN_FUTURES_URL_REST_BASE
#define CCAPI_KUCOIN_FUTURES_URL_REST_BASE "https://api-futures.kucoin.com"
#endif
#ifndef CCAPI_FTX_URL_REST_BASE
#define CCAPI_FTX_URL_REST_BASE "https://ftx.com"
#endif
#ifndef CCAPI_FTX_US_URL_REST_BASE
#define CCAPI_FTX_US_URL_REST_BASE "https://ftx.us"
#endif
#ifndef CCAPI_DERIBIT_URL_REST_BASE
#define CCAPI_DERIBIT_URL_REST_BASE "https://www.deribit.com"
#endif
#ifndef CCAPI_GATEIO_URL_REST_BASE
#define CCAPI_GATEIO_URL_REST_BASE "https://api.gateio.ws"
#endif
#ifndef CCAPI_GATEIO_PERPETUAL_FUTURES_URL_REST_BASE
#define CCAPI_GATEIO_PERPETUAL_FUTURES_URL_REST_BASE "https://fx-api.gateio.ws"
#endif
#ifndef CCAPI_CRYPTOCOM_URL_REST_BASE
#define CCAPI_CRYPTOCOM_URL_REST_BASE "https://api.crypto.com"
#endif
#ifndef CCAPI_BYBIT_URL_REST_BASE
#define CCAPI_BYBIT_URL_REST_BASE "https://api.bybit.com"
#endif
// #ifndef CCAPI_BYBIT_USDT_PERPETUAL_URL_REST_BASE
// #define CCAPI_BYBIT_USDT_PERPETUAL_URL_REST_BASE "https://api.bybit.com"
// #endif
// #ifndef CCAPI_BYBIT_INVERSE_PERPETUAL_URL_REST_BASE
// #define CCAPI_BYBIT_INVERSE_PERPETUAL_URL_REST_BASE "https://api.bybit.com"
// #endif
#ifndef CCAPI_ASCENDEX_URL_REST_BASE
#define CCAPI_ASCENDEX_URL_REST_BASE "https://ascendex.com"
#endif
// end: exchange REST urls

// start: exchange WS urls
#ifndef CCAPI_OKCOIN_URL_WS_BASE
#define CCAPI_OKCOIN_URL_WS_BASE "wss://real.okcoin.com:8443/ws/v3"
#endif
#ifndef CCAPI_COINBASE_URL_WS_BASE
#define CCAPI_COINBASE_URL_WS_BASE "wss://ws-feed.pro.coinbase.com"
#endif
#ifndef CCAPI_GEMINI_URL_WS_BASE
#define CCAPI_GEMINI_URL_WS_BASE "wss://api.gemini.com"
#endif
#ifndef CCAPI_KRAKEN_URL_WS_BASE
#define CCAPI_KRAKEN_URL_WS_BASE "wss://ws.kraken.com"
#endif
#ifndef CCAPI_KRAKEN_URL_WS_BASE_PRIVATE
#define CCAPI_KRAKEN_URL_WS_BASE_PRIVATE "wss://ws-auth.kraken.com"
#endif
#ifndef CCAPI_KRAKEN_FUTURES_URL_WS_BASE
#define CCAPI_KRAKEN_FUTURES_URL_WS_BASE "wss://futures.kraken.com"
#endif
#ifndef CCAPI_BITSTAMP_URL_WS_BASE
#define CCAPI_BITSTAMP_URL_WS_BASE "wss://ws.bitstamp.net"
#endif
#ifndef CCAPI_BITFINEX_PUBLIC_URL_WS_BASE
#define CCAPI_BITFINEX_PUBLIC_URL_WS_BASE "wss://api-pub.bitfinex.com"
#endif
#ifndef CCAPI_BITFINEX_PRIVATE_URL_WS_BASE
#define CCAPI_BITFINEX_PRIVATE_URL_WS_BASE "wss://api.bitfinex.com"
#endif
#ifndef CCAPI_BITMEX_URL_WS_BASE
#define CCAPI_BITMEX_URL_WS_BASE "wss://www.bitmex.com"
#endif
#ifndef CCAPI_BINANCE_US_URL_WS_BASE
#define CCAPI_BINANCE_US_URL_WS_BASE "wss://stream.binance.us:9443"
#endif
#ifndef CCAPI_BINANCE_URL_WS_BASE
#define CCAPI_BINANCE_URL_WS_BASE "wss://stream.binance.com:9443"
#endif
#ifndef CCAPI_BINANCE_USDS_FUTURES_URL_WS_BASE
#define CCAPI_BINANCE_USDS_FUTURES_URL_WS_BASE "wss://fstream.binance.com"
#endif
#ifndef CCAPI_BINANCE_COIN_FUTURES_URL_WS_BASE
#define CCAPI_BINANCE_COIN_FUTURES_URL_WS_BASE "wss://dstream.binance.com"
#endif
#ifndef CCAPI_HUOBI_URL_WS_BASE
#define CCAPI_HUOBI_URL_WS_BASE "wss://api.huobi.pro"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_URL_WS_BASE
#define CCAPI_HUOBI_USDT_SWAP_URL_WS_BASE "wss://api.hbdm.com"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_SUBSCRIBE_ORDER_DATA_TOPIC
#define CCAPI_HUOBI_USDT_SWAP_SUBSCRIBE_ORDER_DATA_TOPIC "orders_cross"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_SUBSCRIBE_MATCH_ORDER_DATA_TOPIC
#define CCAPI_HUOBI_USDT_SWAP_SUBSCRIBE_MATCH_ORDER_DATA_TOPIC "matchOrders_cross"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_URL_WS_BASE
#define CCAPI_HUOBI_COIN_SWAP_URL_WS_BASE "wss://api.hbdm.com"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_SUBSCRIBE_ORDER_DATA_TOPIC
#define CCAPI_HUOBI_COIN_SWAP_SUBSCRIBE_ORDER_DATA_TOPIC "orders"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_SUBSCRIBE_MATCH_ORDER_DATA_TOPIC
#define CCAPI_HUOBI_COIN_SWAP_SUBSCRIBE_MATCH_ORDER_DATA_TOPIC "matchOrders"
#endif
#ifndef CCAPI_OKEX_URL_WS_BASE
#define CCAPI_OKEX_URL_WS_BASE "wss://ws.okex.com:8443"
#endif
#ifndef CCAPI_OKEX_PUBLIC_WS_PATH
#define CCAPI_OKEX_PUBLIC_WS_PATH "/ws/v5/public"
#endif
#ifndef CCAPI_OKEX_PRIVATE_WS_PATH
#define CCAPI_OKEX_PRIVATE_WS_PATH "/ws/v5/private"
#endif
#ifndef CCAPI_ERISX_URL_WS_BASE
#define CCAPI_ERISX_URL_WS_BASE "wss://publicmd-api.erisx.com"
#endif
#ifndef CCAPI_FTX_URL_WS_BASE
#define CCAPI_FTX_URL_WS_BASE "wss://ftx.com"
#endif
#ifndef CCAPI_FTX_US_URL_WS_BASE
#define CCAPI_FTX_US_URL_WS_BASE "wss://ftx.us"
#endif
#ifndef CCAPI_DERIBIT_URL_WS_BASE
#define CCAPI_DERIBIT_URL_WS_BASE "wss://www.deribit.com"
#endif
#ifndef CCAPI_GATEIO_URL_WS_BASE
#define CCAPI_GATEIO_URL_WS_BASE "wss://api.gateio.ws"
#endif
#ifndef CCAPI_GATEIO_PERPETUAL_FUTURES_URL_WS_BASE
#define CCAPI_GATEIO_PERPETUAL_FUTURES_URL_WS_BASE "wss://fx-ws.gateio.ws"
#endif
#ifndef CCAPI_CRYPTOCOM_URL_WS_BASE
#define CCAPI_CRYPTOCOM_URL_WS_BASE "wss://stream.crypto.com"
#endif
#ifndef CCAPI_BYBIT_URL_WS_BASE
#define CCAPI_BYBIT_URL_WS_BASE "wss://stream.bybit.com"
#endif
// #ifndef CCAPI_BYBIT_USDT_PERPETUAL_URL_WS_BASE
// #define CCAPI_BYBIT_USDT_PERPETUAL_URL_WS_BASE "https://api.bybit.com"
// #endif
// #ifndef CCAPI_BYBIT_INVERSE_PERPETUAL_URL_WS_BASE
// #define CCAPI_BYBIT_INVERSE_PERPETUAL_URL_WS_BASE "https://api.bybit.com"
// #endif
#ifndef CCAPI_ASCENDEX_URL_WS_BASE
#define CCAPI_ASCENDEX_URL_WS_BASE "wss://ascendex.com"
#endif
// end: exchange WS urls

// start: exchange FIX urls
#ifndef CCAPI_COINBASE_URL_FIX_BASE
#define CCAPI_COINBASE_URL_FIX_BASE "tcp+ssl://fix.pro.coinbase.com:4198"
#endif
#ifndef CCAPI_GEMINI_URL_FIX_HOST
#define CCAPI_GEMINI_URL_FIX_HOST ""
#endif
#ifndef CCAPI_GEMINI_URL_FIX_PORT
#define CCAPI_GEMINI_URL_FIX_PORT ""
#endif
#ifndef CCAPI_FTX_URL_FIX_BASE
#define CCAPI_FTX_URL_FIX_BASE "tcp+ssl://fix.ftx.com:4363"
#endif
#ifndef CCAPI_FTX_US_URL_FIX_BASE
#define CCAPI_FTX_US_URL_FIX_BASE "tcp+ssl://fix.ftx.us:4363"
#endif
#ifndef CCAPI_DERIBIT_URL_FIX_BASE
#define CCAPI_DERIBIT_URL_FIX_BASE "www.deribit.com:9883"
#endif
// end: exchange FIX urls

// start: exchange API credentials
#ifndef CCAPI_COINBASE_API_KEY
#define CCAPI_COINBASE_API_KEY "COINBASE_API_KEY"
#endif
#ifndef CCAPI_COINBASE_API_SECRET
#define CCAPI_COINBASE_API_SECRET "COINBASE_API_SECRET"
#endif
#ifndef CCAPI_COINBASE_API_PASSPHRASE
#define CCAPI_COINBASE_API_PASSPHRASE "COINBASE_API_PASSPHRASE"
#endif
#ifndef CCAPI_GEMINI_API_KEY
#define CCAPI_GEMINI_API_KEY "GEMINI_API_KEY"
#endif
#ifndef CCAPI_GEMINI_API_SECRET
#define CCAPI_GEMINI_API_SECRET "GEMINI_API_SECRET"
#endif
#ifndef CCAPI_GEMINI_API_SENDER_COMP_ID
#define CCAPI_GEMINI_API_SENDER_COMP_ID ""
#endif
#ifndef CCAPI_GEMINI_API_TARGET_COMP_ID
#define CCAPI_GEMINI_API_TARGET_COMP_ID ""
#endif
#ifndef CCAPI_KRAKEN_API_KEY
#define CCAPI_KRAKEN_API_KEY "KRAKEN_API_KEY"
#endif
#ifndef CCAPI_KRAKEN_API_SECRET
#define CCAPI_KRAKEN_API_SECRET "KRAKEN_API_SECRET"
#endif
#ifndef CCAPI_KRAKEN_FUTURES_API_KEY
#define CCAPI_KRAKEN_FUTURES_API_KEY "KRAKEN_FUTURES_API_KEY"
#endif
#ifndef CCAPI_KRAKEN_FUTURES_API_SECRET
#define CCAPI_KRAKEN_FUTURES_API_SECRET "KRAKEN_FUTURES_API_SECRET"
#endif
#ifndef CCAPI_BITSTAMP_API_KEY
#define CCAPI_BITSTAMP_API_KEY "BITSTAMP_API_KEY"
#endif
#ifndef CCAPI_BITSTAMP_API_SECRET
#define CCAPI_BITSTAMP_API_SECRET "BITSTAMP_API_SECRET"
#endif
#ifndef CCAPI_BITFINEX_API_KEY
#define CCAPI_BITFINEX_API_KEY "BITFINEX_API_KEY"
#endif
#ifndef CCAPI_BITFINEX_API_SECRET
#define CCAPI_BITFINEX_API_SECRET "BITFINEX_API_SECRET"
#endif
#ifndef CCAPI_BITMEX_API_KEY
#define CCAPI_BITMEX_API_KEY "BITMEX_API_KEY"
#endif
#ifndef CCAPI_BITMEX_API_SECRET
#define CCAPI_BITMEX_API_SECRET "BITMEX_API_SECRET"
#endif
#ifndef CCAPI_BINANCE_US_API_KEY
#define CCAPI_BINANCE_US_API_KEY "BINANCE_US_API_KEY"
#endif
#ifndef CCAPI_BINANCE_US_API_SECRET
#define CCAPI_BINANCE_US_API_SECRET "BINANCE_US_API_SECRET"
#endif
#ifndef CCAPI_BINANCE_API_KEY
#define CCAPI_BINANCE_API_KEY "BINANCE_API_KEY"
#endif
#ifndef CCAPI_BINANCE_API_SECRET
#define CCAPI_BINANCE_API_SECRET "BINANCE_API_SECRET"
#endif
#ifndef CCAPI_BINANCE_USDS_FUTURES_API_KEY
#define CCAPI_BINANCE_USDS_FUTURES_API_KEY "BINANCE_USDS_FUTURES_API_KEY"
#endif
#ifndef CCAPI_BINANCE_USDS_FUTURES_API_SECRET
#define CCAPI_BINANCE_USDS_FUTURES_API_SECRET "BINANCE_USDS_FUTURES_API_SECRET"
#endif
#ifndef CCAPI_BINANCE_COIN_FUTURES_API_KEY
#define CCAPI_BINANCE_COIN_FUTURES_API_KEY "BINANCE_COIN_FUTURES_API_KEY"
#endif
#ifndef CCAPI_BINANCE_COIN_FUTURES_API_SECRET
#define CCAPI_BINANCE_COIN_FUTURES_API_SECRET "BINANCE_COIN_FUTURES_API_SECRET"
#endif
#ifndef CCAPI_HUOBI_API_KEY
#define CCAPI_HUOBI_API_KEY "HUOBI_API_KEY"
#endif
#ifndef CCAPI_HUOBI_API_SECRET
#define CCAPI_HUOBI_API_SECRET "HUOBI_API_SECRET"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_API_KEY
#define CCAPI_HUOBI_USDT_SWAP_API_KEY "HUOBI_USDT_SWAP_API_KEY"
#endif
#ifndef CCAPI_HUOBI_USDT_SWAP_API_SECRET
#define CCAPI_HUOBI_USDT_SWAP_API_SECRET "HUOBI_USDT_SWAP_API_SECRET"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_API_KEY
#define CCAPI_HUOBI_COIN_SWAP_API_KEY "HUOBI_COIN_SWAP_API_KEY"
#endif
#ifndef CCAPI_HUOBI_COIN_SWAP_API_SECRET
#define CCAPI_HUOBI_COIN_SWAP_API_SECRET "HUOBI_COIN_SWAP_API_SECRET"
#endif
#ifndef CCAPI_OKEX_API_KEY
#define CCAPI_OKEX_API_KEY "OKEX_API_KEY"
#endif
#ifndef CCAPI_OKEX_API_SECRET
#define CCAPI_OKEX_API_SECRET "OKEX_API_SECRET"
#endif
#ifndef CCAPI_OKEX_API_PASSPHRASE
#define CCAPI_OKEX_API_PASSPHRASE "OKEX_API_PASSPHRASE"
#endif
#ifndef CCAPI_OKEX_API_X_SIMULATED_TRADING
#define CCAPI_OKEX_API_X_SIMULATED_TRADING "OKEX_API_X_SIMULATED_TRADING"
#endif
#ifndef CCAPI_ERISX_API_KEY
#define CCAPI_ERISX_API_KEY "ERISX_API_KEY"
#endif
#ifndef CCAPI_ERISX_API_SECRET
#define CCAPI_ERISX_API_SECRET "ERISX_API_SECRET"
#endif
#ifndef CCAPI_KUCOIN_API_KEY
#define CCAPI_KUCOIN_API_KEY "KUCOIN_API_KEY"
#endif
#ifndef CCAPI_KUCOIN_API_SECRET
#define CCAPI_KUCOIN_API_SECRET "KUCOIN_API_SECRET"
#endif
#ifndef CCAPI_KUCOIN_API_PASSPHRASE
#define CCAPI_KUCOIN_API_PASSPHRASE "KUCOIN_API_PASSPHRASE"
#endif
#ifndef CCAPI_KUCOIN_API_KEY_VERSION
#define CCAPI_KUCOIN_API_KEY_VERSION "KUCOIN_API_KEY_VERSION"
#endif
#ifndef CCAPI_KUCOIN_FUTURES_API_KEY
#define CCAPI_KUCOIN_FUTURES_API_KEY "KUCOIN_FUTURES_API_KEY"
#endif
#ifndef CCAPI_KUCOIN_FUTURES_API_SECRET
#define CCAPI_KUCOIN_FUTURES_API_SECRET "KUCOIN_FUTURES_API_SECRET"
#endif
#ifndef CCAPI_KUCOIN_FUTURES_API_PASSPHRASE
#define CCAPI_KUCOIN_FUTURES_API_PASSPHRASE "KUCOIN_FUTURES_API_PASSPHRASE"
#endif
#ifndef CCAPI_KUCOIN_FUTURES_API_KEY_VERSION
#define CCAPI_KUCOIN_FUTURES_API_KEY_VERSION "KUCOIN_FUTURES_API_KEY_VERSION"
#endif
#ifndef CCAPI_FTX_API_KEY
#define CCAPI_FTX_API_KEY "FTX_API_KEY"
#endif
#ifndef CCAPI_FTX_API_SECRET
#define CCAPI_FTX_API_SECRET "FTX_API_SECRET"
#endif
#ifndef CCAPI_FTX_API_SUBACCOUNT
#define CCAPI_FTX_API_SUBACCOUNT "FTX_API_SUBACCOUNT"
#endif
#ifndef CCAPI_FTX_US_API_KEY
#define CCAPI_FTX_US_API_KEY "FTX_US_API_KEY"
#endif
#ifndef CCAPI_FTX_US_API_SECRET
#define CCAPI_FTX_US_API_SECRET "FTX_US_API_SECRET"
#endif
#ifndef CCAPI_FTX_US_API_SUBACCOUNT
#define CCAPI_FTX_US_API_SUBACCOUNT "FTX_US_API_SUBACCOUNT"
#endif
#ifndef CCAPI_DERIBIT_CLIENT_ID
#define CCAPI_DERIBIT_CLIENT_ID "DERIBIT_CLIENT_ID"
#endif
#ifndef CCAPI_DERIBIT_CLIENT_SECRET
#define CCAPI_DERIBIT_CLIENT_SECRET "DERIBIT_CLIENT_SECRET"
#endif
#ifndef CCAPI_GATEIO_API_KEY
#define CCAPI_GATEIO_API_KEY "GATEIO_API_KEY"
#endif
#ifndef CCAPI_GATEIO_API_SECRET
#define CCAPI_GATEIO_API_SECRET "GATEIO_API_SECRET"
#endif
#ifndef CCAPI_GATEIO_PERPETUAL_FUTURES_API_KEY
#define CCAPI_GATEIO_PERPETUAL_FUTURES_API_KEY "GATEIO_PERPETUAL_FUTURES_API_KEY"
#endif
#ifndef CCAPI_GATEIO_PERPETUAL_FUTURES_API_SECRET
#define CCAPI_GATEIO_PERPETUAL_FUTURES_API_SECRET "GATEIO_PERPETUAL_FUTURES_API_SECRET"
#endif
#ifndef CCAPI_CRYPTOCOM_API_KEY
#define CCAPI_CRYPTOCOM_API_KEY "CRYPTOCOM_API_KEY"
#endif
#ifndef CCAPI_CRYPTOCOM_API_SECRET
#define CCAPI_CRYPTOCOM_API_SECRET "CRYPTOCOM_API_SECRET"
#endif
#ifndef CCAPI_BYBIT_API_KEY
#define CCAPI_BYBIT_API_KEY "BYBIT_API_KEY"
#endif
#ifndef CCAPI_BYBIT_API_SECRET
#define CCAPI_BYBIT_API_SECRET "BYBIT_API_SECRET"
#endif
// #ifndef CCAPI_BYBIT_USDT_PERPETUAL_API_KEY
// #define CCAPI_BYBIT_USDT_PERPETUAL_API_KEY "BYBIT_USDT_PERPETUAL_API_KEY"
// #endif
// #ifndef CCAPI_BYBIT_USDT_PERPETUAL_API_SECRET
// #define CCAPI_BYBIT_USDT_PERPETUAL_API_SECRET "BYBIT_USDT_PERPETUAL_API_SECRET"
// #endif
// #ifndef CCAPI_BYBIT_INVERSE_PERPETUAL_API_KEY
// #define CCAPI_BYBIT_INVERSE_PERPETUAL_API_KEY "BYBIT_INVERSE_PERPETUAL_API_KEY"
// #endif
// #ifndef CCAPI_BYBIT_INVERSE_PERPETUAL_API_SECRET
// #define CCAPI_BYBIT_INVERSE_PERPETUAL_API_SECRET "BYBIT_INVERSE_PERPETUAL_API_SECRET"
// #endif
#ifndef CCAPI_ASCENDEX_API_KEY
#define CCAPI_ASCENDEX_API_KEY "ASCENDEX_API_KEY"
#endif
#ifndef CCAPI_ASCENDEX_API_SECRET
#define CCAPI_ASCENDEX_API_SECRET "ASCENDEX_API_SECRET"
#endif
#ifndef CCAPI_ASCENDEX_API_ACCOUNT_GROUP
#define CCAPI_ASCENDEX_API_ACCOUNT_GROUP "ASCENDEX_API_ACCOUNT_GROUP"
#endif
// end: exchange API credentials

#define CCAPI_HTTP_PORT_DEFAULT "80"
#define CCAPI_HTTPS_PORT_DEFAULT "443"
#ifndef CCAPI_BITMEX_API_RECEIVE_WINDOW_SECONDS
#define CCAPI_BITMEX_API_RECEIVE_WINDOW_SECONDS 5
#endif
#ifndef CCAPI_BITFINEX_STREAM_TRADE_RAW_MESSAGE_TYPE
#define CCAPI_BITFINEX_STREAM_TRADE_RAW_MESSAGE_TYPE "tu"
#endif
#define CCAPI_AUTHORIZATION "AUTHORIZATION"
#ifndef CCAPI_HFFIX_READ_MESSAGE_CHUNK_SIZE
#define CCAPI_HFFIX_READ_MESSAGE_CHUNK_SIZE 4096
#endif
#ifndef CCAPI_FIX_PROTOCOL_VERSION_COINBASE
#define CCAPI_FIX_PROTOCOL_VERSION_COINBASE "FIX.4.2"
#endif
#ifndef CCAPI_FIX_PROTOCOL_VERSION_GEMINI
#define CCAPI_FIX_PROTOCOL_VERSION_GEMINI "FIX.4.4"
#endif
#ifndef CCAPI_FIX_PROTOCOL_VERSION_FTX
#define CCAPI_FIX_PROTOCOL_VERSION_FTX "FIX.4.2"
#endif
#ifndef CCAPI_FIX_PROTOCOL_VERSION_FTX_US
#define CCAPI_FIX_PROTOCOL_VERSION_FTX_US "FIX.4.2"
#endif
#ifndef CCAPI_FIX_PROTOCOL_VERSION_DERIBIT
#define CCAPI_FIX_PROTOCOL_VERSION_DERIBIT "FIX.4.4"
#endif
#endif  // INCLUDE_CCAPI_CPP_CCAPI_MACRO_H_
