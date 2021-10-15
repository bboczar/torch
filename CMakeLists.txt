cmake_minimum_required(VERSION 3.8)

project(Torch)

set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS} -g -Wall -pedantic -Werror")

add_subdirectory(source)
