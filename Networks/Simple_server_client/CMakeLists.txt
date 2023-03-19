cmake_minimum_required(VERSION 3.16.3)

project(network_sample LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)

add_executable(network_sample main.cpp)

include_directories(network_sample
  /usr/local/cuda-12.0/include
  ../../../asio-1.24.0/include/
  ../../../asio-1.24.0/src/
)

link_directories(network_sample
)

# target_link_libraries(network_sample
#   ${CUDA_LIBRARIES}
#   /usr/local/cuda/lib64/libcudart.so
# )