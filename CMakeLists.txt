cmake_minimum_required(VERSION 3.3)
project(data_structure)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    linkedlist.cpp
    linkedlist.h
    test_linkedlist.cpp)

add_executable(data_structure ${SOURCE_FILES})