/* 
 * File:   BSTree.cpp
 * Author: cfwloader
 * 
 * Created on November 19, 2014, 9:25 AM
 */
#include "BSTree.h"

template<typename UserDefineDataStructure>
BSTree<UserDefineDataStructure>::BSTree():_root(0),_nodes_num(0){}

template<typename UserDefineDataStructure>
BSTree<UserDefineDataStructure>::BSTree(const BST<UserDefineDataStructure>& org_tree):_root(org_tree._root),_nodes_num(org_tree._nodes_num){}

template<typename UserDefineDataStructure>
BSTree<UserDefineDataStructure>::~BSTree()
{
    if(_nodes_num>0)Inorder_delete(_root);
    _nodes_num = 0;
}

template<typename UserDefineDataStructure>
void BSTree<UserDefineDataStructure>::Inorder_delete(BST<UserDefineDataStructure>*& __ptr)
{
    if(__ptr)
    {
        Inorder_delete(__ptr->lchild);
        Inorder_delete(__ptr->rchild);
        delete __ptr;
        __ptr = 0;
    }
}

template<typename UserDefineDataStructure>
void BSTree<UserDefineDataStructure>::Inorder(const BST<UserDefineDataStructure>*& __ptr)
{
    if(__ptr)
    {
        Inorder(__ptr->lchild);
	std::cout<<__ptr->_key<<std::endl;
	Inorder(__ptr->rchild);
    }
}

/*
void Inorder(BST *ptr)
{
    if(ptr)
    {
        Inorder(ptr->lchild);
	std::cout<<ptr->_key<<std::endl;
	Inorder(ptr->rchild);
    }
}
*/

template<typename UserDefineDataStructure>
void BSTree<UserDefineDataStructure>::Establish_the_tree()
{
    UserDefineDataStructure data;
    while(std::cin>>data && data!=-255)
    {
        this->Insert(data);
        std::cout<<_root<<std::endl;
    }
    std::cout<<_root->_key<<std::endl;
    return;
}

/*
void Create_BSTree(BST *root)
{
	root=NULL;
	int data;
	while(std::cin>>data&&data!=-255)
	{
		BST_Insert(root,data);
		std::cout<<root<<std::endl;
	}
	std::cout<<root->_key<<std::endl;
}
*/

template<typename UserDefineDataStructure>
int BSTree<UserDefineDataStructure>::Insert(const UserDefineDataStructure& _data)
{
    BST<UserDefineDataStructure>* ptr = new BSTree<UserDefineDataStructure>();
    BST<UserDefineDataStructure>* movep,*temp;
    if(NULL==ptr)return;
    ptr->_key = _data;
    //ptr->lchild = NULL;
    //ptr->rchild = NULL;
    if(0==_root)
    {
        _root = ptr;
        ++_nodes_num;
        return 0;
    }
    movep = _root;
    while(movep!=NULL)
    {
        if(movep->_key==ptr->_key)
            return -1;
        temp=movep;
        movep=(movep->_key<_data)?movep->lchild:movep->rchild;
    }
    if(temp->_key>_data)
        temp->lchild=ptr;
    else
        temp->rchild=ptr;
    ++_nodes_num;
    return 0;
}

template<typename UserDefineDataStructure>
int BSTree<UserDefineDataStructure>::Show_Tree()
{
    this->Inorder(_root);
    return 0;
}

/*
void BST_Insert(BST *root,int data)
{
	BST* ptr=(BST*)malloc(sizeof(BST));
	BST* movep,*temp;
	if(NULL==ptr)return;
	ptr->_key=data;
	ptr->lchild=NULL;
	ptr->rchild=NULL;
	if(0==root)
	{
		root=ptr;
		return;
	}
	movep=root;
	while(movep!=NULL)
	{
		if(movep->_key==ptr->_key)
			return;
		temp=movep;
		movep=(movep->_key<data)?movep->lchild:movep->rchild;
	}
	if(temp->_key>data)
		temp->lchild=ptr;
	else
		temp->rchild=ptr;
}
*/
