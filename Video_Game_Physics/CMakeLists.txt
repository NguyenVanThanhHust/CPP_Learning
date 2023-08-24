cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(video_game LANGUAGES CXX CUDA)

option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)

set(CMAKE_BUILD_TYPE "Release")
set(OpenGL_GL_PREFERENCE  GLVND)
add_definitions("-DENABLE_SSE")

set(CMAKE_CXX_FLAGS "-std=c++17 -O3 -pthread -Wall -Ofast -Wfatal-errors -D_MWAITXINTRIN_H_INCLUDED")

add_executable(particle_simulation src/particle_simulation.cpp)
add_executable(rigid_body_simulation src/rigid_body_simulation.cpp)