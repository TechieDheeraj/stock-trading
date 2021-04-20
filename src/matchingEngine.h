#pragma once

#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"
#include "orderbook.h"
#include "marketData.h"

#define TRACE_ACTION(i, q) std::cout << "Order ID: " << i << " Executed order of quantity: " << q << std::endl// << std::setprecision(3) << q << std::endl

class MatchingEngine {
  public:
    MatchingEngine() {}
    void matchOrders(rapidjson::Document& data, OrderBook& orderB);   
};
