#pragma once

#include <bits/stdc++.h>
#include <ctime>
#include <iomanip>

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)    // only show filename and not it's path (less clutter)
#define INFO(f) f << std::put_time(std::localtime(&time_now), "%y-%m-%d %OH:%OM:%OS") << " [INFO] " << __FILENAME__ << "(" << __FUNCTION__ << ":" << __LINE__ << ") == "
#define ERROR(f) f << std::put_time(std::localtime(&time_now), "%y-%m-%d %OH:%OM:%OS") << " [ERROR] " << __FILENAME__ << "(" << __FUNCTION__ << ":" << __LINE__ << ") == "
#define LOG(t, f) t(f)

static std::time_t time_now = std::time(nullptr);
 
const std::string logFile = "orders.log";

class Logger {
  private:
    const std::string filename = "orders.log";
    //static ofstream ofs;

  public:
    template<typename ...Args>
   // static void LOG(Args...args);
    static void setStream(std::ofstream& ofs);
};
