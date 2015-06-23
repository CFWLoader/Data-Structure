#include "FibonacciHeapNode.h"

#include "FibonacciHeap.h"

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

	newNode->setRight(iterator);

	newNode->setLeft(iterator->getLeft());

	newNode->getLeft()->setRight(newNode);

	iterator->setLeft(newNode);

	return true;
}