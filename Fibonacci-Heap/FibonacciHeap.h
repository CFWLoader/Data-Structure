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

	size_t getMaxDegreeOfSingleNodeInTheHeap() const;

	unsigned long phi();

	inline FibonacciHeapNode* getRoots() const;

	inline void detach();

private:
	bool updateRoots(FibonacciHeapNode*);

	FibonacciHeapNode* root;
};

inline FibonacciHeapNode* FibonacciHeap::getRoots() const
{
	return root;
}

inline void FibonacciHeap::detach()
{
	root = nullptr;
}

#endif