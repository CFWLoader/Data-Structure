#include "HeapNode.h"

HeapNode::HeapNode(unsigned long keyValue) : parent(nullptr),
									child(nullptr),
									brother(nullptr),
									key(keyValue),
									degree(0)
{}


HeapNode::~HeapNode()
{
	if(parent != nullptr)
	{
		parent->setChild(nullptr);

		parent = nullptr;
	}

	if (child != nullptr)
	{
		delete child;

		child = nullptr;
	}

	if (brother != nullptr)
	{
		delete brother;

		brother = nullptr;
	}
}

/*
inline HeapNode* HeapNode::getParent() const
{
	return parent;
}

inline void HeapNode::setParent(HeapNode* newParent)
{
	parent = newParent;
	
	HeapNode* oldParent = parent;

	parent = newParent;

	HeapNode* ptr = brother;

	while(ptr != nullptr)
	{
		ptr->setParent(parent);

		ptr = ptr->getBrother();
	}
	//////////////////////////////////////////////////////////////////////////////////
}

inline HeapNode* HeapNode::getChild() const
{
	return child;
}
*/

void HeapNode::setChild(HeapNode* newChild)
{

	if(newChild == nullptr)
	{
		degree = 0;
	}
	else
	{
		degree = 0;

		HeapNode* ptr = newChild;

		while(ptr != nullptr)
		{
			this->increaseDegree();

			ptr->setParent(this);

			ptr = ptr->getBrother();
		}
		//child->setParent = this;
	}

	child = newChild;
}

/*
inline HeapNode* HeapNode::getBrother() const
{
	return brother;
}
*/

void HeapNode::setBrother(HeapNode* newBrother)
{
	if(parent != nullptr)
	{

		HeapNode* ptr = nullptr;

		ptr = brother;

		while(ptr != nullptr)
		{
			parent->decreaseDegree();

			ptr->setParent(nullptr);

			ptr = ptr->getBrother();
		}

		if(newBrother == nullptr)
		{
			ptr = brother;

			/*

			while(ptr != nullptr)
			{
				parent->decreaseDegree();

				ptr->setParent(nullptr);

				ptr = ptr->getBrother();
			}
			*/
		}
		else 
		{
			ptr = newBrother;
		
			while(ptr != nullptr)
			{
				parent->increaseDegree();

				ptr->setParent(parent);

				ptr = ptr->getBrother();
			}
		}
	}
	
	brother = newBrother;
}

/*

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
*/