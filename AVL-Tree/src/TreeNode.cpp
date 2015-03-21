#include "TreeNode.h"
#include <iostream>
#include <limits.h>

TreeNode::TreeNode() : key(INT_MIN), leftChild(0), rightChild(0)
{
    //ctor
}

TreeNode::TreeNode(int setKey) : key(setKey), leftChild(0), rightChild(0)
{
    //ctor
}

TreeNode::~TreeNode()
{
    delete leftChild;
    leftChild = 0;
    delete rightChild;
    rightChild = 0;
    //std::cout << "deleting myself  " << key << std::endl;
    //delete this;
    //dtor
}
