#include "FibonacciHeapNode.h"

FibonacciHeapNode::FibonacciHeapNode(unsigned long theKey) :
	parent(nullptr), child(nullptr), left(nullptr), right(nullptr), key(theKey)
{}

FibonacciHeapNode::~FibonacciHeapNode()
{
	
}