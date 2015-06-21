#ifndef FIBONACCIHEAP_H_
#define FIBONACCIHEAP_H_

#include "FibonacciHeapNode.h"

class FibonacciHeap
{
public:
	FibonacciHeap();

	~FibonacciHeap();
private:
	FibonacciHeapNode* root;
};

#endif