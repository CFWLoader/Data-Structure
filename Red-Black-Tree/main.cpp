#include <iostream>
#include "data-structure/RedBlackTree.h"

using namespace std;

int main() {
    //cout << "Hello, World!" << endl;
    RedBlackTree redBlackTree;
    redBlackTree.redBlackInsert(new RedBlackTreeNode(1));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(2));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(3));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(4));
    redBlackTree.redBlackInsert(new RedBlackTreeNode(5));
    return 0;
}