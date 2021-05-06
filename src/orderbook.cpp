#include <bits/stdc++.h>
#include "order.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include <locale>
#include <iomanip>
#include "orderbook.h"
#include "logger.h"
#include "priorityQueue.h"

PriorityQueue* OrderBook::searchMetaData(const std::string& orderId) {

  Order orderData;
  auto logger = LogClass::getLogger(); 
  PriorityQueue <Order, OrderComparator> *ordersPq;
  auto itr = orderMetaData.find(orderId);

  if (itr == orderMetaData.end()) {
    SPDLOG_LOGGER_INFO(logger, "Order with OrderID: {} doesn't exist", orderId);
    return nullptr;
  }

  auto orderTup = itr->second;
  std::string symbol = std::get<0>(orderTup);
  std::string side = std::get<1>(orderTup);
  double price = std::get<2>(orderTup);

  if (side == "buy") {
    ordersPq = &buyOrders[symbol][price];
  } else {
    ordersPq = &sellOrders[symbol][price];
  }

  return orderPq;
}

Order OrderBook::searchOrder(const std::string& orderId) {

  auto pq = searchMetaData(orderId);
  if (pq == nullptr) {
    return {};
  }

  pq.search(
  while(!ordersPq.empty()) {
  if (ordersPq.top().orderId == orderId) {
    orderData = ordersPq.top();
  }
  ordersPq.pop();
}

  return orderData;
}

void OrderBook::updateOrder(const std::string& orderId, rapidjson::Document& data) {

}

void OrderBook::cancelOrder(const std::string& orderId, rapidjson::Document& data) {

}

inline void OrderBook::storeOrder(rapidjson::Value& v) {

    Order orderObj; // create object and fill with data
    orderObj.deSerialise(v);

    // Storing meta data information
    std::tuple<std::string, std::string, double> orderTuple = make_tuple(orderObj.symbol, orderObj.side, orderObj.price);

    this->orderMetaData[orderObj.orderId] = orderTuple;

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

void OrderBook::storeOrders(rapidjson::Document& data) {

  auto logger = LogClass::getLogger();
  for (rapidjson::Value &v: data.GetArray()) {

    /*
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
    */

    storeOrder(v);
  }
  spdlog::info("Orders are stored ");
  SPDLOG_LOGGER_INFO(logger, "Orders are stored ");

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
