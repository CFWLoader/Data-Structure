#include "FibonacciHeapNode.h"

#include "FibonacciHeap.h"

#include <deque>

#include <iostream>

#include <cmath>

#include <vector>

#include <algorithm>

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

bool FibonacciHeap::isExistedInRootList(FibonacciHeapNode* checkingNode)
{
	FibonacciHeapNode* iterator = this->root;

	do
	{
		if(iterator == checkingNode)return true;

		iterator = iterator->getRight();
	}while(iterator != root);

	return false;
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

bool FibonacciHeap::cut(FibonacciHeapNode* childNode, FibonacciHeapNode* parentNode)
{
	if(childNode->getRight() == childNode)
	{
		parentNode->setChild(nullptr);
	}
	else
	{
		childNode->getRight()->setLeft(nullptr);
	}

	root->getLeft()->setRight(childNode);

	childNode->setParent(nullptr);

	parentNode->setMarkFlag(false);

	return true;
}

bool FibonacciHeap::cascadingCut(FibonacciHeapNode* cuttingNode)
{
	FibonacciHeapNode* nodeRecord = cuttingNode->getParent();

	if(nodeRecord != nullptr)
	{
		if(cuttingNode->isMarked() == false)
		{
			cuttingNode->setMarkFlag(true);
		}
		else
		{
			this->cut(cuttingNode, nodeRecord);

			this->cascadingCut(nodeRecord);
		}
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

	FibonacciHeapNode* current = nullptr, *adjusting = nullptr;

	FibonacciHeapNode* rootIter = root;

	do 		 																			//Start adjusting the heap.
	{
		rootContainer.push_back(rootIter);												//The root may be changed to a child node.
																						//So we should use a containter.
		rootIter = rootIter->getRight();												//To prevent the root being changed to be a child.

	}while(rootIter->getRight() != root);

	unsigned long currentDegree;

	std::deque<FibonacciHeapNode*>::iterator rootIterator, end;

	FibonacciHeapNode* tempChild_;

	unsigned long tempKey_;

	for(rootIterator = rootContainer.begin(), end = rootContainer.end();
		rootIterator != end;
		++rootIterator)
	{
		current = *rootIterator;

		if(current->getParent() != nullptr)continue;

		//rootContainer.pop_front();

		currentDegree = current->getDegree();

		while(assistance[currentDegree] != nullptr)
		{

			adjusting = assistance[currentDegree];

			if(current->getKey() > adjusting->getKey())
			{
				tempChild_ = current->getChild();

				if(tempChild_ != nullptr)tempChild_->setParent(nullptr);

				current->setChild(adjusting->getChild());

				adjusting->setChild(tempChild_);

				tempKey_ = current->getKey();

				current->setKey(adjusting->getKey());

				adjusting->setKey(tempKey_);
			}

			this->link(adjusting, current);

			rootContainer.erase(find(rootContainer.begin(), rootContainer.end(), adjusting));

			assistance[currentDegree] = nullptr;

			++currentDegree;
		}

		assistance[currentDegree] = current;

	}

	std::deque<FibonacciHeapNode*>::iterator targetRoot;							//Reset the root before add the left node.

	for(targetRoot = rootIterator = rootContainer.begin(), end = rootContainer.end();
		rootIterator != end;
		++rootIterator)
	{
		if((*targetRoot)->getParent() != nullptr || (*targetRoot)->getKey() > (*rootIterator)->getKey())
		{
			targetRoot = rootIterator;
		}
	}

	root = *targetRoot;

	for(unsigned long index = 0; index < upperBound; ++index)									//Checking the left.
	{
		if(assistance[index] != nullptr && !this->isExistedInRootList(assistance[index]))		//Add a new contriant -- check the node is in the root list.
		{
			root->getLeft()->setRight(assistance[index]);
		}
	}

	return true;
}

bool FibonacciHeap::link(FibonacciHeapNode* toBeChild, FibonacciHeapNode* toBeParent)
{

	toBeChild->getLeft()->setRight(nullptr);

	if(toBeParent->getChild() == nullptr)
	{
		toBeParent->setChild(toBeChild);
	}
	else
	{
		toBeParent->getChild()->concatenateRight(toBeChild);
	}

	toBeChild->setMarkFlag(false);

	return  true;
}

bool FibonacciHeap::decreaseKey(FibonacciHeapNode* targetNode, unsigned long newKey)
{
	if(newKey > targetNode->getKey())
	{
		std::cerr << "The new key is greater than the old key.Operation aborted." << std::endl;

		return false;
	}

	targetNode->setKey(newKey);

	FibonacciHeapNode* adjustingNode = targetNode->getParent();

	if(adjustingNode != nullptr && adjustingNode->getKey() > targetNode->getKey())
	{
		this->cut(targetNode, adjustingNode);

		this->cascadingCut(adjustingNode);
	}

	return true;
}

bool FibonacciHeap::deleteNode(FibonacciHeapNode* targetNode)
{
	this->decreaseKey(targetNode, 0);

	this->extractMin();

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