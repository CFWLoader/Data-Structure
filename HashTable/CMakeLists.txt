cmake_minimum_required(VERSION 3.1)
project(HashTable)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(HashTable ${SOURCE_FILES} hashtableclasses/HashTableWithLinearDetector.cpp hashtableclasses/HashTableWithLinearDetector.h hashtableclasses/HashTableWithLinkedList.cpp hashtableclasses/HashTableWithLinkedList.h hashtableclasses/HashTableWithMapping.cpp hashtableclasses/HashTableWithMapping.h)