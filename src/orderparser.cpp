#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "orderparser.h"

rapidjson::Document OrderParser::orderJsonParse(const std::string& filename) {

  rapidjson::Document data;

  std::ifstream ifs(filename);
  rapidjson::IStreamWrapper isw(ifs);

  data.ParseStream(isw);

  return data;
}
