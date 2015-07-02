#ifndef FIBONACCIHEAP_H_
#define FIBONACCIHEAP_H_

#include <cstdio>

class FibonacciHeapNode;

class FibonacciHeap
{
public:
	FibonacciHeap();

	~FibonacciHeap();

	bool insert(unsigned long);

	bool insert(FibonacciHeapNode*);

	bool unionHeap(FibonacciHeap*);

	unsigned long extractMin();

	bool consolidate();

	bool link(FibonacciHeapNode*, FibonacciHeapNode*);

	size_t getMaxDegreeOfSingleNodeInTheHeap() const;

	unsigned long phi();

	inline unsigned long getNumberOfNodes();

	inline void increaseNumber();

	inline FibonacciHeapNode* getRoots() const;

	inline void detach();

private:
	bool updateRoots(FibonacciHeapNode*);

	FibonacciHeapNode* root;

	unsigned long numberOfNodes;
};

inline FibonacciHeapNode* FibonacciHeap::getRoots() const
{
	return root;
}

inline void FibonacciHeap::detach()
{
	root = nullptr;
}

inline unsigned long FibonacciHeap::getNumberOfNodes()
{
	return numberOfNodes;
}

inline void FibonacciHeap::increaseNumber()
{
	++numberOfNodes;
}


#endif