cmake_minimum_required(VERSION 3.5)
project(cworld)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/third_party/rapidjson/include)

add_executable(cworld main.cpp)
