//
// Created by cfwloader on 3/28/15.
//

#include <iostream>
#include <limits>
#include "HashTableWithMapping.h"

HashTableWithMapping::HashTableWithMapping(int presetSize) : size(presetSize), hashValue(size), objects(new int*[size]) {
    initializeArray();
}

HashTableWithMapping::~HashTableWithMapping() {
    if(size > 0){
        for(int index = 0; index < size; ++index){
            delete objects[index];
            objects = 0;
        }
        delete[] objects;
        objects = 0;
        size = 0;
        hashValue = 0;
    }
}

void HashTableWithMapping::initializeArray() {
    for(int index = 0; index < size; ++index){
        //Use minimum 32bits integer to mark the unused.
        objects[index] = 0;
    }
}

void HashTableWithMapping::insert(int* value) {
    int index = *value % hashValue;
    int counter = 0;
    while(objects[index] != 0 && counter < size){
        index = (index + 1) % size;
        ++counter;
    }
    if(counter >= size){
        std::cerr << "The hash table is full." << std::endl;
        return;
    }
    objects[index] = value;
}

void HashTableWithMapping::remove(int* value) {
    int index = *value % hashValue;
    int counter = 0;
    while(objects[index] != value && counter < size){
        index = (index + 1) % size;
        ++counter;
    }
    if(counter >= size){
        std::cerr << "Remove Operation: Value: " << value << ".The target object is not in the table." << std::endl;
        return;
    }
    delete objects[index];
    objects[index] = 0;
    //delete
}

int* HashTableWithMapping::get(int* value) {
    int index = *value % hashValue;
    int counter = 0;
    while(objects[index] != 0 && counter < size){
        index = (index + 1) % size;
        ++counter;
    }
    if(counter >= size){
        std::cerr << "Get Operation: Value: "<< value <<".The target object is not in the table." << std::endl;
        return 0;
    }
    return objects[index];
}

void HashTableWithMapping::showTable() {
    for(int index = 0; index < size; ++ index){
        std::cout << *objects[index] << " ";
    }
    std::cout << std::endl;
}
