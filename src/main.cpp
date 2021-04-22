#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"
#include "orderbook.h"
#include "orderparser.h"
#include "matchingEngine.h"

int main()
{
  OrderParser orderParser;
  OrderBook orderB;
  MatchingEngine matchE;

  const std::string orderFile = "order.json";
  const std::string priceFile = "price.json";

  rapidjson::Document orderData = orderParser.orderJsonParse(orderFile);
  orderB.storeOrders(orderData);
  rapidjson::Document marketData = orderParser.orderJsonParse(priceFile);
  matchE.matchOrders(marketData, orderB);

  return 0;
}
