#ifndef FIBONACCIHEAP_H_
#define FIBONACCIHEAP_H_

class FibonacciHeapNode;

class FibonacciHeap
{
public:
	FibonacciHeap();

	~FibonacciHeap();

	bool insert(unsigned long);

	bool insert(FibonacciHeapNode*);

	inline FibonacciHeapNode* getRoots() const;

private:
	bool updateRoots(FibonacciHeapNode*);

	FibonacciHeapNode* root;
};

inline FibonacciHeapNode* FibonacciHeap::getRoots() const
{
	return root;
}

#endif