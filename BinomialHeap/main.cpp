#include <iostream>

#include "HeapNode.h"

#include "GraphvizOutput.h"

using namespace std;

int main(int argc, char* argv[])
{
	/*
	HeapNode* root = new HeapNode(3);

	HeapNode* child = new HeapNode(4);

	HeapNode* child2 = new HeapNode(5);

	//root->setChild(child);

	//child->setParent(root);

	child->setBrother(child2);

	root->setChild(child);

	child->setParent(root);

	cout << root->getDegree() << endl;

	cout << child2->getParent()->getKey() << endl;

	delete root;
	*/
	GraphvizOutput("./testFile.dot");

	return 0;
}