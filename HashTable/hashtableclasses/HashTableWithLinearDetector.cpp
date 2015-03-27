//
// Created by cfwloader on 3/27/15.
//

#include "HashTableWithLinearDetector.h"
#include <limits>
#include <iostream>
#include <string.h>
#include <strings.h>

/*
HashTableWithLinearDetector::HashTableWithLinearDetector() : size(0), hashValue(0), objects(0){
}
*/

HashTableWithLinearDetector::HashTableWithLinearDetector(int presetSize) : size(presetSize), hashValue(size-1), unusedFlag(std::numeric_limits<int>::min()),objects(new int[size]) {
    initializeArray();
}

HashTableWithLinearDetector::~HashTableWithLinearDetector() {
    if(size > 0){
        delete[] objects;
        objects = 0;
        size = 0;
        hashValue = 0;
    }
}

void HashTableWithLinearDetector::initializeArray() {
    for(int index = 0; index < size; ++index){
        //Use minimum 32bits integer to mark the unused.
        objects[index] = unusedFlag;
    }
}

void HashTableWithLinearDetector::insert(int value) {
    int index = value % hashValue;
    int counter = 0;
    while(objects[index] != unusedFlag && counter < size){
        index = (index + 1) % size;
        ++counter;
    }
    if(counter >= size){
        std::cerr << "The hash table is full." << std::endl;
        return;
    }
    objects[index] = value;
}

void HashTableWithLinearDetector::remove(int value) {
    int index = value % hashValue;
    int counter = 0;
    while(objects[index] != value && counter < size){
        index = (index + 1) % size;
        ++counter;
    }
    if(counter >= size){
        std::cerr << "Remove Operation: Value: " << value << ".The target object is not in the table." << std::endl;
        return;
    }
    objects[index] = unusedFlag;
}

int HashTableWithLinearDetector::get(int value) {
    int index = value % hashValue;
    int counter = 0;
    while(objects[index] != value && counter < size){
        index = (index + 1) % size;
        ++counter;
    }
    if(counter >= size){
        std::cerr << "Get Operation: Value: "<< value <<".The target object is not in the table." << std::endl;
        return unusedFlag;
    }
    return objects[index];
}

void HashTableWithLinearDetector::showTable() {
    for(int index = 0; index < size; ++ index){
        std::cout << objects[index] << " ";
    }
    std::cout << std::endl;
}