//
// Created by cfwloader on 3/27/15.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include <queue>
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

RedBlackTreeNode* RedBlackTreeNode::NIL_PTR = new RedBlackTreeNode();


RedBlackTreeNode::RedBlackTreeNode() :
    key(0),
    color(BLACK),
    leftChild(this),
    rightChild(this),
    parent(this){ }

/*
RedBlackTreeNode::RedBlackTreeNode(int setKey) :
        key(setKey),
        color(RED),
        leftChild(0),
        rightChild(0),
        parent(0) { }
        */

RedBlackTreeNode::RedBlackTreeNode(int setKey) :
        key(setKey),
        color(RED),
        leftChild(NIL_PTR),
        rightChild(NIL_PTR),
        parent(NIL_PTR) { }

RedBlackTreeNode::RedBlackTreeNode(int setKey, Color setColor) :
        key(setKey),
        color(setColor),
        leftChild(NIL_PTR),
        rightChild(NIL_PTR),
        parent(NIL_PTR) { }

/*
RedBlackTreeNode::RedBlackTreeNode(int setKey, Color setColor) :
        key(setKey),
        color(setColor),
        leftChild(0),
        rightChild(0),
        parent(0) { }
        */

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

RedBlackTree::RedBlackTree() : root(RedBlackTreeNode::NIL_PTR) { }

RedBlackTree::~RedBlackTree() {
    //std::cerr << "Destructor invoked." << std::endl;
    this->cascadeDeleter(root);
}

void RedBlackTree::cascadeDeleter(RedBlackTreeNode *&node) {
    if (node != RedBlackTreeNode::NIL_PTR)return;
    if (node->leftChild != RedBlackTreeNode::NIL_PTR) cascadeDeleter(node->leftChild);
    node->leftChild = RedBlackTreeNode::NIL_PTR;
    if (node->rightChild != RedBlackTreeNode::NIL_PTR) cascadeDeleter(node->rightChild);
    node->rightChild = RedBlackTreeNode::NIL_PTR;
    node->parent = RedBlackTreeNode::NIL_PTR;
    delete node;
    node = RedBlackTreeNode::NIL_PTR;
}

void RedBlackTree::showTree(std::ostream &os) const {
    this->showNode(os, root, 1);
}

