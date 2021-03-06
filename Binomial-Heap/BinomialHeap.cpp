#include "BinomialHeap.h"

#include <limits>
#include <vector>
#include <algorithm>
#include <iostream>

#include "GraphvizOutput.h"
#include "Auxiliary.h"

//#define DEBUGGING

//#define EXTRACTMIN_DEBUGGING

#ifdef EXTRACTMIN_DEBUGGING

unsigned long extractMinCounter = 0;

#endif

bool degreeLess(HeapNode* a, HeapNode* b)										//For sorting the roots of heap via generic algorithm.
{
	return a->getDegree() < b->getDegree();
}

const unsigned long ULONG_INF = std::numeric_limits<unsigned long>::max();		//Define maximum value as the bound of the system.

BinomialHeap::BinomialHeap() : root(nullptr), minKeyNode(nullptr)				//Empty constructor.
{}

BinomialHeap::BinomialHeap(HeapNode* settingRoot) : root(settingRoot), minKeyNode(nullptr)
{}																				//For a constructed heap.

BinomialHeap::~BinomialHeap()													//Implicitly deleting the heap.
{
	if(root != nullptr)
	{
		delete root;

		root = nullptr;
	}
}

void BinomialHeap::detach()														//In case of delivering to another heap.
{
	root = nullptr;

	minKeyNode = nullptr;
}

unsigned long BinomialHeap::minimum()											//Get minimum key in the heap without deleting it.
{
	unsigned long result = ULONG_INF;

	HeapNode* ptr = root;

	while(ptr != nullptr)														//The minimum key must exist in roots.
	{
		if(result > ptr->getKey())
		{
			minKeyNode = ptr;

			result = minKeyNode->getKey();
		}

		ptr = ptr->getBrother();
	}

	return result;
}

BinomialHeap* BinomialHeap::unionHeap(BinomialHeap* bHeap)
{
	BinomialHeap* newHeap = this->merge(bHeap);

	HeapNode* ptr = newHeap->root, *prevs = nullptr, *next = nullptr;			//Visiting the heap via three pointer.

	if(ptr == nullptr)return newHeap;

	next = ptr->getBrother();

#ifdef DEBUGGING

	std::string basename("./diagram/unioningHeap");

	int stateCounter = 1;

	char stateCounterStr[20];

#endif

	while(next != nullptr)														//Cases are in page 284.
	{

#ifdef DEBUGGING

		std::string stateName(basename.begin(), basename.end());

		_itoa_s(stateCounter, stateCounterStr, 10);

		stateName.append(stateCounterStr);

		stateName.append(".dot");

		GraphvizOutput stateQuickShot(stateName);

#endif

		if((ptr->getDegree() != next->getDegree()) || 															//Case 1
			(next->getBrother() != nullptr && next->getBrother()->getDegree() == ptr->getDegree()))				//Case 2
		{
			prevs = ptr;

			ptr = next;
		}
		else if(ptr->getKey() <= next->getKey())																//Case 3
		{
			ptr->setBrother(next->getBrother());

			//stateQuickShot.generateDirectionalGraph(next);

			next->link(ptr);

			//stateQuickShot.generateDirectionalGraph(ptr);

		}
		else																									//Case 4
		{
			if(prevs == nullptr) newHeap->root = next;
			else prevs->setBrother(next);

			ptr->link(next);

			ptr = next;
		}

#ifdef DEBUGGING

		stateQuickShot.generateDirectionalGraph(newHeap->getRoot());

		++stateCounter;

#endif

		next = ptr->getBrother();
	}

	return newHeap;
}

BinomialHeap* BinomialHeap::merge(BinomialHeap* bHeap)
{
	BinomialHeap* mergedHeap;

	std::vector<HeapNode*> nodeContainer;

	HeapNode* ptr = this->root, *prevs;											//Two heaps are being dealt respectively.

	while(ptr != nullptr)
	{
		prevs = ptr;

		nodeContainer.push_back(ptr);

		ptr = ptr->getBrother();

		prevs->setBrother(nullptr);												//Destroy roots' brother relation for sorting the heap roots.
	}

	ptr = bHeap->root;

	while(ptr != nullptr)
	{
		prevs = ptr;

		nodeContainer.push_back(ptr);

		ptr = ptr->getBrother();

		prevs->setBrother(nullptr);
	}

	std::sort(nodeContainer.begin(), nodeContainer.end(), degreeLess);			//Sorting.

	std::vector<HeapNode*>::const_iterator iter = nodeContainer.begin(), end = nodeContainer.end();

	if(iter != end)
	{
		ptr = *iter;

		++iter;
	}
	else																		//If the roots are nullptr.
	{
		ptr = nullptr;
	}

	mergedHeap = new BinomialHeap(ptr);

	while(iter != end)															//Reassemlying their brother relation.
	{
		ptr->setBrother(*iter);

		ptr = *iter;

		++iter;
	}

	/*

	GraphvizOutput mergeShot("./diagram/merging-quick-shot.dot");

	mergeShot.generateDirectionalGraph(mergedHeap->getRoot());

	*/

	return mergedHeap;
}

HeapNode* BinomialHeap::getRoot() const
{
	return root;
}

void BinomialHeap::insert(HeapNode* newNode)
{
	BinomialHeap* heapPie = new BinomialHeap();

	heapPie->root = newNode;

	heapPie = this->unionHeap(heapPie);											//Setting the new node as a heap for using the union operation.

	root = heapPie->root;

	heapPie->detach();

	delete heapPie;
}

