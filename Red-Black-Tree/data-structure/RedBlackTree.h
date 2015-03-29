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

    RedBlackTreeNode(int);

    RedBlackTreeNode(int, Color);

    RedBlackTreeNode(const RedBlackTreeNode&);

    //Caution: The destructor just delete the node itself.
    //You should design an algorithm for cascade delete.
    ~RedBlackTreeNode();
};

class RedBlackTree {
public:
    RedBlackTree();
    ~RedBlackTree();
    void testDestructor();
    void redBlackInsert(RedBlackTreeNode*);
private:
    void leftRotate(RedBlackTreeNode*&);
    void rightRotate(RedBlackTreeNode*&);
    void cascadeDeleter(RedBlackTreeNode*&);
    void insertFixer(RedBlackTreeNode*&);

    RedBlackTreeNode* root;
};


#endif //_RED_BLACK_TREE_REDBLACKTREE_H_
