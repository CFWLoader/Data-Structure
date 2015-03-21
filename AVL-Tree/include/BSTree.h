#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include "TreeNode.h"

class BSTree
{
    public:
        BSTree();
        virtual ~BSTree();
        void inorder(std::ostream&) const;
        void inorder(std::ostream&, const TreeNode*) const;
        void traceInorder(std::ostream&) const;
        void traceInorder(std::ostream&, const TreeNode*, int) const;
        void insertToBSTree(int);
        void avlInsert(int);
        void avlInsert(TreeNode*&, int, bool&);
        void leftRotation(TreeNode*&, bool&);
        void rightRotation(TreeNode*&, bool&);
        int Depth() const;
        int Depth(const TreeNode*) const;
        TreeNode* search (int) const;
    protected:
    private:
        TreeNode* root;
};

#endif // BSTREE_H
