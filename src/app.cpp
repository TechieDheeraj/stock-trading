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

<<<<<<< HEAD
TradingApp::TradingApp(const std::string &ip, uint16_t port) : ip_addr(ip), port(port) {}

TradingApp::~TradingApp() {}

std::string TradingApp::getOrders(OrderBook &ob, const std::string &orderId)
{
=======
TradingApp::TradingApp(const std::string& ip, uint16_t port):ip_addr(ip), port(port) { }

TradingApp::~TradingApp() {}

std::string TradingApp::getOrders(OrderBook& ob, const std::string& orderId) {
>>>>>>> base/httpSupport

  std::string response;
  Order orderData = ob.searchOrder(orderId);

  response = orderData.serialise();
  return response;
}

<<<<<<< HEAD
void TradingApp::putOrder(OrderBook &ob, const std::string &orderId)
{
}

void TradingApp::uploadOrders(OrderBook &ob, const std::string &body)
{
=======
void TradingApp::putOrder(OrderBook& ob, const std::string& orderId) {
}

void TradingApp::uploadOrders(OrderBook& ob, const std::string& body) {
>>>>>>> base/httpSupport
  OrderParser orderparser;

  auto logger = LogClass::getLogger();

  if (body.length() == 0)
    return;

  SPDLOG_LOGGER_INFO(logger, "Orders are getting uploaded... ");
<<<<<<< HEAD

=======
  
>>>>>>> base/httpSupport
  rapidjson::Document data = orderparser.orderJsonParse(body.c_str());

  ob.storeOrders(data);
}

<<<<<<< HEAD
void TradingApp::uploadPrice(OrderBook &ob, const std::string &body)
{
=======
void TradingApp::uploadPrice(OrderBook& ob, const std::string& body) {
>>>>>>> base/httpSupport
  OrderParser orderparser;
  MatchingEngine matchE;

  auto logger = LogClass::getLogger();

  if (body.length() == 0)
    return;

  SPDLOG_LOGGER_INFO(logger, "Price is getting uploaded... ");

  rapidjson::Document data = orderparser.orderJsonParse(body.c_str());
  matchE.matchOrders(data, ob);
}

<<<<<<< HEAD
std::string dump_headers(const httplib::Headers &headers)
{
  std::string s;
  char buf[BUFSIZ];

  for (const auto &x : headers)
  {
=======
std::string dump_headers(const httplib::Headers &headers) {
  std::string s;
  char buf[BUFSIZ];

  for (const auto &x : headers) {
>>>>>>> base/httpSupport
    snprintf(buf, sizeof(buf), "%s: %s\n", x.first.c_str(), x.second.c_str());
    s += buf;
  }

  return s;
}

<<<<<<< HEAD
std::string TradingApp::log(const httplib::Request &req, const httplib::Response &res)
{
=======
std::string TradingApp::log(const httplib::Request &req, const httplib::Response &res) {
>>>>>>> base/httpSupport

  std::string s;
  char buf[BUFSIZ];

  s += "================================\n";

  snprintf(buf, sizeof(buf), "%s %s %s", req.method.c_str(),
           req.version.c_str(), req.path.c_str());
  s += buf;

  std::string query;
<<<<<<< HEAD
  for (auto it = req.params.begin(); it != req.params.end(); ++it)
  {
=======
  for (auto it = req.params.begin(); it != req.params.end(); ++it) {
>>>>>>> base/httpSupport
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

<<<<<<< HEAD
void TradingApp::start(OrderBook &ob)
{
  httplib::Server svr;

=======
void TradingApp::start(OrderBook& ob) {

  httplib::Server svr;
  
>>>>>>> base/httpSupport
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

<<<<<<< HEAD
  svr.Get(R"(/ome/orders/([0-9a-zA-Z_-]+))", [&](const httplib::Request &req, httplib::Response &res) {
=======
  svr.Get(R"(/ome/orders/(.*))", [&](const httplib::Request &req, httplib::Response &res) {
>>>>>>> base/httpSupport
    auto response = this->getOrders(ob, req.matches[1]);
    res.set_content(response, "application/json");
  });

  svr.Get("/stop",
<<<<<<< HEAD
          [&](const httplib::Request & /*req*/, httplib::Response & /*res*/) { svr.stop(); });
=======
    [&](const httplib::Request & /*req*/, httplib::Response & /*res*/) { svr.stop(); });
>>>>>>> base/httpSupport

  svr.set_error_handler([](const httplib::Request & /*req*/, httplib::Response &res) {
    const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
    char buf[BUFSIZ];
    snprintf(buf, sizeof(buf), fmt, res.status);
    res.set_content(buf, "text/html");
  });

  svr.set_logger(
      [&](const httplib::Request &req, const httplib::Response &res) { std::cout << log(req, res); });

  auto port = 8080;

  auto base_dir = "./";

<<<<<<< HEAD
  if (!svr.set_mount_point("/", base_dir))
  {
=======
  if (!svr.set_mount_point("/", base_dir)) {
>>>>>>> base/httpSupport
    std::cout << "The specified base directory doesn't exist...";
    return;
  }

  std::cout << "The server started at port " << port << "..." << std::endl;

  svr.listen(ip_addr.c_str(), port);
}
