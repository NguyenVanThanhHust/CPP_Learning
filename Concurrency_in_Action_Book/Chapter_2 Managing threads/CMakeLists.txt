project(chapter_2)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-O3")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories("/usr/include/eigen3")
add_executable(example_1 example_1.cpp)
target_link_libraries(example_1 PRIVATE Threads::Threads)
