#include <iostream>

#include "FibonacciHeapNode.h"

#include "FibonacciHeap.h"

#include "GraphvizOutput.h"

using namespace std;

FibonacciHeap* sample1();
FibonacciHeapNode* sample2();
FibonacciHeap* sample3();

int main(int argc, char* argv[])
{

	FibonacciHeap* theHeap = sample1();

	//FibonacciHeapNode* root = sample2();
	
	GraphvizOutput gOut("./diagram/F-Heap1.dot");

	//gOut.generateDirectionalGraph(theHeap->getRoots());

	gOut.generateDirectionalGraph(theHeap->getRoots());

	FibonacciHeap* uHeap = sample3();

	GraphvizOutput gOut1("./diagram/F-Heap2.dot");

	gOut1.generateDirectionalGraph(uHeap->getRoots());

	theHeap->unionHeap(uHeap);

	uHeap->detach();

	GraphvizOutput gOut2("./diagram/F-Heap3.dot");

	gOut2.generateDirectionalGraph(theHeap->getRoots());

	delete theHeap;

	delete uHeap;

	return 0;
}

FibonacciHeap* sample1()
{
	FibonacciHeap* theHeap = new FibonacciHeap();

	theHeap->insert(3);

	theHeap->getRoots()->setChild(new FibonacciHeapNode(22));

	theHeap->getRoots()->getChild()->setLeft(new FibonacciHeapNode(5674));

	FibonacciHeapNode* node = new FibonacciHeapNode(4);

	theHeap->insert(node);

	node = new FibonacciHeapNode(5);

	node->setChild(new FibonacciHeapNode(43));

	theHeap->insert(node);

	//node->getChild()->setRight(new FibonacciHeapNode(73362));

	node = new FibonacciHeapNode(666);

	theHeap->insert(node);

	/*

	theHeap->getRoots()->getRight()->setChild(new FibonacciHeapNode(43));

	theHeap->getRoots()->getLeft()->setChild(new FibonacciHeapNode(57));

	*/

	return theHeap;
}

FibonacciHeapNode* sample2()
{
	FibonacciHeapNode* root = new FibonacciHeapNode(3);

	root->setLeft(new FibonacciHeapNode(4));

	/*
	root = root->getLeft();

	root->setRight(new FibonacciHeapNode(5));
	*/

	return root;
}

FibonacciHeap* sample3()
{
	FibonacciHeap* theHeap = new FibonacciHeap();

	theHeap->insert(13);

	theHeap->getRoots()->setChild(new FibonacciHeapNode(122));

	theHeap->getRoots()->getChild()->setLeft(new FibonacciHeapNode(15674));

	FibonacciHeapNode* node = new FibonacciHeapNode(14);

	theHeap->insert(node);

	node = new FibonacciHeapNode(15);

	node->setChild(new FibonacciHeapNode(143));

	theHeap->insert(node);

	//node->getChild()->setRight(new FibonacciHeapNode(73362));

	node = new FibonacciHeapNode(1666);

	theHeap->insert(node);

	/*

	theHeap->getRoots()->getRight()->setChild(new FibonacciHeapNode(43));

	theHeap->getRoots()->getLeft()->setChild(new FibonacciHeapNode(57));

	*/

	return theHeap;
}