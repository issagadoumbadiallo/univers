cmake_minimum_required(VERSION 3.9.4)
#project(braketparseExample)

add_executable(executable_parsebraket parsebracket.cpp)

include_directories(../../adouna/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")

add_definitions( "-Wall -O3" )