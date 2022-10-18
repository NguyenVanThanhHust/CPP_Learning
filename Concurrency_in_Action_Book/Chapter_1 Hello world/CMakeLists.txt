set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(hello_world hello_world.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(hello_world PRIVATE Threads::Threads)