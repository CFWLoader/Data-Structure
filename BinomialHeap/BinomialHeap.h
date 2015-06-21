#ifndef BINOMIALHEAP_H_
#define BINOMIALHEAP_H_

#include "HeapNode.h"

extern const unsigned long ULONG_INF;

class BinomialHeap
{
public:

	BinomialHeap();

	BinomialHeap(HeapNode*);

	~BinomialHeap();

	void detach();

	unsigned long minimum();

	BinomialHeap* unionHeap(BinomialHeap*);							//Union two heap.

	BinomialHeap* merge(BinomialHeap*);								//Merging two heap via sorting their roots' degree.
																	//Notice that self root need updating after merging.
																	//The function is needed by union operation.

	HeapNode* getRoot() const;

	void insert(HeapNode*);

	unsigned long extractMin();

	HeapNode* decreaseKey(HeapNode*, unsigned long);				//Decrease specified node's key.The new key must less than current.

	void deleteNode(HeapNode*);										//Delete specified node.

private:

	HeapNode* root;

	HeapNode* minKeyNode;
};

#endif
