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

    std::unordered_map<std::string, std::unordered_map<double, std::priority_queue<Order, std::vector<Order>, OrderComparator>>> buyOrders;
    std::unordered_map<std::string, std::unordered_map<double, std::priority_queue<Order, std::vector<Order>, OrderComparator>>> sellOrders;

    void storeOrders(rapidjson::Document& order_data); 
};
