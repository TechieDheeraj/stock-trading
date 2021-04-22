#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"
#include "orderbook.h"
#include "marketData.h"
#include "matchingEngine.h"
#include "logger.h"

extern std::ofstream ofs;

void MatchingEngine::matchOrders(rapidjson::Document& data, OrderBook& orderB) {

  for(rapidjson::Value &val: data.GetArray()) {
    MarketData market_data;
    market_data.deserialiser(val);
    LOG(INFO, ofs) << " market stock is " << market_data.symbol << " price " << market_data.price << std::endl;
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

      LOG(INFO,ofs)  << " buyer qty:  " << bqty << " seller qty " << sqty << std::endl;

      double diff = bqty-sqty;
      if (diff == 0.0) {
        LOG(INFO,ofs) << "Order ID: " << buyOrders->top().orderId.c_str() << " Executed order of quantity: " <<  bqty << std::endl;
        //TRACE_ACTION(sellOrders->top().orderId.c_str(), sqty);
        buyOrders->pop();
        sellOrders->pop();
      } else if (diff < 0) { // seller has more quantity
        // sell shares and pop buyer from queue and drop event 
        LOG(INFO,ofs) << " Buyer " << buyOrders->top().orderId.c_str() << std::endl;
        LOG(INFO,ofs) << " Seller " << sellOrders->top().orderId.c_str() << std::endl;
        LOG(INFO,ofs) << "[Buyer] Order ID: " << buyOrders->top().orderId.c_str() << " Executed order of quantity: " <<  bqty << std::endl;
        LOG(INFO,ofs) << "[Seller] Order ID: " << sellOrders->top().orderId.c_str() << " Executed order of quantity: " <<  bqty << std::endl;
        //TRACE_ACTION(buyOrders->top().orderId.c_str(), bqty);
       // TRACE_ACTION(sellOrders->top().orderId.c_str(), bqty); // bqty because seller could sell only bqties
        LOG(INFO,ofs) << " seller sold shares to buyers of qty: " << bqty << std::endl;
        buyOrders->pop();

        // TODO: If quantity is used in comparator then first pop and repush the data rather than writing directly
      //  auto ptr = (Order *)&sellOrders->top();
        auto sellObj = sellOrders->top(); sellOrders->pop();
        sqty = sellObj.quantity = abs(diff);
        sellOrders->push(sellObj);

        //sqty = ptr->quantity = abs(diff);  
      } else if (diff > 0) { // buyer has more quantity
        // sell shares and pop buyer from queue and drop event 
        LOG(INFO,ofs) << " Buyer " << buyOrders->top().orderId.c_str() << std::endl;
        LOG(INFO,ofs) << " Seller " << sellOrders->top().orderId.c_str() << std::endl;
        LOG(INFO,ofs) << "[Buyer] Order ID: " << buyOrders->top().orderId.c_str() << " Executed order of quantity: " <<  sqty << std::endl;
        LOG(INFO,ofs) << "[Seller] Order ID: " << sellOrders->top().orderId.c_str() << " Executed order of quantity: " <<  sqty << std::endl;
        //TRACE_ACTION(sellOrders->top().orderId.c_str(), sqty);
        //TRACE_ACTION(buyOrders->top().orderId.c_str(), sqty); // sqty because buyer could buy only sqties
        LOG(INFO,ofs) << "Buyer bought shares from sellers of qty " << sqty << std::endl;
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
