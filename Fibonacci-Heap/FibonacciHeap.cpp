#include "FibonacciHeapNode.h"

#include "FibonacciHeap.h"

#include <deque>

//#include <iostream>

#include <cmath>

#include <vector>

#include <utility>

FibonacciHeap::FibonacciHeap() : root(nullptr), numberOfNodes(0)
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

	++numberOfNodes;

	return true;
}

bool FibonacciHeap::insert(FibonacciHeapNode* theNewNode)
{
	++numberOfNodes;

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

	this->numberOfNodes += unioningHeap->numberOfNodes;

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

	--numberOfNodes;

	return targetValue;

}

//The upper bound used a thoerem: Single node's degree will never be greater than the number of nodes in the heap.
bool FibonacciHeap::consolidate()
{
	double tempResult_ = ::log(static_cast<double>(numberOfNodes)) / ::log(2.0);

	unsigned long upperBound = static_cast<unsigned long>(tempResult_) + ((tempResult_ >  static_cast<unsigned long>(tempResult_)) ? 1 : 0); 

	//std::cout << "The upper Bound is " << upperBound << std::endl;

	std::vector<FibonacciHeapNode*> assistance(upperBound, nullptr);

	std::deque<FibonacciHeapNode*> rootContainer;

	//Completion of initializing the assist array.

	FibonacciHeapNode* rootIterator = root, *current = nullptr, *adjusting = nullptr;

	do 		 																				//Start adjusting the heap.
	{
		rootContainer.push_back(rootIterator);												//The root may be changed to a child node.
																							//So we should use a containter.
		rootIterator = rootIterator->getRight();											//To prevent the root being changed to be a child.

	}while(rootIterator->getRight() != root);

	unsigned long currentDegree;

	while(!rootContainer.empty())
	{
		current = rootContainer.front();

		rootContainer.pop_front();

		currentDegree = current->getDegree();

		while(assistance[currentDegree] != nullptr)
		{
			adjusting = assistance[currentDegree];

			if(current->getKey() > adjusting->getKey())
			{
				std::swap(current, adjusting);
			}

			root = this->link(adjusting, current);

			assistance[currentDegree] = nullptr;

			++currentDegree;
		}

		assistance[currentDegree] = current;

	}

	for(unsigned long index = 0; index < upperBound; ++index)									//Checking the left.
	{
		if(assistance[index] != nullptr)
		{
			root->getLeft()->concatenateRight(assistance[index]);
		}
	}

	return true;
}

FibonacciHeapNode* FibonacciHeap::link(FibonacciHeapNode* toBeChild, FibonacciHeapNode* toBeParent)
{
	toBeChild->getLeft()->setRight(nullptr);

	toBeChild->isolate();

	if(toBeParent->getChild() == nullptr)
	{
		toBeParent->setChild(toBeChild);
	}
	else
	{
		toBeParent->getChild()->setRight(toBeChild);
	}

	return toBeParent;
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