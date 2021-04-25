#pragma once

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

    // map for storing metadata: key <orderID> and Value <Name, side, price>
    std::unordered_map<std::string, std::tuple<std::string, std::string, double>> orderMetaData; // takes orderId and returns price and name
    std::unordered_map<std::string, std::unordered_map<double, std::priority_queue<Order, std::vector<Order>, OrderComparator>>> buyOrders;
    std::unordered_map<std::string, std::unordered_map<double, std::priority_queue<Order, std::vector<Order>, OrderComparator>>> sellOrders;

    Order searchOrder(const std::string& orderId);
    void storeOrders(rapidjson::Document& order_data); 
    inline void storeOrder(rapidjson::Value& v);
};
