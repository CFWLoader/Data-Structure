//
// Created by cfwloader on 3/27/15.
//

#include <gmpxx.h>
#include <iostream>
#include "HashTableWithLinkedList.h"

//HashTableWithLinkedList::unusedFlag = std::numeric_limits<int>::min();

HashTableWithLinkedList::HashTableWithLinkedList(int presetSize) : size(presetSize), hashValue(size), objects(new ListNode[size]){
    initializeArray();
}

HashTableWithLinkedList::~HashTableWithLinkedList() {
    if(size > 0){
        delete[] objects;
        objects = 0;
        size = 0;
        hashValue = 0;
    }
}

void HashTableWithLinkedList::initializeArray() {
    for(int index = 0; index < size; ++index){
        objects[index].key = unusedFlag;
        objects[index].next = 0;
    }
}

void HashTableWithLinkedList::insert(int value) {
    int index = value % hashValue;
    if(objects[index].key == unusedFlag){
        objects[index].key = value;
        //std::cout << "O: Inserting : " << value << " Hash Index : " << index << " Inserted : " << objects[index].key << std::endl;
        return;
    }
    ListNode* ptr = &objects[index];
    while(ptr->next != 0){
        ptr = ptr->next;
    }
    ptr->next = new ListNode(value);
    //std::cout << "Inserting : " << value << " Hash Index : " << index <<" Inserted : " << ptr->key << std::endl;
    ptr = 0;
    return;
}

void HashTableWithLinkedList::remove(int value) {
    int index = value % hashValue;
    if(objects[index].key == unusedFlag){
        std::cerr << "Remove Operation: Value: " << value << ".The target object is not in the table." << std::endl;
        return;
    }
    ListNode* ptr = &objects[index];
    ListNode* pre = 0;
    while(ptr != 0 && ptr->key != value){
        pre = ptr;
        ptr = ptr->next;
    }
    if(ptr == 0){
        std::cerr << "Remove Operation: Value: " << value << ".The target object is not in the table." << std::endl;
        return;
    }
    pre->next = ptr->next;
    delete ptr;
    pre = 0, ptr = 0;
    return;
}

int HashTableWithLinkedList::get(int value) {
    int index = value % hashValue;
    if(objects[index].key == unusedFlag){
        std::cerr << "Get Operation: Value: " << value << ".The target object is not in the table." << std::endl;
        return unusedFlag;
    }
    ListNode* ptr = &objects[index];
    //ListNode* pre = 0;
    while(ptr != 0 && ptr->key != value){
        //pre = ptr;
        ptr = ptr->next;
    }
    if(ptr == 0){
        std::cerr << "Get Operation: Value: " << value << ".The target object is not in the table." << std::endl;
        return unusedFlag;
    }
    //pre->next = ptr->next;
    //delete ptr;
    //pre = 0, ptr = 0;
    return ptr->key;
}

void HashTableWithLinkedList::showTable() {
    ListNode* iter;
    for(int index = 0; index < size; ++index){
        iter = &objects[index];
        while(iter != 0 && iter->key != unusedFlag){
            std::cout << iter->key << " ";
            iter = iter->next;
        }
    }
    std::cout << std::endl;
}