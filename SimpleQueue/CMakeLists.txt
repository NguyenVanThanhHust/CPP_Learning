cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(simple_queue LANGUAGES CXX CUDA)

option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)

set(CMAKE_BUILD_TYPE "Release")
set(OpenGL_GL_PREFERENCE  GLVND)
add_definitions("-DENABLE_SSE")

set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -pthread -Wall -Ofast -Wfatal-errors -D_MWAITXINTRIN_H_INCLUDED")


link_directories(/usr/local/cuda/lib64)

add_executable(${PROJECT_NAME}
    atomicops.h
    readwritequeue.h
    main.cpp
    )

target_link_libraries(${PROJECT_NAME}
    cuda
)
        
