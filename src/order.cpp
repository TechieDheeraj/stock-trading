
#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"

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
