CC = g++

FLAGS = -std=c++11 -g -Wall

TARGET = KMerger

TEMPDATA_DIR = ./datas

all: $(TARGET)

KMerger: main.cpp FileBuffer.o RandomNumberGenerator.hpp
	$(CC) -o $@ $^ $(FLAGS)

FileBuffer.o: FileBuffer.cpp FileBuffer.h
	$(CC) -o $@ $< $(FLAGS) -c

clean: 
	rm -rf $(TARGET) *.o

cleandata:
	rm -rf $(TEMPDATA_DIR)/*

cleanall:
	rm -rf $(TARGET) *.o $(TEMPDATA_DIR)/*

# KMegerSorter.o: KMegerSorter.cpp KMegerSorter.h
#	$(CC) -o $@ $(FLAGS) $<