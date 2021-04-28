#include <bits/stdc++.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "order.h"
#include "orderbook.h"
#include "orderparser.h"
#include "matchingEngine.h"
#include "logger.h"
#include <httplib.h>
#include "app.h"

TradingApp::TradingApp(const std::string& ip, uint16_t port):ip_addr(ip), port(port) { }

TradingApp::~TradingApp() {}

std::string TradingApp::getOrders(OrderBook& ob, const std::string& orderId) {

  std::string response = "";
  Order orderData = ob.searchOrder(orderId);

  if (orderData.getOrderId() == "")
    return response;

  response = orderData.serialise();
  return response;
}

void TradingApp::putOrder(OrderBook& ob, const std::string& orderId) {
}

void TradingApp::uploadOrders(OrderBook& ob, const std::string& body) {
  OrderParser orderparser;

  auto logger = LogClass::getLogger();

  if (body.length() == 0)
    return;

  SPDLOG_LOGGER_INFO(logger, "Orders are getting uploaded... ");
  
  rapidjson::Document data = orderparser.orderJsonParse(body.c_str());

  ob.storeOrders(data);
}

void TradingApp::uploadPrice(OrderBook& ob, const std::string& body) {
  OrderParser orderparser;
  MatchingEngine matchE;

  auto logger = LogClass::getLogger();

  if (body.length() == 0)
    return;

  SPDLOG_LOGGER_INFO(logger, "Price is getting uploaded... ");

  rapidjson::Document data = orderparser.orderJsonParse(body.c_str());
  matchE.matchOrders(data, ob);
}

std::string dump_headers(const httplib::Headers &headers) {
  std::string s;
  char buf[BUFSIZ];

  for (const auto &x : headers) {
    snprintf(buf, sizeof(buf), "%s: %s\n", x.first.c_str(), x.second.c_str());
    s += buf;
  }

  return s;
}

std::string TradingApp::log(const httplib::Request &req, const httplib::Response &res) {

  std::string s;
  char buf[BUFSIZ];

  s += "================================\n";

  snprintf(buf, sizeof(buf), "%s %s %s", req.method.c_str(),
           req.version.c_str(), req.path.c_str());
  s += buf;

  std::string query;
  for (auto it = req.params.begin(); it != req.params.end(); ++it) {
    const auto &x = *it;
    snprintf(buf, sizeof(buf), "%c%s=%s",
             (it == req.params.begin()) ? '?' : '&', x.first.c_str(),
             x.second.c_str());
    query += buf;
  }
  snprintf(buf, sizeof(buf), "%s\n", query.c_str());
  s += buf;

  s += dump_headers(req.headers);

  s += "--------------------------------\n";

  snprintf(buf, sizeof(buf), "%d\n", res.status);
  s += buf;
  s += dump_headers(res.headers);

  return s;
}

void TradingApp::start(OrderBook& ob) {

  httplib::Server svr;
  
  svr.Post("/ome/orders", [&](const httplib::Request &req, httplib::Response &res) {
    std::cout << "Market Orders " << req.body << std::endl;

    this->uploadOrders(ob, req.body);
    auto body = dump_headers(req.headers);
    res.set_content(body, "text/plain");
  });

  svr.Post("/ome/price", [&](const httplib::Request &req, httplib::Response &res) {
    std::cout << "Market Price " << req.body << std::endl;

    this->uploadPrice(ob, req.body);
    auto body = dump_headers(req.headers);
    res.set_content(body, "text/plain");
  });

  svr.Get(R"(/ome/orders/(.*))", [&](const httplib::Request &req, httplib::Response &res) {
    auto response = this->getOrders(ob, req.matches[1]);
    if (response == "") {
      res.status = 404;
      response += "Order: " + req.matches.str(1) + " not found";
    }
    res.set_content(response, "application/json");
  });

  svr.Get("/stop",
    [&](const httplib::Request & /*req*/, httplib::Response & /*res*/) { svr.stop(); });

  svr.set_error_handler([](const httplib::Request & /*req*/, httplib::Response &res) {
    //const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
    const char *fmt = "{\"Error Status\":%d, \"Error Message\": \"%s\" }";
    char buf[BUFSIZ];
    snprintf(buf, sizeof(buf), fmt, res.status, res.body.c_str());
    res.set_content(buf, "application/json");
  });

  svr.set_logger(
      [&](const httplib::Request &req, const httplib::Response &res) { std::cout << log(req, res); });

  auto port = 8080;

  auto base_dir = "./";

  if (!svr.set_mount_point("/", base_dir)) {
    std::cout << "The specified base directory doesn't exist...";
    return;
  }

  std::cout << "The server started at port " << port << "..." << std::endl;

  svr.listen(ip_addr.c_str(), port);
}
