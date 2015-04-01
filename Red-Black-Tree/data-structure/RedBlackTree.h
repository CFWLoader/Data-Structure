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

    //static RedBlackTreeNode* NIL_PTR;

    RedBlackTreeNode(int);

    RedBlackTreeNode(int, Color);

    RedBlackTreeNode(const RedBlackTreeNode&);

    //Caution: The destructor just delete the node itself.
    //You should design an algorithm for cascade delete.
    ~RedBlackTreeNode();

    /*
private:
    RedBlackTreeNode();
     */
};

class RedBlackTree {
public:
    RedBlackTree();
    ~RedBlackTree();
    void redBlackInsert(RedBlackTreeNode*);
    RedBlackTreeNode* redBlackDelete(RedBlackTreeNode*);
    void showTree(std::ostream&) const;
    void showNode(std::ostream&, RedBlackTreeNode* const &, int) const;
private:
    void leftRotate(RedBlackTreeNode*);
    void rightRotate(RedBlackTreeNode*);
    void cascadeDeleter(RedBlackTreeNode*&);
    void insertFixer(RedBlackTreeNode*);
    void deleteFixer(RedBlackTreeNode*);
    //This function cost me some time to understand.
    RedBlackTreeNode* successor(RedBlackTreeNode*);

    RedBlackTreeNode* root;
};


#endif //_RED_BLACK_TREE_REDBLACKTREE_H_
