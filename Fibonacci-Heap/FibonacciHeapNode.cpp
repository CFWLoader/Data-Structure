#include "FibonacciHeapNode.h"

FibonacciHeapNode::FibonacciHeapNode(unsigned long theKey) :
	parent(nullptr), child(nullptr), left(nullptr), right(nullptr), 
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

	if(right != nullptr)
	{
		delete right;

		right = nullptr;
	}
}