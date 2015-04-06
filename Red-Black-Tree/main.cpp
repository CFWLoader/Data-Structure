#include <iostream>
#include <fstream>
#include <assert.h>
#include "data-structure/RedBlackTree.h"

using namespace std;

int main() {
    //cout << "Hello, World!" << endl;
    RedBlackTree redBlackTree;
    ofstream jsOut("/run/media/cfwloader/Documents/Project/C++/Data-Structure/Red-Black-Tree/GraphicTreeView/myJsData.js");

    for(int i = 0; i < 20; ++i){
        redBlackTree.redBlackInsert(new RedBlackTreeNode(i));
        /*
        ofstream jsOut("/run/media/cfwloader/Documents/Project/C++/Data-Structure/Red-Black-Tree/GraphicTreeView/myJsData.js");

        if (jsOut.is_open()) {
            redBlackTree.writeDataToFile_JSType(jsOut);
        }else{
            cout << "write failed." << endl;
        }
        jsOut.close();

        cout << i << endl;
        getchar();
         */

        /*
        redBlackTree.showTree(cout);
        getchar();
         */
    }

    /*
    redBlackTree.redBlackInsert(new RedBlackTreeNode(1));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(2));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(3));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(4));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(5));
     */

    redBlackTree.showTree(cout);
    /*
    int searchKey;
    RedBlackTreeNode* ptrRecord;
    while(cin >> searchKey){
        ptrRecord = redBlackTree.binarySearch(searchKey);
        redBlackTree.redBlackDelete(ptrRecord);
        redBlackTree.showTree(cout);
    }
     */

    if (jsOut.is_open()) {
        redBlackTree.writeDataToFile_JSType(jsOut);
    }else{
        cout << "write failed." << endl;
    }
    jsOut.close();

    /*
    for(int i = 0; i < 20; ++i){
        redBlackTree.redBlackInsert(new RedBlackTreeNode(i));
    }

    redBlackTree.redBlackInsert(new RedBlackTreeNode(1));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(2));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(3));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(4));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(5));

    redBlackTree.showTree(cout);
    int searchKey;
    RedBlackTreeNode* ptrRecord;
    while(cin >> searchKey){
        ptrRecord = redBlackTree.binarySearch(searchKey);
        redBlackTree.redBlackDelete(ptrRecord);
        redBlackTree.showTree(cout);
    }
    */
    return 0;
}