cmake_minimum_required(VERSION 3.0.0)
project(stock-trading VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

file(GLOB SrcFiles
     "*.h"
     "*.cpp"
)

add_executable(stock-trading ${SrcFiles})
target_include_directories(stock-trading PUBLIC ../include)
target_compile_options(stock-trading PUBLIC "-pthread")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
