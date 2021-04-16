#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"
#include "orderbook.h"
#include "orderparser.h"

#define TRACE(msg)            cout << msg << endl
#define TRACE_ACTION(a, k, v) cout << a << " (" << k << ", " << v << ")" << endl

int main()
{
  OrderParser orderParser;
  OrderBook orderB;
  const std::string filename = "order.json";

  rapidjson::Document data = orderParser.orderJsonParse(filename);
  orderB.storeOrders(data);

  return 0;
}
