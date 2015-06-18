#include "HeapNode.h"

HeapNode::HeapNode(unsigned long keyValue) : parent(nullptr),
									child(nullptr),
									brother(nullptr),
									key(keyValue),
									degree(0)
{}


HeapNode::~HeapNode()
{
	parent = nullptr;

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

HeapNode* HeapNode::getParent() const
{
	return parent;
}

void HeapNode::setParent(HeapNode* newParent)
{
	parent = newParent;
}

HeapNode* HeapNode::getChild() const
{
	return child;
}

void HeapNode::setChild(HeapNode* newChild)
{

	if(newChild == nullptr)
	{
		degree = 0;
	}
	else
	{ 
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

HeapNode* HeapNode::getBrother() const
{
	return brother;
}

void HeapNode::setBrother(HeapNode* newBrother)
{
	if(parent != nullptr)
	{
		HeapNode* ptr = nullptr;

		if(newBrother == nullptr)
		{
			ptr = brother;

			while(ptr != nullptr)
			{
				parent->decreaseDegree();

				ptr = ptr->getBrother();
			}
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

	if(brother != nullptr)
	{
		
	}
	
	brother = newBrother;
}

unsigned long HeapNode::getKey() const
{
	return key;
}

void HeapNode::setKey(unsigned long newKey)
{
	key = newKey;
}

unsigned long HeapNode::getDegree() const
{
	return degree;
}

void HeapNode::setDegree(unsigned long newDegree)
{
	degree = newDegree;
}

void HeapNode::clearRelationships()
{
	parent = nullptr;

	child = nullptr;

	brother = nullptr;

	degree = 0;
}

void HeapNode::increaseDegree()
{
	++degree;
}

void HeapNode::decreaseDegree()
{
	--degree;
}