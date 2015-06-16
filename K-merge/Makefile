CC = g++

FLAGS = -std=c++11 -g -Wall

TARGET = KMerger

TEMPDATA_DIR = ./datas

all: $(TARGET)

KMerger: main.o KMergeSorter.o FileBuffer.o Auxiliary.o
	$(CC) -o $@ $^ $(FLAGS)

main.o: main.cpp
	$(CC) -o $@ $< $(FLAGS) -c

#TestClass.o: TestClass.cpp TestClass.h
#	$(CC) -o $@ $< $(FLAGS) -c

KMergeSorter.o: KMergeSorter.cpp KMergeSorter.h
	$(CC) -o $@ $< $(FLAGS) -c

FileBuffer.o: FileBuffer.cpp FileBuffer.h
	$(CC) -o $@ $< $(FLAGS) -c

Auxiliary.o: Auxiliary.cpp Auxiliary.h
	$(CC) -o $@ $< $(FLAGS) -c

clean: 
	rm -rf $(TARGET) *.o

cleandata:
	rm -rf $(TEMPDATA_DIR)/*

cleanall:
	rm -rf $(TARGET) *.o $(TEMPDATA_DIR)/*