#include <iostream>

#include "FibonacciHeapNode.h"

#include "FibonacciHeap.h"

#include "GraphvizOutput.h"

using namespace std;

int main(int argc, char* argv[])
{
	FibonacciHeap theHeap;

	theHeap.insert(3);

	theHeap.getRoots()->setChild(new FibonacciHeapNode(22));

	theHeap.insert(4);

	theHeap.getRoots()->setChild(new FibonacciHeapNode(84));

	theHeap.insert(5);

	theHeap.insert(666);

	/*

	FibonacciHeapNode* iter = theHeap.getRoots();

	cout << "Right Loop: " << endl;

	for(int counter = 0; counter < 10; ++counter, iter = iter->getRight())
	{
		cout << iter->getKey() << "    Left:  " << iter->getLeft()->getKey() << "   Right:  " << iter->getRight()->getKey() << endl;
	}

	cout << "Left Loop: " << endl;

	for(int counter = 0; counter < 10; ++counter, iter = iter->getLeft())
	{
		cout << iter->getKey() << "    Left:  " << iter->getLeft()->getKey() << "   Right:  " << iter->getRight()->getKey() << endl;
	}

	*/
	
	GraphvizOutput gOut("./diagram/F-Heap.dot");

	gOut.generateDirectionalGraph(theHeap.getRoots());

	//cout << theHeap.getRoots()->getKey() << endl;

	return 0;
}