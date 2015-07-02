#ifndef FIBONACCIHEAPNODE
#define FIBONACCIHEAPNODE

extern unsigned long UL_INFINITY;

class FibonacciHeapNode
{
public:

	explicit FibonacciHeapNode(unsigned long);

	~FibonacciHeapNode();

	inline FibonacciHeapNode* getParent() const;

	void setParent(FibonacciHeapNode*);

	inline FibonacciHeapNode* getChild() const;

	void setChild(FibonacciHeapNode*);

	inline FibonacciHeapNode* getLeft() const;

	void setLeft(FibonacciHeapNode*);

	void concatenateLeft(FibonacciHeapNode*);

	inline FibonacciHeapNode* getRight() const;

	void setRight(FibonacciHeapNode*);

	void concatenateRight(FibonacciHeapNode*);

	inline unsigned long getKey() const;

	inline void setKey(unsigned long);

	inline unsigned long getDegree() const;

	inline void setDegree(unsigned long);

	inline void increaseDegree();

	inline void decreaseDegree();

	inline bool isMarked() const;

	inline void setMarkFlag(bool);

	void isolate();

	void detach();

private:

	inline void releaseRight();										//For destructor.

	FibonacciHeapNode* parent;
	FibonacciHeapNode* child;
	FibonacciHeapNode* left;
	FibonacciHeapNode* right;

	unsigned long key;

	unsigned long degree;

	bool markFlag;
};

inline FibonacciHeapNode* FibonacciHeapNode::getParent() const
{
	return parent;
}

inline FibonacciHeapNode* FibonacciHeapNode::getChild() const
{
	return child;
}

inline FibonacciHeapNode* FibonacciHeapNode::getLeft() const
{
	return left;
}

inline FibonacciHeapNode* FibonacciHeapNode::getRight() const
{
	return right;
}

inline unsigned long FibonacciHeapNode::getKey() const
{
	return key;
}

inline void FibonacciHeapNode::setKey(unsigned long newKey)
{
	this->key = newKey;
}

inline unsigned long FibonacciHeapNode::getDegree() const
{
	return degree;
}

inline void FibonacciHeapNode::setDegree(unsigned long newDegree)
{
	this->degree = newDegree;
}

inline void FibonacciHeapNode::increaseDegree()
{
	++degree;
}

inline void FibonacciHeapNode::decreaseDegree()
{
	--degree;
}

inline bool FibonacciHeapNode::isMarked() const
{
	return markFlag;
}

inline void FibonacciHeapNode::setMarkFlag(bool theFlag)
{
	this->markFlag = theFlag;
}

inline void FibonacciHeapNode::releaseRight()
{
	this->right = nullptr;
}

#endif