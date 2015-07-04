#include "FibonacciHeapNode.h"

#include "FibonacciHeap.h"

#include <deque>

#include <iostream>

#include <cmath>

#include <vector>

#include <algorithm>

//#include <utility>

//#define DEBUG_FUN_LINK

//#define DEBUG_FUN_CONSOLIDATE

//#define DEBUG_FUN_CONSOLIDATE_AFTER

//#define DEBUG_FUN_CONSOLIDATE_SWAP

#ifdef DEBUG_FUN_LINK

#include "Auxiliary.h"

#include "GraphvizOutput.h"

#include <string>

unsigned long linkFunCounter = 0;

#endif


#ifdef DEBUG_FUN_CONSOLIDATE

#include "Auxiliary.h"

#include "GraphvizOutput.h"

#include <string>

unsigned long consolidateFunCounter = 0;

#endif

#ifdef DEBUG_FUN_CONSOLIDATE_SWAP

#include "Auxiliary.h"

#include "GraphvizOutput.h"

#include <string>

unsigned long consolidateFunCounter = 0;

#endif

#ifdef DEBUG_FUN_CONSOLIDATE_AFTER

#include "Auxiliary.h"

#include "GraphvizOutput.h"

#include <string>

unsigned long consolidateFunCounter = 0;

#endif

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

#ifdef DEBUG_FUN_CONSOLIDATE

	++consolidateFunCounter;

	std::string consolidateStatusCounter = "./diagram/F-Heap-Consolidate-status";

	char statusCounter[20];

	GraphvizOutput debugOutput(consolidateStatusCounter + "a.dot");

	unsigned long localStatusCounter = 0;

	/*
	_itoa_s(consolidateFunCounter, statusCounter, 10);

	linkStatusCounter.append(statusCounter);

	GraphvizOutput debugOutput(consolidateStatusCounter + "a.dot");

	debugOutput.generateDebuggingGraph(root);
	*/

	//std::cout << "P-Key: " << toBeParent->getKey() << "   C-Key: " << toBeChild->getKey() << std::endl;

#endif

#ifdef DEBUG_FUN_CONSOLIDATE_SWAP

	++consolidateFunCounter;

	std::string consolidateStatusCounter = "./diagram/F-Heap-Consolidate-status-swap";

	char statusCounter[20];

	GraphvizOutput debugOutput(consolidateStatusCounter + "a.dot");

	unsigned long localStatusCounter = 0;

#endif

#ifdef DEBUG_FUN_CONSOLIDATE_AFTER

	++consolidateFunCounter;

	std::string consolidateStatusCounter = "./diagram/F-Heap-Consolidate-status-";

	char statusCounter[20];

	GraphvizOutput debugOutput(consolidateStatusCounter + "a.dot");

	unsigned long localStatusCounter = 0;

#endif

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

#ifdef DEBUG_FUN_CONSOLIDATE

	++localStatusCounter;

	std::string theRealStatus = consolidateStatusCounter;

	_itoa_s(consolidateFunCounter, statusCounter, 10);

	theRealStatus.append(statusCounter);

	theRealStatus.append("-local-");

	_itoa_s(localStatusCounter, statusCounter, 10);

	theRealStatus.append(statusCounter);

	debugOutput.resetFile(theRealStatus + "a.dot");

	debugOutput.generateDebuggingGraph(current);

	/*
	debugOutput.resetFile(theRealStatus + "-root-a.dot");

	debugOutput.generateDebuggingGraph(root);
	*/

#endif
			adjusting = assistance[currentDegree];

			if(current->getKey() > adjusting->getKey())
			{

#ifdef DEBUG_FUN_CONSOLIDATE_SWAP

	++localStatusCounter;

	std::string theRealStatus = consolidateStatusCounter;

	_itoa_s(consolidateFunCounter, statusCounter, 10);

	theRealStatus.append(statusCounter);

	theRealStatus.append("-local-");

	_itoa_s(localStatusCounter, statusCounter, 10);

	theRealStatus.append(statusCounter);

	debugOutput.resetFile(theRealStatus + "a.dot");

	debugOutput.generateDebuggingGraph(current);

	std::cout << "Swapping: " << current->getKey() << "   " << adjusting->getKey() << std::endl;

#endif
				tempChild_ = current->getChild();

				if(tempChild_ != nullptr)tempChild_->setParent(nullptr);

				current->setChild(adjusting->getChild());

				adjusting->setChild(tempChild_);

				tempKey_ = current->getKey();

				current->setKey(adjusting->getKey());

				adjusting->setKey(tempKey_);
				//std::swap(current, adjusting);

#ifdef DEBUG_FUN_CONSOLIDATE_SWAP

	std::string theAfterStatus = consolidateStatusCounter;

	_itoa_s(consolidateFunCounter, statusCounter, 10);

	theAfterStatus.append(statusCounter);

	theAfterStatus.append("-local-");

	_itoa_s(localStatusCounter, statusCounter, 10);

	theAfterStatus.append(statusCounter);

	debugOutput.resetFile(theRealStatus + "b.dot");

	debugOutput.generateDebuggingGraph(current);

#endif
			}

			this->link(adjusting, current);

			rootContainer.erase(find(rootContainer.begin(), rootContainer.end(), adjusting));

