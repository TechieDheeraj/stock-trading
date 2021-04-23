#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"
#include "orderbook.h"
#include "orderparser.h"
#include "matchingEngine.h"
#include "logger.h"

int main()
{
  OrderParser orderParser;
  OrderBook orderB;
  MatchingEngine matchE;
  LogClass logObj;
  auto logger = logObj.getLogger();

  const std::string orderFile = "order.json";
  const std::string priceFile = "price.json";

  spdlog::info("============= Welcome to Stock Trading APP =============\n");
  SPDLOG_LOGGER_INFO(logger, "============= Welcome to Stock Trading APP =============\n");
  rapidjson::Document orderData = orderParser.orderJsonParse(orderFile);
  spdlog::info("User Orders has been loaded ");
  SPDLOG_LOGGER_INFO(logger, "User Orders has been loaded ");
  orderB.storeOrders(orderData);
  spdlog::info("User Orders has been processed");
  SPDLOG_LOGGER_INFO(logger, "User Orders has been processed");
  rapidjson::Document marketData = orderParser.orderJsonParse(priceFile);
  spdlog::info("Market Stream has been processed\n");
  SPDLOG_LOGGER_INFO(logger, "Market Stream has been processed\n");
  matchE.matchOrders(marketData, orderB);
  spdlog::info(" ============= Thanks for using Stock Trading APP =============\n");
  SPDLOG_LOGGER_INFO(logger, " ============= Thanks for using Stock Trading APP =============\n");

  return 0;
}
