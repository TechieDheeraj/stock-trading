#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"
#include "orderbook.h"
#include "marketData.h"
#include "matchingEngine.h"
#include "logger.h"

void MatchingEngine::matchOrders(rapidjson::Document& data, OrderBook& orderB) {

  auto logger = LogClass::getLogger();

  for(rapidjson::Value &val: data.GetArray()) {
    MarketData market_data;
    market_data.deserialiser(val);
    SPDLOG_LOGGER_INFO(logger, "Market stock is {}, price {} ", market_data.symbol, market_data.price);
    std::priority_queue<Order, std::vector<Order>, OrderComparator> *buyOrders = nullptr; 
    std::priority_queue<Order, std::vector<Order>, OrderComparator> *sellOrders = nullptr; 
    bool fBuyOrders = false;
    bool fSellOrders = false;

    // check buy orders from orderbook
    if (orderB.buyOrders.find(market_data.symbol) != orderB.buyOrders.end()) {
      auto &orders = orderB.buyOrders[market_data.symbol]; 
      if (orders.find(market_data.price) != orders.end()) {
        buyOrders = &orders[market_data.price];
        fBuyOrders = true;
      }
    }

    if (!fBuyOrders)
      continue;

    // check sell orders from orderbook
    if (orderB.sellOrders.find(market_data.symbol) != orderB.sellOrders.end()) {
      auto &orders = orderB.sellOrders[market_data.symbol]; 
      if (orders.find(market_data.price) != orders.end()) {
        sellOrders = &orders[market_data.price];
        fSellOrders = true;
      }
    }
    if (!fSellOrders)
      continue;

    while(!buyOrders->empty() && !sellOrders->empty()) {

      double bqty = buyOrders->top().quantity;
      double sqty = sellOrders->top().quantity;

      SPDLOG_LOGGER_INFO(logger, "Buyer qty: {:03.2f} seller qty: {:03.2f}", bqty, sqty);

      double diff = bqty-sqty;
      if (diff == 0.0) {
        SPDLOG_LOGGER_INFO(logger, "[Buyer] Order ID: {}, Executed order of quantity: {:03.2f}", buyOrders->top().orderId, bqty);
        SPDLOG_LOGGER_INFO(logger, "[Seller] Order ID: {}, Executed order of quantity: {:03.2f}", sellOrders->top().orderId, bqty);
        orderB.orderMetaData.erase(buyOrders->top().orderId);
        orderB.orderMetaData.erase(sellOrders->top().orderId);
        buyOrders->pop();
        sellOrders->pop();
      } else if (diff < 0) { // seller has more quantity
        // sell shares and pop buyer from queue and drop event 
        SPDLOG_LOGGER_INFO(logger, "[Buyer] Order ID: {}, Executed order of quantity: {:03.2f}", buyOrders->top().orderId, bqty);
        SPDLOG_LOGGER_INFO(logger, "[Seller] Order ID: {}, Executed order of quantity: {:03.2f}", sellOrders->top().orderId, bqty);
        SPDLOG_LOGGER_INFO(logger, "Seller {} sold shares to buyer {} of qty: {:03.2f}", sellOrders->top().orderId, buyOrders->top().orderId, bqty);
        orderB.orderMetaData.erase(buyOrders->top().orderId);
        buyOrders->pop();

        // TODO: If quantity is used in comparator then first pop and repush the data rather than writing directly
      //  auto ptr = (Order *)&sellOrders->top();
        auto sellObj = sellOrders->top(); sellOrders->pop();
        sqty = sellObj.quantity = abs(diff);
        sellOrders->push(sellObj);

        //sqty = ptr->quantity = abs(diff);  
      } else if (diff > 0) { // buyer has more quantity
        // sell shares and pop buyer from queue and drop event 
        SPDLOG_LOGGER_INFO(logger, "[Buyer] Order ID: {}, Executed order of quantity: {:03.2f}", buyOrders->top().orderId, sqty);
        SPDLOG_LOGGER_INFO(logger, "[Seller] Order ID: {}, Executed order of quantity: {:03.2f}", sellOrders->top().orderId, sqty);
        SPDLOG_LOGGER_INFO(logger, "Buyer {} bought shares from seller {} of qty: {:03.2f}", buyOrders->top().orderId, sellOrders->top().orderId, sqty);
        orderB.orderMetaData.erase(sellOrders->top().orderId);
        sellOrders->pop();

        // TODO: If quantity is used in comparator then first pop and repush the data rather than writing directly
       // auto ptr = (Order *)&buyOrders->top();
        //bqty = *(Order *)&buyOrders->top()->quantity = abs(diff);  
        //bqty = ptr->quantity = abs(diff);  
        auto buyObj = buyOrders->top(); buyOrders->pop();
        bqty = buyObj.quantity = abs(diff);
        buyOrders->push(buyObj);
      }
    }
  }
}
