//
// Created by cfwloader on 3/27/15.
//

#include "RedBlackTree.h"

RedBlackTreeNode::RedBlackTreeNode(int setKey) :
        key(setKey),
        color(RED),
        leftChild(0),
        rightChild(0),
        parent(0){}

RedBlackTreeNode::RedBlackTreeNode(int setKey, Color setColor) :
        key(setKey),
        color(setColor),
        leftChild(0),
        rightChild(0),
        parent(0){}

RedBlackTreeNode::RedBlackTreeNode(const RedBlackTreeNode& originalNode) :
        key(originalNode.key),
        color(originalNode.color),
        leftChild(originalNode.leftChild),
        rightChild(originalNode.rightChild),
        parent(originalNode.parent){}

//Caution: The destructor just delete the node itself.
//You should design an algorithm for cascade delete.
RedBlackTreeNode::~RedBlackTreeNode(){
    leftChild = 0;
    rightChild = 0;
    parent = 0;
}

RedBlackTree::RedBlackTree() : root(0){}

RedBlackTree::~RedBlackTree() {
    //std::cout << "Destructor invoked." << std::endl;
    this->cascadeDeleter(root);
}

void RedBlackTree::testDestructor() {
    root = new RedBlackTreeNode(1, BLACK);
    root->leftChild = new RedBlackTreeNode(2, RED);
    root->rightChild = new RedBlackTreeNode(3, RED);
    root->leftChild->rightChild = new RedBlackTreeNode(4, BLACK);
    root->rightChild->rightChild = new RedBlackTreeNode(5, BLACK);
}

void RedBlackTree::cascadeDeleter(RedBlackTreeNode *& node) {
    if(!node)return;
    if(node->leftChild) cascadeDeleter(node->leftChild);
    node->leftChild = 0;
    if(node->rightChild) cascadeDeleter(node->rightChild);
    node->rightChild = 0;
    node->parent = 0;
    delete node;
    node = 0;
}

void RedBlackTree::leftRotate(RedBlackTreeNode*& node) {
    RedBlackTreeNode** rightChild = &node->rightChild;
    node->rightChild = (*rightChild)->leftChild;
    (*rightChild)->parent = node->parent;
    if(node->parent == 0)root = (*rightChild);
    else if(node == node->parent->leftChild)node->parent->leftChild = *rightChild;
    else node->parent->rightChild = *rightChild;
    (*rightChild)->leftChild = node;
    node->parent = *rightChild;
}

void RedBlackTree::rightRotate(RedBlackTreeNode *& node) {
    RedBlackTreeNode** leftChild = &node->leftChild;
    node->leftChild = (*leftChild)->rightChild;
    (*leftChild)->parent = node->parent;
    if(node->parent == 0)root = (*leftChild);
    else if(node == node->parent->rightChild)node->parent->rightChild = *leftChild;
    else node->parent->leftChild = *leftChild;
    (*leftChild)->rightChild = node;
    node->parent = *leftChild;
}

void RedBlackTree::redBlackInsert(RedBlackTreeNode * node) {
    RedBlackTreeNode* iter = root;
    RedBlackTreeNode* ptr = 0;
    while(iter != 0){
        ptr = iter;
        if(ptr->key < node->key){
            iter = iter->leftChild;
        }else{
            iter = iter->rightChild;
        }
    }
    node->parent = ptr;
    if(ptr == 0){
        root = node;
    }else if(node->key < ptr->key){
        ptr->leftChild = node;
    }else{
        ptr->rightChild = node;
    }
    this->insertFixer(node);
}

void RedBlackTree::insertFixer(RedBlackTreeNode *& node) {
}