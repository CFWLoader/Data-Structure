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

	child2->setChild(new HeapNode(33));

	root->setBrother(new HeapNode(7));

	HeapNode* branch = new HeapNode(22);

	branch->setBrother(new HeapNode(77));

	branch->getBrother()->setBrother(new HeapNode(54));

	root->getChild()->setChild(branch);

	delete root->getChild()->getChild();

	//delete root;

	//delete root->getBrother();

	//root->setBrother(nullptr);
	*/

	GraphvizOutput gOut("./testFile.dot");

	gOut.generateDirectionalGraph(root);

	delete root;

	return 0;
}