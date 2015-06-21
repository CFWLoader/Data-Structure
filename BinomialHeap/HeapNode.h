#ifndef HEAPNODE_H_
#define HEAPNODE_H_

class HeapNode
{
public:

	explicit HeapNode(unsigned long);

	~HeapNode();

	inline HeapNode* getParent() const;

	inline void setParent(HeapNode*);

	inline HeapNode* getChild() const;

	void setChild(HeapNode*);

	inline HeapNode* getBrother() const;

	void setBrother(HeapNode*);

	inline unsigned long getKey() const;

	inline void setKey(unsigned long);

	inline unsigned long getDegree() const;

	inline void setDegree(unsigned long);

	inline void clearRelationships();

	inline void increaseDegree();

	inline void decreaseDegree();

	inline void link(HeapNode*);

private:

	HeapNode* parent,
			*child,
			*brother;

	unsigned long key;

	unsigned long degree;
};

inline HeapNode* HeapNode::getParent() const
{
	return parent;
}

inline void HeapNode::setParent(HeapNode* newParent)
{
	parent = newParent;
	/*
	HeapNode* oldParent = parent;

	parent = newParent;

	HeapNode* ptr = brother;

	while(ptr != nullptr)
	{
		ptr->setParent(parent);

		ptr = ptr->getBrother();
	}
	*/
}

inline HeapNode* HeapNode::getChild() const
{
	return child;
}

inline HeapNode* HeapNode::getBrother() const
{
	return brother;
}

inline unsigned long HeapNode::getKey() const
{
	return key;
}

inline void HeapNode::setKey(unsigned long newKey)
{
	key = newKey;
}

inline unsigned long HeapNode::getDegree() const
{
	return degree;
}

inline void HeapNode::setDegree(unsigned long newDegree)
{
	degree = newDegree;
}

inline void HeapNode::clearRelationships()
{
	if(parent != nullptr)parent->decreaseDegree();
	
	parent = nullptr;

	child = nullptr;

	brother = nullptr;

	degree = 0;
}

inline void HeapNode::increaseDegree()
{
	++degree;
}

inline void HeapNode::decreaseDegree()
{
	--degree;
}

inline void HeapNode::link(HeapNode* newParent)
{
	this->setBrother(newParent->getChild());

	newParent->setChild(this);
}

#endif