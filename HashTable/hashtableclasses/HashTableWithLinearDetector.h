//
// Created by cfwloader on 3/27/15.
//

#ifndef _HASHTABLE_HASHTABLEWITHLINEARDETECTOR_H_
#define _HASHTABLE_HASHTABLEWITHLINEARDETECTOR_H_

//This class is the hash table uses linear detector to
//fix hash conflicts.
class HashTableWithLinearDetector {
public:
    HashTableWithLinearDetector() = delete;
    explicit HashTableWithLinearDetector(int);
    ~HashTableWithLinearDetector();
    void insert(int);
    void remove(int);
    int get(int);
    void showTable();
private:
    int size, hashValue, unusedFlag;
    int* objects;
    void initializeArray();
};


#endif //_HASHTABLE_HASHTABLEWITHLINEARDETECTOR_H_
