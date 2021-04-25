#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

std::string Order::serialise() {

  rapidjson::StringBuffer s;
  rapidjson::Writer<rapidjson::StringBuffer> writer(s);

  writer.StartObject();

  writer.Key("orderId"); writer.String(this->orderId.c_str());
  writer.Key("symbol"); writer.String(this->symbol.c_str());
  writer.Key("assetId"); writer.String(this->assetId.c_str());
  writer.Key("exchange"); writer.String(this->exchange.c_str());
  writer.Key("assetType"); writer.String(this->assetType.c_str());
  writer.Key("accountId"); writer.String(this->accountId.c_str());
  writer.Key("portfolioId"); writer.String(this->portfolioId.c_str());
  writer.Key("side"); writer.String(this->side.c_str());
  writer.Key("orderType"); writer.String(this->orderType.c_str());
  writer.Key("quantity"); writer.Double(this->quantity);
  writer.Key("price"); writer.Double(this->price);
  writer.Key("auxPrice"); writer.Double(this->auxPrice);
  writer.Key("timeInForce"); writer.String(this->timeInForce.c_str());
  writer.Key("stopPrice"); writer.Double(this->stopPrice);
  writer.Key("routing"); writer.String(this->routing.c_str());
  writer.Key("parentOrderId"); writer.String(this->parentOrderId.c_str());
  writer.Key("bulkOrderId"); writer.String(this->bulkOrderId.c_str());
  writer.Key("status"); writer.Uint(this->status);
  writer.Key("altOrderId"); writer.String(this->altOrderId.c_str());
  writer.Key("rebalanceId"); writer.String(this->rebalanceId.c_str());
  writer.Key("modelId"); writer.String(this->modelId.c_str());
  writer.Key("orderTime"); writer.String(this->orderTime.c_str());
  writer.Key("updateDate"); writer.String(this->updateDate.c_str());

  writer.EndObject();

  return s.GetString();
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
