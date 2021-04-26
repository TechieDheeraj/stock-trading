#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"
#include "marketData.h"

void MarketData::deserialiser(rapidjson::Value &val)
{
  this->symbol = sanitize<std::string>(val["symbol"]);
  this->assetId = sanitize<std::string>(val["assetId"]);
  this->exchange = sanitize<std::string>(val["exchange"]);
  this->price = sanitize<double>(val["price"]);
}
