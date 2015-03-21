#include <iostream>
#include "BSTree.h"

using namespace std;

int testBSTreeBasicFunction();
int testBSTreeBasicFunction0();

int testAVL_Insert();

int main()
{
    //testBSTreeBasicFunction();
    testAVL_Insert();
    return 0;
}

int testBSTreeBasicFunction(){
    BSTree tree;
    tree.insertToBSTree(10);
    tree.insertToBSTree(1);
    tree.insertToBSTree(20);
    tree.insertToBSTree(4);
    tree.insertToBSTree(55);
    tree.traceInorder(cout);
    /*TreeNode* node = tree.search(1);
    if(node != 0)cout << node->Getkey() << endl;
    node = tree.search(3);
    if(node != 0)cout << node->Getkey() << endl;*/
    cout << "The tree depth: " << tree.Depth() << endl;
    return 0;
}

int testBSTreeBasicFunction0(){
    BSTree tree;
    tree.insertToBSTree(0);
    tree.insertToBSTree(1);
    tree.insertToBSTree(2);
    tree.insertToBSTree(3);
    tree.insertToBSTree(4);
    tree.insertToBSTree(5);
    tree.insertToBSTree(6);
    tree.traceInorder(cout);
    /*TreeNode* node = tree.search(1);
    if(node != 0)cout << node->Getkey() << endl;
    node = tree.search(3);
    if(node != 0)cout << node->Getkey() << endl;*/
    cout << "The tree depth: " << tree.Depth() << endl;
    return 0;
}

int testAVL_Insert(){
    BSTree tree;
    tree.avlInsert(0);
    tree.avlInsert(1);
    tree.avlInsert(2);
    tree.avlInsert(3);
    tree.avlInsert(4);
    tree.avlInsert(5);
    tree.avlInsert(6);
    /*
    tree.avlInsert(6);
    tree.avlInsert(5);
    tree.avlInsert(4);
    tree.avlInsert(3);
    tree.avlInsert(2);
    tree.avlInsert(1);
    tree.avlInsert(0);
    */
    tree.traceInorder(cout);
    cout << "The tree depth: " << tree.Depth() << endl;
    return 0;
}
