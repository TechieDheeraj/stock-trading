#pragma once

#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

class Order {
  private:
    std::string orderId;
    std::string symbol; // AAPL, FB, AMZN ..etc
    std::string assetId;
    std::string exchange;
    std::string assetType;
    std::string accountId;
    std::string portfolioId;
    std::string side; // order: buy/sell
    std::string orderType;
    double quantity;
    double price;
    double auxPrice;
    std::string timeInForce;
    double stopPrice;
    std::string routing;
    std::string parentOrderId;
    std::string bulkOrderId;
    int status;
    std::string altOrderId;
    std::string rebalanceId;
    std::string modelId;
    std::string orderTime;
    std::string updateDate;

  public:
    friend class OrderBook;
    friend class MatchingEngine;
    void deSerialise(rapidjson::Value& val);
    inline bool is_buy() { return (this->side == "buy") ? true: false; }
    bool order_qty();
    bool getPrice();
    long epochtime;

    Order() { epochtime = 0; }
};

template<typename T> inline T sanitize(rapidjson::Value& v) {}
template<>
inline std::string sanitize<std::string>(rapidjson::Value& v) {
  return v.IsNull() ? "" : v.GetString();
}
template<>
inline double sanitize<double>(rapidjson::Value& v) {
  return v.IsNull() ? 0.0 : v.GetDouble();
}
template<>
inline int sanitize<int>(rapidjson::Value& v) {
  return v.IsNull() ? 0 : v.GetInt();
}
