cmake_minimum_required(VERSION 3.0.0)
project(stock-trading VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MAKE_PROGRAM "make")

add_subdirectory(src/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