unsigned long BinomialHeap::extractMin()
{

#ifdef EXTRACTMIN_DEBUGGING

	char number[20];

	std::string baseName = "./diagram/extractMinQuickShot";

	++extractMinCounter;

	/*

	std::string beforeOperationStateName(baseName);

	_itoa_s(extractMinCounter, number, 10);

	beforeOperationStateName.append(number);

	beforeOperationStateName.append("-foreHeap");

	beforeOperationStateName.append(".dot");

	GraphvizOutput foreHeapStateQuickShot(beforeOperationStateName);

	foreHeapStateQuickShot.generateDirectionalGraph(this->getRoot());

	*/

#endif

	if(root == nullptr) return ULONG_INF;

	HeapNode* prev = root;

	minKeyNode = root;

	HeapNode* minPrev = prev;

	HeapNode* nodeIterator = prev->getBrother();

/*
#ifdef EXTRACTMIN_DEBUGGING

	std::string beforeOperationStateName(baseName);

	_itoa_s(extractMinCounter, number, 10);

	beforeOperationStateName.append(number);

	beforeOperationStateName.append("-foreHeap");

	beforeOperationStateName.append(".dot");

	GraphvizOutput foreHeapStateQuickShot(beforeOperationStateName);

	foreHeapStateQuickShot.generateDirectionalGraph(this->getRoot());

#endif
*/

	while(nodeIterator != nullptr)																//Find the minimum key in the roots.
	{
		if(nodeIterator->getKey() < minKeyNode->getKey())
		{
			minPrev = prev;

			minKeyNode = nodeIterator;
		}

		prev = nodeIterator;

		nodeIterator = nodeIterator->getBrother();
	}

	minPrev->setBrother(minKeyNode->getBrother());												//Reassemblying the min key heap.

	if(minKeyNode == this->root)this->root = minKeyNode->getBrother();									//If the target is self.
/*
#ifdef EXTRACTMIN_DEBUGGING

	std::string sourceStateName(baseName);

	_itoa_s(extractMinCounter, number, 10);

	sourceStateName.append(number);

	sourceStateName.append("-srcHeap");

	sourceStateName.append(".dot");

	GraphvizOutput srcHeapStateQuickShot(sourceStateName);

	srcHeapStateQuickShot.generateDirectionalGraph(this->getRoot());

#endif
*/
	unsigned long resultValue = minKeyNode->getKey();

	HeapNode* childs = minKeyNode->getChild();													//Update new roots' parent to nullptr.

	while(childs != nullptr)
	{
		childs->setParent(nullptr);

		childs = childs->getBrother();
	}

	BinomialHeap* heapPie = new BinomialHeap(minKeyNode->getChild());							//Building a new heap for using heap operation.
/*
#ifdef EXTRACTMIN_DEBUGGING

	std::string beforeStateName(baseName);

	_itoa_s(extractMinCounter, number, 10);

	beforeStateName.append(number);

	beforeStateName.append("-HeapPie-before");

	beforeStateName.append(".dot");

	GraphvizOutput beforeStateQuickShot(beforeStateName);

	beforeStateQuickShot.generateDirectionalGraph(heapPie->getRoot());

#endif
*/

	heapPie = heapPie->merge(new BinomialHeap());

#ifdef EXTRACTMIN_DEBUGGING

	std::string stateName(baseName);

	_itoa_s(extractMinCounter, number, 10);

	stateName.append(number);

	stateName.append("-HeapPie-merged");

	stateName.append(".dot");

	GraphvizOutput stateQuickShot(stateName);

	stateQuickShot.generateDirectionalGraph(heapPie->getRoot());

	std::string srcHeapStateName(baseName);

	_itoa_s(extractMinCounter, number, 10);

	srcHeapStateName.append(number);

	srcHeapStateName.append("-srcHeap-before-union");

	srcHeapStateName.append(".dot");

	GraphvizOutput srcHeapStateQuickShot(srcHeapStateName);

	srcHeapStateQuickShot.generateDirectionalGraph(this->getRoot());

#endif

	minKeyNode->clearRelationships();															//The extracted key has to detach the relations.

	delete minKeyNode;

	minKeyNode = nullptr;

	heapPie = this->unionHeap(heapPie);

#ifdef EXTRACTMIN_DEBUGGING

	std::string unionedStateName(baseName);

	_itoa_s(extractMinCounter, number, 10);

	unionedStateName.append(number);

	unionedStateName.append("-HeapPie-union");

	unionedStateName.append(".dot");

	GraphvizOutput unionedHeapPie(unionedStateName);

	unionedHeapPie.generateDirectionalGraph(heapPie->getRoot());

#endif

	root = heapPie->root;

	heapPie->detach();																			//Clean temporary variables.

	delete heapPie;

	return resultValue;
}

HeapNode* BinomialHeap::decreaseKey(HeapNode* targetNode, unsigned long newKey)
{
	if((targetNode == nullptr) || newKey > targetNode->getKey())
	{
		std::cerr << "Passing a NULL pointer or The new key is greater than current key." << std::endl;

		return nullptr;
	}

	targetNode->setKey(newKey);

	HeapNode* ptr = targetNode;

	HeapNode* ptrParent = ptr->getParent();

	unsigned long tempKey;

	while(ptrParent != nullptr && ptr->getKey() < ptrParent->getKey())										//In case of the node is a child node of other nodes.
	{
		tempKey = ptr->getKey();

		ptr->setKey(ptrParent->getKey());

		ptrParent->setKey(tempKey);

		ptr = ptrParent;

		ptrParent = ptr->getParent();
	}

	return new HeapNode(targetNode->getKey());
}

void BinomialHeap::deleteNode(HeapNode* target)
{
	this->decreaseKey(target, 0);

	this->extractMin();
}