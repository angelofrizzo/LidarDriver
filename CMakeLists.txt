cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

project(LidarDriver)

include_directories(include)

add_executable(main src/main.cpp src/LidarDriver.cpp)
