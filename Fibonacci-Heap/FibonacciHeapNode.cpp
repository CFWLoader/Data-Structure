#include "FibonacciHeapNode.h"

#include <iostream>
#include <limits>

unsigned long UL_INFINITY = std::numeric_limits<unsigned long>::max();

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

	//std::cout << "Correctly deleting node, key:  " << this->key << std::endl;

	//right = nullptr;
}

void FibonacciHeapNode::setParent(FibonacciHeapNode* newParent)
{
	if(newParent == nullptr)
	{
		FibonacciHeapNode* ptr = this->right;	

		while(ptr != this)
		{
			ptr->parent = nullptr;

			ptr = ptr->right;

			//std::cout << "Looping here: key:  " << this->key << std::endl;
		}
	}

	this->parent = newParent;
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

void FibonacciHeapNode::setLeft(FibonacciHeapNode* newLeft)			//Remove a left node if you pass a null value,parent node will decrease 1.
{																	//Insert a left node if you pass a non-null value and parent node will increase 1.
	//if(newLeft == this)return;

	FibonacciHeapNode* oldLeft = left;

	if(newLeft == nullptr)
	{
		//if(parent != nullptr)parent->decreaseDegree();

		oldLeft->left->right = this;

		this->left = oldLeft->left;

		if(parent != nullptr && parent->child == oldLeft)parent->setChild(this);

	} 
	else
	{
		/*

		newNode->setRight(iterator);

		newNode->setLeft(iterator->getLeft());

		newNode->getLeft()->setRight(newNode);
		*/
		newLeft->parent = this->parent;

		newLeft->right = this;

		newLeft->left = oldLeft;

		oldLeft->right = newLeft;

		//oldLeft->getLeft()->setRight(newLeft);

		this->left = newLeft;

		if(parent != nullptr)parent->increaseDegree();

		//FibonacciHeapNode* oldLeft = this->left;

	}
	
	//his->left = newLeft;
}

void FibonacciHeapNode::concatenateLeft(FibonacciHeapNode* newLeft)		//Remove a left node if you pass a null value,parent node will decrease 1.
{																		//Link the two bidirectional list.
																		//This function solved the problem of adding a segment of nodes.
	FibonacciHeapNode* oldLeft = left, *newLeftRight = newLeft->right;	

	if(newLeft == nullptr)
	{

		oldLeft->left->right = this;

		this->left = oldLeft->left;

		if(parent != nullptr && parent->child == oldLeft)parent->setChild(this);

	} 
	else
	{
		newLeft->parent = this->parent;

		newLeft->right = this;

		oldLeft->right = newLeftRight;

		newLeftRight->left = oldLeft;

		this->left = newLeft;

		if(parent != nullptr)
		{
			FibonacciHeapNode* iterator = newLeft;

			do
			{
				parent->increaseDegree();

				iterator = iterator->right;
			}while(iterator != newLeft);
		}
	}
}

void FibonacciHeapNode::setRight(FibonacciHeapNode* newRight)			//Behavior is same as setLeft function.
{
	FibonacciHeapNode* oldRight = right;

	if(newRight == nullptr)
	{

		oldRight->right->left = this;

		this->right = oldRight->right;

		if(parent != nullptr && parent->child == oldRight)parent->setChild(this);
	} 
	else
	{
		newRight->parent = this->parent;

		newRight->left = this;

		newRight->right = oldRight;

		oldRight->left = newRight;

		this->right = newRight;

		if(parent != nullptr)parent->increaseDegree();
	}
}

void FibonacciHeapNode::concatenateRight(FibonacciHeapNode* newRight)			//Behavior is same as concatenateLeft function.
{
	FibonacciHeapNode* oldRight = right, *newRightLeft = newRight->left;

	if(newRight == nullptr)
	{

		oldRight->right->left = this;

		this->right = oldRight->right;

		if(parent != nullptr && parent->child == oldRight)parent->setChild(this);
	} 
	else
	{
		newRight->parent = this->parent;

		newRight->left = this;

		//newRight->right = oldRight;

		oldRight->left = newRightLeft;

		newRightLeft->right = oldRight;

		this->right = newRight;

		if(parent != nullptr)
		{
			FibonacciHeapNode* iterator = newRight;

			do
			{
				parent->increaseDegree();

				iterator = iterator->right;
			}while(iterator != newRight);
		}
	}
}

void FibonacciHeapNode::detach()
{
	parent = nullptr;

	child = nullptr;

	left = nullptr;

	right = nullptr;

	degree = 0;
}