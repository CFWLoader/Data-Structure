cmake_minimum_required(VERSION 3.1)
project(Red_Black_Tree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Red_Black_Tree ${SOURCE_FILES} data-structure/RedBlackTree.cpp data-structure/RedBlackTree.h)