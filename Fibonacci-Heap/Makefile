CC = g++

CPPFLAGS = -std=c++11 -g -Wall

TARGET = FibonacciHeap

all: $(TARGET)

FibonacciHeap: FibonacciHeapNode.o FibonacciHeap.o main.o
	$(CC) -o $@ $(CPPFLAGS) $<

main.o: main.cpp
	$(CC) -o $@ $(CPPFLAGS) $<

FibonacciHeapNode.o: FibonacciHeapNode.cpp FibonacciHeapNode.h
	$(CC) -o $@ $(CPPFLAGS) -c $<

FibonacciHeap.o: FibonacciHeap.cpp FibonacciHeap.h
	$(CC) -o $@ $(CPPFLAGS) -c $<

clean:
	rm -rf *.o