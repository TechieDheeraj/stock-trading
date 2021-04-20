#pragma once

#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

class OrderParser {
  
  public:
    OrderParser() {}
    rapidjson::Document orderJsonParse(const std::string& filename);
};
