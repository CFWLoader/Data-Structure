//
// Created by cfwloader on 3/28/15.
//

#ifndef _HASHTABLE_HASHTABLEWITHMAPPING_H_
#define _HASHTABLE_HASHTABLEWITHMAPPING_H_

/*
struct MapNode{
    int hashIndex;
    int* object;
    MapNode() : object(0){}
    MapNode(int hashValue, int* objectValue) : hashIndex(hashValue), object(objectValue){}
    ~MapNode(){
        hashIndex = -1;
        if(object)delete object;
        object = 0;
    }
};
*/

//The class is under being speculation.
//Because the hash value seems redundant in this implementation.
//Finally, I found out it's the prototype of hash mapping.
class HashTableWithMapping {
public:
    HashTableWithMapping() = delete;
    explicit HashTableWithMapping(int);
    ~HashTableWithMapping();
    void insert(int*);
    void remove(int*);
    int* get(int*);
    void showTable();
private:
    int size, hashValue;
    //static int unusedFlag;
    int** objects;
    void initializeArray();
};


#endif //_HASHTABLE_HASHTABLEWITHMAPPING_H_
