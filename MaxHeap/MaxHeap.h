/*
 * File:   MaxHeap.h
 * Author: cfwloader
 *
 * Created on October 9, 2014, 9:34 PM
 */

#ifndef MAXHEAP_H
#define	MAXHEAP_H

template<typename InnerDataStructure>
struct Node
{
    InnerDataStructure item;
    Node *parent,*lchild,*rchild;
    Node():parent(0),lchild(0),rchild(0){}
    const Node<InnerDataStructure>& operator=(const Node<InnerDataStructure>& org_node){
        this->parent = org_node.parent;
        this->lchild = org_node.lchild;
        this->rchild = org_node.rchild;
        return *this;
    }
};

template<typename T>
class MaxHeap
{
private:
    int node_number;
    Node<T>* _root;
    int height(Node<T>*&);
    Node<T>* Find_minor_position(Node<T>*,const T&);
    bool Delete_the_node(Node<T>*&);
    void Preorder_executor(Node<T>*&,int);
    int Nodes_counter(Node<T>*&);
public:
    MaxHeap();
    ~MaxHeap();
    bool IsEmpty();
    bool IsFull();
    bool Insert(const T& item);
    T Delete();
    int Get_nodes_number();
    void Preorder();
};

#endif	/* MAXHEAP_H */