#ifdef DEBUG_FUN_CONSOLIDATE

	std::string theAfterStatus = consolidateStatusCounter;

	_itoa_s(consolidateFunCounter, statusCounter, 10);

	theAfterStatus.append(statusCounter);

	theAfterStatus.append("-local-");

	_itoa_s(localStatusCounter, statusCounter, 10);

	theAfterStatus.append(statusCounter);

	debugOutput.resetFile(theRealStatus + "b.dot");

	debugOutput.generateDebuggingGraph(current);

	/*
	debugOutput.resetFile(theRealStatus + "-root-b.dot");

	debugOutput.generateDebuggingGraph(root);
	*/

#endif

			assistance[currentDegree] = nullptr;

			++currentDegree;
		}

		assistance[currentDegree] = current;

	}

#ifdef DEBUG_FUN_CONSOLIDATE

	std::cout << "Main of consolidation finished." << std::endl;

#endif

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
/*
#ifdef DEBUG_FUN_CONSOLIDATE_AFTER

	std::string theSelectedStatus = consolidateStatusCounter;

	_itoa_s(consolidateFunCounter, statusCounter, 10);

	theSelectedStatus.append(statusCounter);

	debugOutput.resetFile(theSelectedStatus + "sel.dot");

	debugOutput.generateDebuggingGraph(root);

#endif
*/

	for(unsigned long index = 0; index < upperBound; ++index)									//Checking the left.
	{
		if(assistance[index] != nullptr && !this->isExistedInRootList(assistance[index]))		//Add a new contriant -- check the node is in the root list.
		{
			root->getLeft()->setRight(assistance[index]);
		}
	}

#ifdef DEBUG_FUN_CONSOLIDATE

	std::string theFinishedStatus = consolidateStatusCounter;

	_itoa_s(consolidateFunCounter, statusCounter, 10);

	theFinishedStatus.append(statusCounter);

	debugOutput.resetFile(theFinishedStatus + "fin.dot");

	debugOutput.generateDebuggingGraph(*targetRoot);

#endif

	return true;
}

bool FibonacciHeap::link(FibonacciHeapNode* toBeChild, FibonacciHeapNode* toBeParent)
{
#ifdef DEBUG_FUN_LINK

	++linkFunCounter;

	std::string linkStatusCounter = "./diagram/F-Heap-Link-status";

	char statusCounter[20];

	_itoa_s(linkFunCounter, statusCounter, 10);

	linkStatusCounter.append(statusCounter);

	GraphvizOutput debugOutput(linkStatusCounter + "a.dot");

	debugOutput.generateDebuggingGraph(toBeParent);

	std::cout << "P-Key: " << toBeParent->getKey() << "   C-Key: " << toBeChild->getKey() << std::endl;

#endif

	toBeChild->getLeft()->setRight(nullptr);
	//toBeChild->isolate();

#ifdef DEBUG_FUN_LINK

	debugOutput.resetFile(linkStatusCounter + "b.dot");

	debugOutput.generateDebuggingGraph(toBeParent);

#endif

	if(toBeParent->getChild() == nullptr)
	{
		toBeParent->setChild(toBeChild);
	}
	else
	{
		toBeParent->getChild()->concatenateRight(toBeChild);
	}

	toBeChild->setMarkFlag(false);

#ifdef DEBUG_FUN_LINK

	debugOutput.resetFile(linkStatusCounter + "c.dot");

	debugOutput.generateDebuggingGraph(toBeParent);

#endif

	return  true;
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