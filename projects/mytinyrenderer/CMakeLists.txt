cmake_minimum_required(VERSION 3.17)
project(mytinyrenderer)

set(CMAKE_CXX_STANDARD 14)

add_executable(mytinyrenderer main.cpp tgaimage.h tgaimage.cpp)