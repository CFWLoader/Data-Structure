CC = g++

FLAGS = -std=c++11 -g -Wall

TARGET = BinomialHeap

all: $(TARGET)

BinomialHeap: HeapNode.o GraphvizOutput.o main.o
	$(CC) -o $@ $(FLAGS) $^

#main.o: main.cpp
#	$(CC) -o $@ $(FLAGS) -c $<

#HeapNode.o: HeapNode.cpp HeapNode.h
#	$(CC) -o $@ $(FLAGS) -c $<

%.o: %.cpp %.h
	$(CC) -o $@ $(FLAGS) -c $<

clean:
	rm -rf *.o

cleanall:
	rm -rf $(TARGET) *.o