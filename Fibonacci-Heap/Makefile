CC = g++

CPPFLAGS = -std=c++11 -g -Wall

TARGET = FibonacciHeap

all: $(TARGET)

FibonacciHeap: FibonacciHeapNode.o FibonacciHeap.o GraphvizOutput.o main.o
	$(CC) -o $@ $(CPPFLAGS) $^

main.o: main.cpp
	$(CC) -o $@ $(CPPFLAGS) -c $<

FibonacciHeapNode.o: FibonacciHeapNode.cpp FibonacciHeapNode.h
	$(CC) -o $@ $(CPPFLAGS) -c $<

FibonacciHeap.o: FibonacciHeap.cpp FibonacciHeap.h
	$(CC) -o $@ $(CPPFLAGS) -c $<

GraphvizOutput.o: GraphvizOutput.cpp GraphvizOutput.h
	$(CC) -o $@ $(CPPFLAGS) -c $<

clean:
	rm -rf *.o

cleanall:
	rm -rf *.o $(TARGET) ./diagram/*