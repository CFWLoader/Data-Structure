project(FibonacciHeap)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

set(SOURCE_FILES 
			Auxiliary.h
			Auxiliary.cpp
			FibonacciHeapNode.h
			FibonacciHeapNode.cpp
			FibonacciHeap.h
			FibonacciHeap.cpp
			GraphvizOutput.h
			GraphvizOutput.cpp
			main.cpp
	)

add_executable(FibonacciHeap ${SOURCE_FILES})