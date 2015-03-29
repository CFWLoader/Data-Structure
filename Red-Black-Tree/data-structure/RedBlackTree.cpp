//
// Created by cfwloader on 3/27/15.
//

#include <iostream>
#include "RedBlackTree.h"

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
    //std::cout << "Destructor invoked." << std::endl;
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

void RedBlackTree::leftRotate(RedBlackTreeNode *&node) {
    RedBlackTreeNode **rightChild = &node->rightChild;
    node->rightChild = (*rightChild)->leftChild;
    (*rightChild)->parent = node->parent;
    if (node->parent == 0)root = (*rightChild);
    else if (node == node->parent->leftChild)node->parent->leftChild = *rightChild;
    else node->parent->rightChild = *rightChild;
    (*rightChild)->leftChild = node;
    node->parent = *rightChild;
}

void RedBlackTree::rightRotate(RedBlackTreeNode *&node) {
    RedBlackTreeNode **leftChild = &node->leftChild;
    node->leftChild = (*leftChild)->rightChild;
    (*leftChild)->parent = node->parent;
    if (node->parent == 0)root = (*leftChild);
    else if (node == node->parent->rightChild)node->parent->rightChild = *leftChild;
    else node->parent->leftChild = *leftChild;
    (*leftChild)->rightChild = node;
    node->parent = *leftChild;
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
            iter = iter->leftChild;
        } else {
            iter = iter->rightChild;
        }
    }
    node->parent = ptr;
    if (ptr == 0) {
        root = node;
        root->color = BLACK;
    } else if (node->key < ptr->key) {
        ptr->leftChild = node;
    } else {
        ptr->rightChild = node;
    }
    //We must fix the tree to accord with the principles of red black tree.
    std::cout << "Inserting node: " << node->key << std::endl;
    this->insertFixer(node);
}

//Function for fixing the tree after the insert operation.
//It seems there are six situations of fixing the tree.
void RedBlackTree::insertFixer(RedBlackTreeNode *node) {
    RedBlackTreeNode *ptr = 0;
    while (node->color == RED) {
        if (node->parent == node->parent->parent->leftChild) {
            ptr = node->parent->parent->rightChild;
            if (ptr->color == RED) {                                    //case 1.
                node->parent->color = BLACK;
                ptr->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else if (node == node->parent->rightChild) {              //case 2.
                node = node->parent;
                this->leftRotate(node);
            }
            node->parent->color = BLACK;                                //case 3. Note that case 2 is not mutual with case 3.
            node->parent->parent->color = RED;
            this->rightRotate(node->parent->parent);
        } else {
            ptr = node->parent->parent->leftChild;
            if (ptr->color == RED) {                                    //case 4.
                node->parent->color = BLACK;
                ptr->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else if (node == node->parent->leftChild) {               //case 5.
                node = node->parent;
                this->rightRotate(node);
            }
            node->parent->color = BLACK;                                //case 6. Note that case 5 is not mutual with case 6.
            node->parent->parent->color = RED;
            this->leftRotate(node->parent->parent);
        }
    }
    root->color = BLACK;                                                //Root must be black.
}