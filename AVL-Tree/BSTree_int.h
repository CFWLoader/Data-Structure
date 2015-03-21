/* 
 * File:   BSTree.h
 * Author: cfwloader
 *
 * Created on November 19, 2014, 3:33 PM
 */

#ifndef BSTREE_INT_H
#define	BSTREE_INT_H

#include<iostream>
#include<string>

struct BST
{
    int _key;
    BST *lchild;
    BST *rchild;
    BST():_key(0),lchild(0),rchild(0){}
    const BST& operator=(const BST& bst){_key = bst._key; lchild = bst.lchild; rchild = bst.rchild;}
    friend std::ostream& operator<<(std::ostream&,const BST&);//{os<<"key: "<<_key<<"  Left Child Address: "<<lchild<<"  Right Child Address: "<<rchild<<std::endl;return os;}
};

class BSTree {
    
public:
    BSTree();
    BSTree(const BSTree&);
    virtual ~BSTree();
    
    void Establish_the_tree();
    int Insert(const int&);
    int Show_Tree();
    
private:
    BST* _root;
    int _nodes_num;
    
    void Inorder(BST*&);
    void Inorder_delete(BST*&);
};


#endif	/* BSTREE_H */

