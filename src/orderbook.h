#include <bits/stdc++.h>
#include "order.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include <locale>
#include <iomanip>

struct OrderComparator {
  bool operator()(const Order& a, const Order& b) {
    return a.epochtime > b.epochtime;
  }
};

class OrderBook {
  public:
    OrderBook() {}

    std::unordered_map<std::string, std::unordered_map<double, std::priority_queue<Order, std::vector<Order>, OrderComparator>>> buyOrders;
    std::unordered_map<std::string, std::unordered_map<double, std::priority_queue<Order, std::vector<Order>, OrderComparator>>> sellOrders;

    void storeOrders(rapidjson::Document& order_data); 
};

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

}
