#include <iostream>

#include "FibonacciHeapNode.h"

#include "FibonacciHeap.h"

#include "GraphvizOutput.h"

using namespace std;

FibonacciHeap* sample1();
FibonacciHeapNode* sample2();

int main(int argc, char* argv[])
{

	//FibonacciHeap* theHeap = sample1();

	FibonacciHeapNode* root = sample2();
	
	GraphvizOutput gOut("./diagram/F-Heap.dot");

	gOut.generateDirectionalGraph(root);

	delete root;

	return 0;
}

FibonacciHeap* sample1()
{
	FibonacciHeap* theHeap = new FibonacciHeap();

	theHeap->insert(3);

	theHeap->getRoots()->setChild(new FibonacciHeapNode(22));

	theHeap->insert(4);

	theHeap->insert(5);

	theHeap->insert(666);

	theHeap->getRoots()->getRight()->setChild(new FibonacciHeapNode(43));

	theHeap->getRoots()->getLeft()->setChild(new FibonacciHeapNode(57));

	return theHeap;
}

FibonacciHeapNode* sample2()
{
	FibonacciHeapNode* root = new FibonacciHeapNode(3);

	root->setLeft(new FibonacciHeapNode(4));

	return root;
}