#ifndef HEAPNODE_H_
#define HEAPNODE_H_

class HeapNode
{
public:

	explicit HeapNode(unsigned long);

	~HeapNode();

	HeapNode* getParent() const;

	void setParent(HeapNode*);

	HeapNode* getChild() const;

	void setChild(HeapNode*);

	HeapNode* getBrother() const;

	void setBrother(HeapNode*);

	unsigned long getKey() const;

	void setKey(unsigned long);

	unsigned long getDegree() const;

	void setDegree(unsigned long);

	void clearRelationships();

	void increaseDegree();

	void decreaseDegree();

private:

	HeapNode* parent,
			*child,
			*brother;

	unsigned long key;

	unsigned long degree;
};

#endif