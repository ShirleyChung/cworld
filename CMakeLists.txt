cmake_minimum_required(VERSION 3.5)
project(cworld)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/third_party/rapidjson/include)

option(BUILD_LIBRARY "Build library" OFF)
option(BUILD_EXECUTABLE "Build executable" ON)

if(BUILD_LIBRARY)
    set(CMAKE_SYSTEM_NAME iOS)
    # 包含 ios-cmake 工具链
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/third_party/ios-cmake/ios.toolchain.cmake CACHE INTERNAL "")

    # 设置 iOS 平台为 SIMULATOR64
    set(IOS_PLATFORM SIMULATOR64)

    add_library(cworld STATIC earthmap.cpp utility.cpp cworld.cpp)
endif()

if(BUILD_EXECUTABLE)
    add_executable(cworld main.cpp earthmap.cpp utility.cpp)
endif()

target_compile_options(cworld PRIVATE -Wall -Wextra)


