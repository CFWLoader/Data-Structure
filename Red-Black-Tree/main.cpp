#include <iostream>
#include "data-structure/RedBlackTree.h"

using namespace std;

int main() {
    //cout << "Hello, World!" << endl;
    RedBlackTree redBlackTree;
    for(int i = 0; i < 20; ++i){
        redBlackTree.redBlackInsert(new RedBlackTreeNode(i));
    }
    /*
    redBlackTree.redBlackInsert(new RedBlackTreeNode(1));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(2));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(3));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(4));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(5));
     */
    redBlackTree.showTree(cout);
    return 0;
}