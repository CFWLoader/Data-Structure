#include "FibonacciHeapNode.h"

#include <iostream>

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

	if(left != nullptr)
	{
		left->releaseRight();										//Set right's left to nullptr for breaking the loop.
																	//Normally setting right will lead to a wrong delete operation.
																	//I made a special function for this.

		left = nullptr;												//Notice that the brother relationship is a loop in F-Heap.
																	//So I simply set the left to nullptr and do delete operation on right.
	}	

	if(right != this && right != nullptr)							//Notice that the right and left may be self.
	{
		delete right;

		right = nullptr;
	}

	std::cout << "Correctly deleting node, key:  " << this->key << std::endl;

	//right = nullptr;
}


void FibonacciHeapNode::setChild(FibonacciHeapNode* newChild)
{
	if(newChild == nullptr)
	{
		degree = 0;
	}
	else
	{
		degree = 0;

		FibonacciHeapNode* iterator = newChild, *loopEnd = newChild;

		do
		{
			iterator->setParent(this);

			this->increaseDegree();

			iterator = iterator->getRight();
		}while(iterator->getRight() != loopEnd);
	}

	this->child = newChild;
}

void FibonacciHeapNode::setLeft(FibonacciHeapNode* newLeft)
{
	FibonacciHeapNode* oldLeft = left;

	if(newLeft == nullptr)
	{
		if(parent != nullptr)parent->decreaseDegree();

		oldLeft->getLeft()->setRight(this);

		this->left = oldLeft->left;
	} 
	else
	{
		newLeft->setParent(this->parent);

		newLeft->setLeft(oldLeft->getLeft());

		newLeft->setRight(this);

		oldLeft->getLeft()->setRight(newLeft);

		this->left = newLeft;

		//FibonacciHeapNode* oldLeft = this->left;

	}
	
	//his->left = newLeft;
}

void FibonacciHeapNode::setRight(FibonacciHeapNode* newRight)
{
	/*
	FibonacciHeapNode* oldRight = right;

	if(newRight == nullptr)
	{
		if(parent != nullptr)parent->decreaseDegree();

		oldRight->getRight()->setLeft(this);

		this->right = oldRight->right;
	} 
	else
	{
		newRight->setParent(this->parent);

		newRight->setRight(oldRight->getRight());

		newRight->setLeft(this);

		oldRight->getRight()->setLeft(newRight);

		this->right = newRight;

		//FibonacciHeapNode* oldRight = this->left;

	}

	oldRight->setLeft(oldRight);

	oldRight->setRight(oldRight);
	*/
	this->right = newRight;
}

void FibonacciHeapNode::detach()
{
	parent = nullptr;

	child = nullptr;

	left = nullptr;

	right = nullptr;

	degree = 0;
}