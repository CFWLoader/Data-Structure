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

	void insert(HeapNode*);

	unsigned long extractMin();

	HeapNode* decreaseKey(HeapNode*, unsigned long);

private:

	HeapNode* root;

	HeapNode* minKeyNode;
};

#endif
