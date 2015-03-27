#include <iostream>

#include "hashtableclasses/HashTableWithLinearDetector.h"

using namespace std;

int main() {
    //cout << "Hello, World!" << endl;
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