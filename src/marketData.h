#pragma once

#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"

class MarketData
{
private:
  std::string symbol; // AAPL, FB, AMZN ..etc
  std::string assetId;
  std::string exchange;
  double price;

public:
  friend class MatchingEngine;
  MarketData() {}
  void deserialiser(rapidjson::Value &val);
};
