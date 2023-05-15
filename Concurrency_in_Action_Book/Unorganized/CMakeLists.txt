project(test_thread)

set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-O3")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories("/usr/include/eigen3")

add_executable(multi_thread_manual multi_thread_manual.cpp)
target_link_libraries(multi_thread_manual PRIVATE Threads::Threads)

add_executable(multi_thread_safe multi_thread_safe.cpp)
target_link_libraries(multi_thread_safe PRIVATE Threads::Threads)
