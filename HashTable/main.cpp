#include <iostream>
#include <cstdlib>

#include "hashtableclasses/HashTableWithLinearDetector.h"
#include "hashtableclasses/HashTableWithLinkedList.h"

int HashTableWithLinkedList::unusedFlag = std::numeric_limits<int>::min();

using namespace std;

int testHashTableWithLinearDetector();
int testHashTableWithLinkedList();

int main() {
    //cout << "Hello, World!" << endl;
    //testHashTableWithLinearDetector();
    testHashTableWithLinkedList();
    return 0;
}

int testHashTableWithLinearDetector(){
        HashTableWithLinearDetector htwld(5);
        htwld.insert(1);
        htwld.insert(6);
        htwld.insert(5);
        htwld.insert(0);
        htwld.insert(4);
        htwld.showTable();
        htwld.insert(3);
        htwld.showTable();
        cout << htwld.get(1) << endl;
        cout << htwld.get(3) << endl;
        htwld.remove(6);
        htwld.remove(6);
};

int testHashTableWithLinkedList(){
        HashTableWithLinkedList htwll(7);
        srand(time(0));
        for(int count = 0; count < 30; ++count){
                htwll.insert(rand()%1000 + 33);
        }
        htwll.showTable();
        int value;
        cout << "Which value do you want to get?" << endl;
        cin >> value;
        cout << htwll.get(value) << endl;
        cout << "Which value do you want to delete?" << endl;
        cin >> value;
        htwll.remove(value);
}