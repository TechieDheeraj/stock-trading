#pragma once
#ifndef LOGCLASS_H
#define LOGCLASS_H

#include <spdlog/spdlog.h>
#include "spdlog/sinks/basic_file_sink.h"

class LogClass
{

public:
  LogClass();
  ~LogClass();

  static std::string loggerName();
  static std::string fileName();
  static std::shared_ptr<spdlog::logger> getLogger();
  void register_logger(std::shared_ptr<spdlog::logger> logger);

  void testLog();

private:
  std::shared_ptr<spdlog::logger> m_logger;
};
#endif //LOGCLASS_H
