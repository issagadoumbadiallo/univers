cmake_minimum_required(VERSION 3.0)
#project(SpdlogExamples)

find_package(Threads)

add_executable(executable climbing.cpp )

include_directories(../../adouna/ ../../../thirdparty/spdlog/)

target_link_libraries(executable ${CMAKE_THREAD_LIBS_INIT})


file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")

#add_test(NAME RunExample COMMAND (executable)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")

add_definitions( "-Wall -O3" )
