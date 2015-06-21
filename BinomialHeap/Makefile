CC = g++

FLAGS = -std=c++11 -g -Wall

TARGET = BinomialHeap

all: $(TARGET)

BinomialHeap: HeapNode.o BinomialHeap.o GraphvizOutput.o Auxiliary.o main.o
	$(CC) -o $@ $(FLAGS) $^

BinomialHeap.o: BinomialHeap.cpp BinomialHeap.h
	$(CC) -o $@ $(FLAGS) -c $<

main.o: main.cpp
	$(CC) -o $@ $(FLAGS) -c $<

HeapNode.o: HeapNode.cpp HeapNode.h
	$(CC) -o $@ $(FLAGS) -c $<

GraphvizOutput.o: GraphvizOutput.cpp GraphvizOutput.h
	$(CC) -o $@ $(FLAGS) -c $<

Auxiliary.o: Auxiliary.cpp Auxiliary.h
	$(CC) -o $@ $(FLAGS) -c $<	

#%.o: %.cpp %.h
#	$(CC) -o $@ $(FLAGS) -c $<

clean:
	rm -rf *.o

cleanall:
	rm -rf $(TARGET) *.o ./diagram/*
