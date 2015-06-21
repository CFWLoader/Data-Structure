#ifndef FIBONACCIHEAPNODE
#define FIBONACCIHEAPNODE

class FibonacciHeapNode
{
public:

	explicit FibonacciHeapNode(unsigned long);

	~FibonacciHeapNode();

	inline FibonacciHeapNode* getParent() const;

	inline void setParent(FibonacciHeapNode*);

	inline FibonacciHeapNode* getChild() const;

	inline void setChild(FibonacciHeapNode*);

	inline FibonacciHeapNode* getLeft() const;

	inline void setLeft(FibonacciHeapNode*);

	inline FibonacciHeapNode* getRight() const;

	inline void setRight(FibonacciHeapNode*);

	inline unsigned long getKey() const;

	inline void setKey(unsigned long);

private:

	FibonacciHeapNode* parent;
	FibonacciHeapNode* child;
	FibonacciHeapNode* left;
	FibonacciHeapNode* right;

	unsigned long key;
};

#endif