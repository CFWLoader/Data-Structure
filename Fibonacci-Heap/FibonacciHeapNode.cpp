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
		left->setRight(nullptr);									//Set right's left to nullptr for breaking the loop.

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
	if(parent != nullptr)
	{
		HeapNode* ptr = nullptr;

		ptr = left;

		while(ptr != nullptr)
		{
			parent->decreaseDegree();

			ptr->setParent(nullptr);

			ptr = ptr->getBrother();
		}

		if(newBrother == nullptr)
		{
			ptr = brother;
		}
		else 
		{
			ptr = newBrother;
		
			while(ptr != nullptr)
			{
				parent->increaseDegree();

				ptr->setParent(parent);

				ptr = ptr->getBrother();
			}
		}
	}
	
	brother = newBrother;
}

void FibonacciHeapNode::setRight(FibonacciHeapNode* newRight)
{
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