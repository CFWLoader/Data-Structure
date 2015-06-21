#include "BinomialHeap.h"

#include <limits>
#include <vector>
#include <algorithm>

#include "GraphvizOutput.h"
#include "Auxiliary.h"

//#define DEBUGGING

bool degreeLess(HeapNode* a, HeapNode* b)
{
	return a->getDegree() < b->getDegree();
}

const unsigned long ULONG_INF = std::numeric_limits<unsigned long>::max();

BinomialHeap::BinomialHeap() : root(nullptr), minKeyNode(nullptr)
{}

BinomialHeap::BinomialHeap(HeapNode* settingRoot) : root(settingRoot), minKeyNode(nullptr)
{}

BinomialHeap::~BinomialHeap()
{
	if(root != nullptr)
	{
		delete root;

		root = nullptr;
	}
}

void BinomialHeap::detach()
{
	root = nullptr;

	minKeyNode = nullptr;
}

unsigned long BinomialHeap::minimum()
{
	unsigned long result = ULONG_INF;

	HeapNode* ptr = root;

	while(ptr != nullptr)
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

	HeapNode* ptr = newHeap->root, *prevs = nullptr, *next = nullptr;

	if(ptr == nullptr)return newHeap;

	next = ptr->getBrother();

#ifdef DEBUGGING

	std::string basename("./diagram/unioningHeap");

	int stateCounter = 1;

	char stateCounterStr[20];

#endif

	while(next != nullptr)
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

	HeapNode* ptr = this->root, *prevs;

	while(ptr != nullptr)
	{
		prevs = ptr;

		nodeContainer.push_back(ptr);

		ptr = ptr->getBrother();

		prevs->setBrother(nullptr);
	}

	ptr = bHeap->root;

	while(ptr != nullptr)
	{
		prevs = ptr;

		nodeContainer.push_back(ptr);

		ptr = ptr->getBrother();

		prevs->setBrother(nullptr);
	}

	std::sort(nodeContainer.begin(), nodeContainer.end(), degreeLess);

	std::vector<HeapNode*>::const_iterator iter = nodeContainer.begin(), end = nodeContainer.end();

	if(iter != end)
	{
		ptr = *iter;

		++iter;
	}
	else
	{
		ptr = nullptr;
	}

	mergedHeap = new BinomialHeap(ptr);

	while(iter != end)
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

	heapPie = this->unionHeap(heapPie);

	root = heapPie->root;

	heapPie->detach();
}

unsigned long BinomialHeap::extractMin()
{
	if(root == nullptr) return ULONG_INF;

	HeapNode* nodeIterator = root;

	minKeyNode = nodeIterator;

	HeapNode* prev = nullptr;

	while(nodeIterator != nullptr)																//Find the minimum key in the roots.
	{
		if(nodeIterator->getKey() < minKeyNode->getKey())
		{
			minKeyNode = nodeIterator;
		}

		nodeIterator = nodeIterator->getBrother();
	}


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
}