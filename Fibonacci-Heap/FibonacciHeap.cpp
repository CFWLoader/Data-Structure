#include "FibonacciHeapNode.h"

#include "FibonacciHeap.h"

FibonacciHeap::FibonacciHeap()
{
	root = nullptr;
}

FibonacciHeap::~FibonacciHeap()
{
	delete root;
}

bool FibonacciHeap::insert(unsigned long newKey)
{
	
}