void RedBlackTree::showNode(std::ostream &os, RedBlackTreeNode *const &node, int layer) const {
    if (node == RedBlackTreeNode::NIL_PTR)return;
    os << "Node->key: " << node->key << " Node->color: " << (node->color == RED ? "RED" : "BLACK") << " Layer: " <<
    layer << " P-key: " << (node->parent ? node->parent->key : -9999) << " L-key: " << (node->leftChild ? node->leftChild->key : -9999) << " R-key: " << (node->rightChild ? node->rightChild->key : -9999) <<
            std::endl;
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
    if(rightChild->leftChild != RedBlackTreeNode::NIL_PTR)rightChild->leftChild->parent = node;
    rightChild->parent = node->parent;
    if (node->parent == RedBlackTreeNode::NIL_PTR)root = rightChild;
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
    if(leftChild->rightChild != RedBlackTreeNode::NIL_PTR)leftChild->rightChild->parent = node;
    leftChild->parent = node->parent;
    if (node->parent == RedBlackTreeNode::NIL_PTR)root = leftChild;
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
    RedBlackTreeNode *ptr = RedBlackTreeNode::NIL_PTR;
    while (iter != RedBlackTreeNode::NIL_PTR) {
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
    if (ptr == RedBlackTreeNode::NIL_PTR) {
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
    RedBlackTreeNode *ptr = RedBlackTreeNode::NIL_PTR;
#ifdef INSERT_FIX_DEBUG
    cerr << "Fixer is called. Pointer: " << node << " Node key: " << node->key << endl;
    //this->showTree(cerr);
#endif
    while (node->parent->color == RED) {
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

//This function cost me some time to understand.
RedBlackTreeNode *RedBlackTree::successor(RedBlackTreeNode *node) {
    assert(node != 0);
    if (node->rightChild == RedBlackTreeNode::NIL_PTR) {
        RedBlackTreeNode *parent = node->parent;
        while (parent != RedBlackTreeNode::NIL_PTR && node != parent->rightChild) {
            node = parent;
            parent = node->parent;
        }
        node = parent;
    } else {
        node = node->rightChild;
        while (node->leftChild != RedBlackTreeNode::NIL_PTR) {
            node = node->leftChild;
        }
    }
    return node;
}

//Binary search tree's delete method.
RedBlackTreeNode *RedBlackTree::redBlackDelete(RedBlackTreeNode *node) {
    RedBlackTreeNode *ptr = RedBlackTreeNode::NIL_PTR, *child = RedBlackTreeNode::NIL_PTR;
    if(node == RedBlackTreeNode::NIL_PTR) return 0;
    if (node->leftChild == RedBlackTreeNode::NIL_PTR || node->rightChild == RedBlackTreeNode::NIL_PTR) {
        ptr = node;
    } else {
        ptr = this->successor(node);
    }
    if (ptr->leftChild != RedBlackTreeNode::NIL_PTR) {
        child = ptr->leftChild;
    } else {
        child = ptr->rightChild;
    }
    if(child != RedBlackTreeNode::NIL_PTR)child->parent = ptr->parent;
    if (child != RedBlackTreeNode::NIL_PTR && ptr->parent == RedBlackTreeNode::NIL_PTR) {
        root = child;
    } else if (child != RedBlackTreeNode::NIL_PTR && ptr == child->parent->leftChild) {
        ptr->parent->leftChild = child;
    } else {
        ptr->parent->rightChild = child;
    }
    if (ptr != node) {
        node->key = ptr->key;
    }
    if (ptr->color == BLACK)this->deleteFixer(child);
    return ptr;
}

void RedBlackTree::deleteFixer(RedBlackTreeNode *node) {
    RedBlackTreeNode *ptr = RedBlackTreeNode::NIL_PTR;
    while (node != root && node->color == BLACK) {
        if (node == node->parent->leftChild) {                                                            //Case 1
            ptr = node->parent->rightChild;
            if (ptr->color == RED) {
                ptr->color = BLACK;
                node->parent->color = RED;
                this->leftRotate(node->parent);
                ptr = node->parent->rightChild;
            }
            if (ptr->leftChild->color == BLACK && ptr->rightChild->color == BLACK) {                      //Case 2
                ptr->color = RED;
                node = node->parent;
            } else if (ptr->rightChild->color == BLACK) {                                                 //Case 3
                ptr->leftChild->color = BLACK;
                ptr->color = RED;
                this->rightRotate(ptr);
                ptr = ptr->parent->rightChild;
            }
            ptr->color = node->parent->color;                                                           //Case 4
            node->parent->color = BLACK;
            ptr->rightChild->color = BLACK;
            node = root;
        } else {
            if (node == node->parent->rightChild) {                                                          //Case 5
                ptr = node->parent->leftChild;
                if (ptr->color == RED) {
                    ptr->color = BLACK;
                    node->parent->color = RED;
                    this->rightRotate(node->parent);
                    ptr = node->parent->leftChild;
                }
                if (ptr->rightChild->color == BLACK && ptr->leftChild->color == BLACK) {                      //Case 6
                    ptr->color = RED;
                    node = node->parent;
                } else if (ptr->leftChild->color == BLACK) {                                                 //Case 7
                    ptr->rightChild->color = BLACK;
                    ptr->color = RED;
                    this->leftRotate(ptr);
                    ptr = ptr->parent->leftChild;
                }
                ptr->color = node->parent->color;                                                           //Case 8
                node->parent->color = BLACK;
                ptr->leftChild->color = BLACK;
                node = root;
            }
        }
    }
    root->color = BLACK;
}

RedBlackTreeNode *RedBlackTree::binarySearch(int keyValue) const {
    RedBlackTreeNode* node = root;
    while(node != RedBlackTreeNode::NIL_PTR && node->key != keyValue)
        node = (node->key < keyValue) ? node->rightChild : node->leftChild;
    return node;
}

void RedBlackTree::writeDataToFile_JSType(std::ofstream &out) {
    out << "rbt=[";
    std::queue<RedBlackTreeNode*> nodeQueue;
    if(root != RedBlackTreeNode::NIL_PTR)nodeQueue.push(root);
    RedBlackTreeNode* ptr = RedBlackTreeNode::NIL_PTR;
    while(!nodeQueue.empty()){
        ptr = nodeQueue.front();
        nodeQueue.pop();
        if(ptr->leftChild != RedBlackTreeNode::NIL_PTR)nodeQueue.push(ptr->leftChild);
        if(ptr->rightChild != RedBlackTreeNode::NIL_PTR)nodeQueue.push(ptr->rightChild);
        out << "{\"key\":\"node-" << ptr->key << "\", " ;
        if(ptr->parent != RedBlackTreeNode::NIL_PTR)out << "\"parent\":\"node-" << ptr->parent->key << "\", ";
        else out << "\"parent\":\"node0\", ";
        out << "\"color\":\"" << (ptr->color == RED ? "#ff0000\"}" : "#00A9C9\"}");
        if(!nodeQueue.empty())out << ", ";
    }
    /*
    this->writeDataToFile_JSType(out, root);
    out;
     */
    out << "]";
}

/*
void RedBlackTree::writeDataToFile_JSType(std::ofstream & out, RedBlackTreeNode* const &node) {
    if(node == 0)return;
    out << "{\"key\":\"node-" << node->key << "\", " ;
    if(node->parent)out << "\"parent\":\"" << node->parent->key << "\", ";
    else out << "\"parent\":\"node0\", ";
    out << "\"color\":\"" << (node->color == RED ? "#ff0000\"}" : "#00A9C9\"},");
}
 */
