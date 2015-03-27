//
// Created by cfwloader on 3/27/15.
//

#ifndef _RED_BLACK_TREE_REDBLACKTREE_H_
#define _RED_BLACK_TREE_REDBLACKTREE_H_

enum Color{RED, BLACK};

struct RedBlackTreeNode{
    int key;
    Color color;
    RedBlackTreeNode* leftChild, *rightChild, *parent;
};

class RedBlackTree {
public:
    RedBlackTree();
    ~RedBlackTree();
private:
    RedBlackTreeNode* root;
};


#endif //_RED_BLACK_TREE_REDBLACKTREE_H_
