#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using Writer = rapidjson::Writer<rapidjson::StringBuffer>;

template <typename T>
struct data {
  std::string first;
  T second;

  data(const std::string &a, const T &b) : first(a), second(b)
  {
  }
};

void helper(Writer &writer, const data<std::string> &p) {
  writer.Key(p.first.c_str());
  writer.String(p.second.c_str());
}
void helper(Writer &writer, const data<double> &p) {
  writer.Key(p.first.c_str());
  writer.Double(p.second);
}
void helper(Writer &writer, const data<int> &p) {
  writer.Key(p.first.c_str());
  writer.Int(p.second);
}

template <typename... ValueTypes>
std::string GenerateJSON(const ValueTypes &...pairs) {
  rapidjson::StringBuffer s;
  rapidjson::Writer<rapidjson::StringBuffer> writer(s);

  writer.StartObject();
  (helper(writer, pairs), ...);
  writer.EndObject();

  return s.GetString();
}

std::string Order::serialise() {
  std::string result = GenerateJSON(
      data("orderId", this->orderId),
      data("symbol", this->symbol),
      data("assetId", this->assetId),
      data("exchange", this->exchange),
      data("assetType", this->assetType),
      data("accountId", this->accountId),
      data("portfolioId", this->portfolioId),
      data("side", this->side),
      data("orderType", this->orderType),
      data("quantity", this->quantity),
      data("price", this->price),
      data("auxPrice", this->auxPrice),
      data("timeInForce", this->timeInForce),
      data("stopPrice", this->stopPrice),
      data("routing", this->routing),
      data("parentOrderId", this->parentOrderId),
      data("bulkOrderId", this->bulkOrderId),
      data("status", this->status),
      data("altOrderId", this->altOrderId),
      data("rebalanceId", this->rebalanceId),
      data("modelId", this->modelId),
      data("orderTime", this->orderTime),
      data("updateDate", this->updateDate));
  return result;
}

void Order::deSerialise(rapidjson::Value& val) {

    this->orderId = sanitize<std::string>(val["orderId"]);
    this->symbol = sanitize<std::string>(val["symbol"]); // AAPL, FB, AMZN ..etc
    this->assetId = sanitize<std::string>(val["assetId"]);
    this->exchange = sanitize<std::string>(val["exchange"]);
    this->assetType = sanitize<std::string>(val["assetType"]);
    this->accountId = sanitize<std::string>(val["accountId"]);
    this->portfolioId = sanitize<std::string>(val["portfolioId"]);
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

std::string Order::getOrderId() {
  return orderId;
}
