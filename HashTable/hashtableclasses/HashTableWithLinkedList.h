//
// Created by cfwloader on 3/27/15.
//

#ifndef _HASHTABLE_HASHTABLEWITHLINKEDLIST_H_
#define _HASHTABLE_HASHTABLEWITHLINKEDLIST_H_

#include <limits>

//Data structure for linked list.
struct ListNode{
    int key;
    ListNode* next;
    ListNode() : next(0){}
    ListNode(int val) : key(val), next(0){}
};

class HashTableWithLinkedList {
public:
    HashTableWithLinkedList() = delete ;
    explicit HashTableWithLinkedList(int);
    ~HashTableWithLinkedList();
    void insert(int);
    void remove(int);
    int get(int);
    void showTable();
private:
    int size, hashValue;
    static int unusedFlag;
    ListNode* objects;
    void initializeArray();
};


#endif //_HASHTABLE_HASHTABLEWITHLINKEDLIST_H_
