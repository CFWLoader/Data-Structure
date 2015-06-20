#ifndef BINOMIALHEAP_H_
#define BINOMIALHEAP_H_

#include "HeapNode.h"

class BinomialHeap
{
public:

	BinomialHeap();

	BinomialHeap(HeapNode*);

	~BinomialHeap();

	void detach();

	unsigned long minimum();

	BinomialHeap* unionHeap(BinomialHeap*);

	BinomialHeap* merge(BinomialHeap*);

	HeapNode* getRoot() const;

private:

	HeapNode* root;

	HeapNode* minKeyNode;
};

#endif
