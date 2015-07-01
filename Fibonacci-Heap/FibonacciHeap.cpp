#include "FibonacciHeapNode.h"

#include "FibonacciHeap.h"

#include <vector>

FibonacciHeap::FibonacciHeap() : root(nullptr)
{
}

FibonacciHeap::~FibonacciHeap()
{
	delete root;
}

bool FibonacciHeap::insert(unsigned long newKey)
{
	FibonacciHeapNode* newNode = new FibonacciHeapNode(newKey);

	this->updateRoots(newNode);

	return true;
}

bool FibonacciHeap::insert(FibonacciHeapNode* theNewNode)
{
	return this->updateRoots(theNewNode);
}

bool FibonacciHeap::updateRoots(FibonacciHeapNode* newNode)
{
	if(root == nullptr)
	{
		root = newNode;

		return true;
	}

	FibonacciHeapNode* iterator = root->getRight();

	while((iterator != root) && (newNode->getDegree() > iterator->getDegree()))
	{
		iterator = iterator->getRight();
	}

	/*

	newNode->setRight(iterator);

	newNode->setLeft(iterator->getLeft());

	newNode->getLeft()->setRight(newNode);
	*/

	if(newNode->getDegree() < iterator->getDegree())
	{
		iterator->setLeft(newNode);
	}
	else 
	{
		iterator->setRight(newNode);
	}

	if(iterator == root && newNode->getDegree() < iterator->getDegree())
	{
		root = newNode;
	}

	return true;
}

bool FibonacciHeap::unionHeap(FibonacciHeap* unioningHeap)
{
	root->getLeft()->concatenateRight(unioningHeap->root);

	return true;
}

unsigned long FibonacciHeap::phi()
{
	return 0;
}