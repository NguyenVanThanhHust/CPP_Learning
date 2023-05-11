cmake_minimum_required(VERSION 3.16.3)

project(network_sample LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)

add_executable(network_sample main.cpp)

include_directories(network_sample
  /usr/local/cuda/include
  ../../../asio/include/
  ../../../asio/src/
)

link_directories(network_sample
)