#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"
#include "orderbook.h"
#include "orderparser.h"
#include "matchingEngine.h"
#include "logger.h"

std::ofstream ofs;

int main()
{
  OrderParser orderParser;
  OrderBook orderB;
  MatchingEngine matchE;

  //const std::string logFile = "orders.log";

  ofs.open(logFile);
  //LOG::setStream(ofs);

  const std::string orderFile = "order.json";
  const std::string priceFile = "price.json";

  LOG(INFO, ofs) << "============= Welcome to Stock Trading APP ============= \n " << std::endl;
  std::cout << "============= Welcome to Stock Trading APP ============= \n" << std::endl;
  rapidjson::Document orderData = orderParser.orderJsonParse(orderFile);
  std::cout << "\tUser Orders has been loaded " << std::endl;
  LOG(INFO, ofs) << "User Orders has been loaded " << std::endl;
  orderB.storeOrders(orderData);
  std::cout << "\tUser Orders has been processed " << std::endl;
  LOG(INFO, ofs) << "User Orders has been processed " << std::endl;
  rapidjson::Document marketData = orderParser.orderJsonParse(priceFile);
  std::cout << "\tMarket Stream has been processed \n" << std::endl;
  LOG(INFO, ofs) << "Market Stream has been processed " << std::endl;

  matchE.matchOrders(marketData, orderB);

  LOG(INFO, ofs) << "============= Thanks for using Stock Trading APP ============= \n" << std::endl;
  std::cout << "============= Thanks for using Stock Trading APP ============= \n" << std::endl;
  ofs.close();

  return 0;
}
