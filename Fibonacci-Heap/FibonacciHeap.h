#ifndef FIBONACCIHEAP_H_
#define FIBONACCIHEAP_H_

class FibonacciHeapNode;

class FibonacciHeap
{
public:
	FibonacciHeap();

	~FibonacciHeap();

	bool insert(unsigned long);
	
private:
	FibonacciHeapNode* root;
};

#endif