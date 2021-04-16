#pragma once

#include<bits/stdc++.h>
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
    rapidjson::Document parseData(std::string& filename);
    void deSerialise(rapidjson::Value& val);
    inline bool is_buy() { return (this->side == "buy") ? true: false; }
    bool order_qty();
    bool getPrice();
    long epochtime;

    Order() { epochtime = 0; }
};

rapidjson::Document Order::parseData(std::string& filename) {

  rapidjson::Document data;

  std::ifstream ifs(filename);
  rapidjson::IStreamWrapper isw(ifs);

  data.ParseStream(isw);

  return data;
}

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
void Order::deSerialise(rapidjson::Value& val) {

    this->orderId = sanitize<std::string>(val["orderId"]);//).GetString();
    this->symbol = sanitize<std::string>(val["symbol"]); // AAPL, FB, AMZN ..etc
    this->assetId = sanitize<std::string>(val["assetId"]);
    this->exchange = sanitize<std::string>(val["exchange"]);
    this->assetType = sanitize<std::string>(val["assetType"]);
    this->accountId = sanitize<std::string>(val["accountId"]);
    this->portfolioId = sanitize<std::string>(val["portfolioId"]);//.GetString() ;
    this->side = sanitize<std::string>(val["side"]); // order: buy/sell
    this->orderType = sanitize<std::string>(val["orderType"]);
    this->quantity = sanitize<double>(val["quantity"]);
    this->price = sanitize<double>(val["price"]);
    this->auxPrice = sanitize<double>(val["auxPrice"]);
    this->timeInForce = sanitize<std::string>(val["timeInForce"]);
    this->stopPrice = sanitize<double>(val["stopPrice"]);
    this->routing = sanitize<std::string>(val["routing"]);
    this->parentOrderId = sanitize<std::string>(val["parentOrderId"]);
    this->bulkOrderId = sanitize<std::string>(val["bulkOrderId"]);
    this->status = sanitize<int>(val["status"]) ;
    this->altOrderId = sanitize<std::string>(val["altOrderId"]);
    this->rebalanceId = sanitize<std::string>(val["rebalanceId"]);
    this->modelId = sanitize<std::string>(val["modelId"]);
    this->orderTime = sanitize<std::string>(val["orderTime"]);
    this->updateDate = sanitize<std::string>(val["updateDate"]);
}
