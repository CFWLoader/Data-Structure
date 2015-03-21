/* 
 * File:   BSTree.cpp
 * Author: cfwloader
 * 
 * Created on November 19, 2014, 9:25 AM
 */
#include "BSTree_int.h"

std::ostream& operator<<(std::ostream& os,const BST& bst_node)
{
    os<<"key: "<<bst_node._key<<"  Left Child Address: "<<bst_node.lchild<<"  Right Child Address: "<<bst_node.rchild<<std::endl;
    return os;
}


BSTree::BSTree():_root(0),_nodes_num(0){}

BSTree::BSTree(const BSTree& org_tree):_root(org_tree._root),_nodes_num(org_tree._nodes_num){}

BSTree::~BSTree()
{
    if(_nodes_num>0)Inorder_delete(_root);
    _nodes_num = 0;
}

void BSTree::Inorder_delete(BST*& __ptr)
{
    if(__ptr)
    {
        Inorder_delete(__ptr->lchild);
        Inorder_delete(__ptr->rchild);
        delete __ptr;
        __ptr = 0;
    }
}

void BSTree::Inorder(BST*& __ptr)
{
    if(__ptr)
    {
        this->Inorder(__ptr->lchild);
	std::cout<<__ptr->_key<<std::endl;
	this->Inorder(__ptr->rchild);
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

void BSTree::Establish_the_tree()
{
    int data;
    while(std::cin>>data && data!=-255)
    {
        this->Insert(data);
        //std::cout<<_root<<std::endl;
    }
    //std::cout<<_root->_key<<std::endl;
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

int BSTree::Insert(const int& _data)
{
    BST* ptr = new BST();  
    if(NULL == ptr)return -1;
    ptr->_key = _data;
    //ptr->lchild = NULL;
    //ptr->rchild = NULL;
    if(0 == _root)
    {
        _root = ptr;
        ++_nodes_num;
        ptr = 0;
        return 0;
    }
    BST* movep,*temp;
    movep = _root;
    while(movep != NULL)
    {
        //if(movep->_key == ptr->_key)
        //    return -1;
        temp = movep;
        std::cout<<"Comparing "<<movep->_key<<" Data Larger? "<<(movep->_key < _data)<<std::endl;
        //std::cout<<*movep<<std::endl;
        movep = (movep->_key < _data)? movep->lchild : movep->rchild;
        if(movep == temp->lchild)std::cout<<"Chose Left.";
        else std::cout<<"Chose Right.";
    }
    if(temp->_key > _data){
        std::cout<<"Insert to lchild."<<std::endl;
        temp->lchild = ptr;
    }
    else{
        std::cout<<"Insert to rchild."<<std::endl;
        temp->rchild = ptr;
    }
    ++_nodes_num;
    ptr = movep = temp = 0;
    return 0;
}

int BSTree::Show_Tree()
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
