#include <bits/stdc++.h>
#include "logger.h"

const std::string logger_name = "file_logger";
const std::string log_dir = "../logs/";
const std::string logfile = "orders.log";

inline std::string LogClass::loggerName() {
  return logger_name;
}

inline std::string LogClass::fileName() {
  return log_dir+logfile;
}

void LogClass::testLog() {
  m_logger->info("Testing log\n");
}

LogClass::LogClass() {
  m_logger = spdlog::basic_logger_mt(LogClass::loggerName(), LogClass::fileName());
  //spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] [source %@] [function %!] %v");
  //spdlog::set_default_logger(m_logger);
  m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] [%@] [%!] %v");

}

LogClass::~LogClass() {
}

std::shared_ptr<spdlog::logger> LogClass::getLogger() {
  return spdlog::get(LogClass::loggerName());
  //return m_logger;
}

void LogClass::register_logger(std::shared_ptr<spdlog::logger> logger) {
  spdlog::register_logger(logger);
}
