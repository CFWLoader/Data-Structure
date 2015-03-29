//
// Created by cfwloader on 3/27/15.
//

#include <iostream>
#include "RedBlackTree.h"

//#define INSERT_FIX_DEBUG
//#define RB_INSERT_DEBUG
//#define LEFT_ROTATE_DEBUG

#ifdef INSERT_FIX_DEBUG
using namespace std;
#endif

#ifdef RB_INSERT_DEBUG
using namespace std;
#endif

#ifdef LEFT_ROTATE_DEBUG
using namespace std;
#endif

//RedBlackTreeNode* RedBlackTreeNode::NIL_PTR = new RedBlackTreeNode();

/*
RedBlackTreeNode::RedBlackTreeNode() :
    key(0),
    color(BLACK),
    leftChild(this),
    rightChild(this),
    parent(this){ }
*/

RedBlackTreeNode::RedBlackTreeNode(int setKey) :
        key(setKey),
        color(RED),
        leftChild(0),
        rightChild(0),
        parent(0) { }

RedBlackTreeNode::RedBlackTreeNode(int setKey, Color setColor) :
        key(setKey),
        color(setColor),
        leftChild(0),
        rightChild(0),
        parent(0) { }

RedBlackTreeNode::RedBlackTreeNode(const RedBlackTreeNode &originalNode) :
        key(originalNode.key),
        color(originalNode.color),
        leftChild(originalNode.leftChild),
        rightChild(originalNode.rightChild),
        parent(originalNode.parent) { }

//Caution: The destructor just delete the node itself.
//You should design an algorithm for cascade delete.
RedBlackTreeNode::~RedBlackTreeNode() {
    leftChild = 0;
    rightChild = 0;
    parent = 0;
}

RedBlackTree::RedBlackTree() : root(0) { }

RedBlackTree::~RedBlackTree() {
    //std::cerr << "Destructor invoked." << std::endl;
    this->cascadeDeleter(root);
}

void RedBlackTree::cascadeDeleter(RedBlackTreeNode *&node) {
    if (!node)return;
    if (node->leftChild) cascadeDeleter(node->leftChild);
    node->leftChild = 0;
    if (node->rightChild) cascadeDeleter(node->rightChild);
    node->rightChild = 0;
    node->parent = 0;
    delete node;
    node = 0;
}

void RedBlackTree::showTree(std::ostream& os) const{
    this->showNode(os, root, 1);
}

void RedBlackTree::showNode(std::ostream& os, RedBlackTreeNode * const& node, int layer) const {
    if(node == 0)return;
    os << "Node->key: " << node->key << " Node->color: " << (node->color==RED?"RED":"BLACK") << " Layer: " << layer << std::endl;
    this->showNode(os, node->leftChild, layer + 1);
    this->showNode(os, node->rightChild, layer + 1);
}

void RedBlackTree::leftRotate(RedBlackTreeNode *node) {
    RedBlackTreeNode *rightChild = node->rightChild;
    node->rightChild = rightChild->leftChild;
#ifdef LEFT_ROTATE_DEBUG
    //this->showTree(cerr);
    cerr << "Parent key: " << node->key << endl;
    //cerr << node->rightChild->key << endl;
    cerr << "Right child: " << rightChild << endl;
#endif
    rightChild->parent = node->parent;
    if (node->parent == 0)root = rightChild;
    else if (node == node->parent->leftChild)node->parent->leftChild = rightChild;
    else node->parent->rightChild = rightChild;
    rightChild->leftChild = node;
    node->parent = rightChild;
#ifdef LEFT_ROTATE_DEBUG
    cerr << "Left Rotated." << endl;
    this->showTree(cerr);
#endif
}

void RedBlackTree::rightRotate(RedBlackTreeNode *node) {
    RedBlackTreeNode *leftChild = node->leftChild;
    node->leftChild = leftChild->rightChild;
    leftChild->parent = node->parent;
    if (node->parent == 0)root = leftChild;
    else if (node == node->parent->rightChild)node->parent->rightChild = leftChild;
    else node->parent->leftChild = leftChild;
    leftChild->rightChild = node;
    node->parent = leftChild;
}

