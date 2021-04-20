#include <bits/stdc++.h>
#include "order.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include <locale>
#include <iomanip>
#include "orderbook.h"

void OrderBook::storeOrders(rapidjson::Document& data) {

  for (rapidjson::Value &v: data.GetArray()) {

    Order orderObj; // create object and fill with data
    orderObj.deSerialise(v);

    std::tm t = {};
    std::istringstream ss(orderObj.orderTime);

    if (ss >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S")) {
      orderObj.epochtime = std::mktime(&t);
    }

    if (orderObj.is_buy()) {
      this->buyOrders[orderObj.symbol][orderObj.price].push(orderObj);
    } else {
      this->sellOrders[orderObj.symbol][orderObj.price].push(orderObj);
    }
  }
  std::cout << "Orders are stored " << std::endl;

  /*
  std::cout  << " Buying orders " << std::endl;
  for(auto& [company, ordersMap]: buyOrders) {
    for(auto& [price, pq] : ordersMap) {
      while(!pq.empty()) {
        auto tmp = pq.top(); pq.pop();
        std::cout << "company " << tmp.symbol << "price " << tmp.price <<  " tmp.epochtime " << tmp.epochtime << std::endl; 
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
std::cout << " Selling orders " << std::endl;
  for(auto& [company, ordersMap]: sellOrders) {
    for(auto& [price, pq] : ordersMap) {
      while(!pq.empty()) {
        auto tmp = pq.top(); pq.pop();
        std::cout << "company " << tmp.symbol << "price " << tmp.price <<  " tmp.epochtime " << tmp.epochtime << std::endl; 
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  */
}
