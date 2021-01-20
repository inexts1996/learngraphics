cmake_minimum_required(VERSION 3.17)
project(tinyrenderer)

set(CMAKE_CXX_STANDARD 14)

add_executable(tinyrenderer tgaimage.h tgaimage.cpp main.cpp)