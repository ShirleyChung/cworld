cmake_minimum_required(VERSION 3.5)
project(cworld)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/third_party/rapidjson/include)

option(BUILD_LIBRARY "Build library" OFF)
option(BUILD_EXECUTABLE "Build executable" ON)

if(BUILD_LIBRARY)
    set(CMAKE_SYSTEM_NAME iOS)
    set(CMAKE_OSX_ARCHITECTURES arm64 armv7)
    add_library(cworld STATIC earthmap.cpp utility.cpp)
endif()

if(BUILD_EXECUTABLE)
    add_executable(cworld main.cpp earthmap.cpp utility.cpp)
endif()

target_compile_options(cworld PRIVATE -Wall -Wextra)


