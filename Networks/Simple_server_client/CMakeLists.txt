cmake_minimum_required(VERSION 3.16.3)

project(network_sample LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-std=c++17 -O3 -pthread -Wall -Ofast -Wfatal-errors -D_MWAITXINTRIN_H_INCLUDED")

add_executable(network_sample main.cpp)

include_directories(network_sample
  /usr/local/cuda/include
  ../../../asio-1.28.0/include/
  ../../../asio-1.28.0/src/
)

link_directories(network_sample
)