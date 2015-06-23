#include "FibonacciHeapNode.h"

FibonacciHeapNode::FibonacciHeapNode(unsigned long theKey) :
	parent(nullptr), child(nullptr), left(this), right(this), 
	key(theKey), degree(0), markFlag(false)
{}

FibonacciHeapNode::~FibonacciHeapNode()
{
	parent = nullptr;

	if(child != nullptr)
	{
		delete child;

		child = nullptr;
	}

	left = nullptr;												//Notice that the brother relationship is a loop in F-Heap.
																//So I simply set the left to nullptr and do delete operation on right.
	/*
	if(right != this && right != nullptr)						//Notice that the right and left may be self.
	{
		delete right;

		right = nullptr;
	}
	*/

	right = nullptr;
}


void FibonacciHeapNode::setChild(FibonacciHeapNode* newChild)
{
	this->child = newChild;

	newChild->setParent(this);
}

void FibonacciHeapNode::detach()
{
	parent = nullptr;

	child = nullptr;

	left = nullptr;

	right = nullptr;
}