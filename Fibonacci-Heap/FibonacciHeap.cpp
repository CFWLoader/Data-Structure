#include "FibonacciHeapNode.h"

#include "FibonacciHeap.h"

#include <deque>

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

unsigned long FibonacciHeap::extractMin()
{
	if(root == nullptr)return UL_INFINITY;

	FibonacciHeapNode* iterator = root, *target = root;									//Find the minimum value.

	do
	{
		if(iterator->getKey() < target->getKey())
		{
			target = iterator;
		}

		iterator = iterator->getRight();
	}while(iterator != root);

	unsigned long targetValue = target->getKey();

	if (target->getChild() != nullptr)													//If target node has child, add them to root list.
	{
		root->getLeft()->concatenateRight(target->getChild());

		target->getChild()->setParent(nullptr);

		target->setChild(nullptr);
	}

	if(target == root)																	//Before deleting the node, check if the root is the target.
	{																					//Checking whether the root is the last node.
		if(root == root->getRight())
		{
			root = nullptr;
		} 
		else
		{  
			root = root->getRight();

			this->consolidate();														//Adjust the heap because the root changed.
		}
	}

	target->getLeft()->setRight(nullptr);

	target->detach();

	delete target;

	return targetValue;

}

bool FibonacciHeap::consolidate()
{
	return true;
}

size_t FibonacciHeap::getMaxDegreeOfSingleNodeInTheHeap() const
{
	if(root == nullptr)return 0;

	size_t maxDegree = root->getDegree();

	std::deque<FibonacciHeapNode*> searchQueue;

	searchQueue.push_back(root);

	FibonacciHeapNode* iterator, *loopEnd;

	while(!searchQueue.empty())
	{
		iterator = searchQueue.front();

		searchQueue.pop_front();

		loopEnd = iterator;

		do
		{
			if(maxDegree < iterator->getDegree())maxDegree = iterator->getDegree();

			iterator = iterator->getRight();
		}while(iterator != loopEnd);
	}

	return maxDegree;
}


unsigned long FibonacciHeap::phi()
{
	return 0;
}