//Notice that the insert or delete operation will do effect to the tree.
//The tree may break the principles.
//So we must call fixer function to fix the tree.
void RedBlackTree::redBlackInsert(RedBlackTreeNode *node) {
    RedBlackTreeNode *iter = root;
    RedBlackTreeNode *ptr = 0;
    while (iter != 0) {
        ptr = iter;
        if (ptr->key < node->key) {
            iter = iter->rightChild;
#ifdef RB_INSERT_DEBUG
        cerr << "Next is right child.Inserting: " << node->key << " Current: " << ptr->key << endl;
#endif
        } else {
            iter = iter->leftChild;
#ifdef RB_INSERT_DEBUG
            cerr << "Next is left child.Inserting: " << node->key << " Current: " << ptr->key << endl;
#endif
        }
    }
    node->parent = ptr;
    if (ptr == 0) {
        root = node;
        //root->color = BLACK;
#ifdef RB_INSERT_DEBUG
        cerr << "Inserting to root." << endl;
#endif
    } else if (node->key < ptr->key) {
        ptr->leftChild = node;
#ifdef RB_INSERT_DEBUG
        cerr << "Inserting to left child, the parent key is " << node->parent->key << "." << endl;
#endif
    } else {
        ptr->rightChild = node;
#ifdef RB_INSERT_DEBUG
        cerr << "Inserting to right child, the parent key is " << node->parent->key << "." << endl;
#endif
    }
    //We must fix the tree to accord with the principles of red black tree.
    //std::cerr << "Inserting node: " << node->key << std::endl;
#ifdef RB_INSERT_DEBUG
    cerr << "Node address: " << node << endl;
#endif
    this->insertFixer(node);
}

//Function for fixing the tree after the insert operation.
//It seems there are six situations of fixing the tree.
void RedBlackTree::insertFixer(RedBlackTreeNode *node) {
    RedBlackTreeNode *ptr = 0;
#ifdef INSERT_FIX_DEBUG
    cerr << "Fixer is called. Pointer: " << node << " Node key: " << node->key << endl;
    //this->showTree(cerr);
#endif
    while (node->parent && node->parent->color == RED) {
#ifdef INSERT_FIX_DEBUG
        //cerr << "Cases happening. " << endl;
        //this->showTree(cerr);
#endif
        if (node->parent == node->parent->parent->leftChild) {
            ptr = node->parent->parent->rightChild;
            if (ptr->color == RED) {                                    //case 1.
#ifdef INSERT_FIX_DEBUG
                cerr << "Case 1 happened. Key: " << node->key << endl;
#endif
                node->parent->color = BLACK;
                ptr->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
                continue;
            } else if (node == node->parent->rightChild) {              //case 2.
#ifdef INSERT_FIX_DEBUG
                cerr << "Case 2 happened. Key: " << node->key << endl;
#endif
                node = node->parent;
                this->leftRotate(node);
            }
#ifdef INSERT_FIX_DEBUG
            cerr << "Case 3 happened. Key: " << node->key << endl;
#endif
            node->parent->color = BLACK;                                //case 3. Note that case 2 is not mutual with case 3.
            node->parent->parent->color = RED;
            this->rightRotate(node->parent->parent);
        } else {
            ptr = node->parent->parent->leftChild;
            if (ptr && ptr->color == RED) {                                    //case 4.
#ifdef INSERT_FIX_DEBUG
                cerr << "Case 4 happened. Key: " << node->key << endl;
#endif
                node->parent->color = BLACK;
                ptr->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
                continue;
            } else if (node == node->parent->leftChild) {               //case 5.
#ifdef INSERT_FIX_DEBUG
                cerr << "Case 5 happened. Key: " << node->key << endl;
#endif
                node = node->parent;
                this->rightRotate(node);
            }
#ifdef INSERT_FIX_DEBUG
            cerr << "Case 6 happened. Key: " << node->key << endl;
#endif
            node->parent->color = BLACK;                                //case 6. Note that case 5 is not mutual with case 6.
            node->parent->parent->color = RED;
            this->leftRotate(node->parent->parent);
        }
    }
    root->color = BLACK;                                                //Root must be black.
}