#pragma once
#include <bits/stdc++.h>
#include <cstdio>
#include <httplib.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"
#include "orderbook.h"
#include "matchingEngine.h"
#include "logger.h"

class TradingApp {
  private:
    std::string ip_addr;
    uint16_t port;

  public:
    TradingApp(const std::string& ip="127.0.0.1", uint16_t port=8080);
    ~TradingApp();
    void start(OrderBook& ob);
    std::string getOrders(OrderBook& ob, const std::string& orderId);
    void putOrder(OrderBook& ob, const std::string& orderId);
    void uploadOrders(OrderBook& ob, const std::string& body);
    void uploadPrice(OrderBook& ob, const std::string& body);
    std::string log(const httplib::Request &req, const httplib::Response &res);
};
