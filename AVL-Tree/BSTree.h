/* 
 * File:   BSTree.h
 * Author: cfwloader
 *
 * Created on November 19, 2014, 3:33 PM
 */

#ifndef BSTREE_H
#define	BSTREE_H

#include<iostream>
#include<string>

template<typename UserDefineDataStructure>
struct BST
{
    UserDefineDataStructure _key;
    BST<UserDefineDataStructure> *lchild;
    BST<UserDefineDataStructure> *rchild;
    BST():_key(0),lchild(0),rchild(0){}
    const BST& operator=(const BST<UserDefineDataStructure>& bst){_key = bst._key; lchild = bst.lchild; rchild = bst.rchild;}
    std::ostream& operator<<(std::ostream& os){os<<"key: "<<_key<<"  Left Child Address: "<<lchild<<"  Right Child Address: "<<rchild<<std::endl;return os;}
};

template<typename UserDefineDataStructure>
class BSTree {
    
public:
    BSTree();
    BSTree(const BST<UserDefineDataStructure>&);
    virtual ~BSTree();
    
    void Establish_the_tree();
    int Insert(const UserDefineDataStructure&);
    int Show_Tree();
    
private:
    BST<UserDefineDataStructure>* _root;
    int _nodes_num;
    
    void Inorder(const BST<UserDefineDataStructure>*&);
    void Inorder_delete(BST<UserDefineDataStructure>*&);
};


#endif	/* BSTREE_H */

