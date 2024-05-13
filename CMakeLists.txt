cmake_minimum_required(VERSION 3.5)
project(cworld)

set(CMAKE_CXX_STANDARD 11)

#set(CMAKE_SYSTEM_NAME iOS)
#set(CMAKE_OSX_ARCHITECTURES arm64 armv7)

include_directories(${CMAKE_SOURCE_DIR}/third_party/rapidjson/include)

add_executable(cworld main.cpp earthmap.cpp utility.cpp)

#add_library(cworld STATIC earthmap.cpp utility.cpp)

target_compile_options(cworld PRIVATE -Wall -Wextra)
