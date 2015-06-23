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

	inline unsigned long getDegree() const;

	inline void setDegree(unsigned long);

	inline void increaseDegree();

	inline void decreaseDegree();

	inline bool isMarked() const;

	inline void setMarkFlag(bool);

private:

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

inline void FibonacciHeapNode::setParent(FibonacciHeapNode* newParent)
{
	this->parent = newParent;
}

inline FibonacciHeapNode* FibonacciHeapNode::getChild() const
{
	return child;
}

inline void FibonacciHeapNode::setChild(FibonacciHeapNode* newChild)
{
	this->child = newChild;
}

inline FibonacciHeapNode* FibonacciHeapNode::getLeft() const
{
	return left;
}

inline void FibonacciHeapNode::setLeft(FibonacciHeapNode* newLeft)
{
	this->left = newLeft;
}

inline FibonacciHeapNode* FibonacciHeapNode::getRight() const
{
	return right;
}

inline void FibonacciHeapNode::setRight(FibonacciHeapNode* newRight)
{
	this->right = newRight;
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

inline void FibonacciHeapNode::setDegree(unsigned long newDegree) const
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

#endif