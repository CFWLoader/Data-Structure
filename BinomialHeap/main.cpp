#include <iostream>

#include "BinomialHeap.h"

#include "GraphvizOutput.h"

using namespace std;

HeapNode* sample1();

HeapNode* sample2();

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
	//BinomialHeap bHeap;

	/*

	GraphvizOutput gOut("./testFile.dot");

	gOut.generateDirectionalGraph(root);

	delete root;
	*/
	BinomialHeap heap1(sample1());

	BinomialHeap heap2(sample2());

	BinomialHeap* newHeap = heap1.unionHeap(&heap2);

	heap1.detach();

	heap2.detach();

	GraphvizOutput finalHeap("./diagram/FinalHeap.dot");

	finalHeap.generateDirectionalGraph(newHeap->getRoot());

	/*

	newHeap->insert(new HeapNode(1));

	GraphvizOutput finalHeapInserted1("./diagram/FinalHeap-inserted1.dot");

	finalHeapInserted1.generateDirectionalGraph(newHeap->getRoot());

	newHeap->insert(new HeapNode(3));

	GraphvizOutput finalHeapInserted2("./diagram/FinalHeap-inserted2.dot");

	finalHeapInserted2.generateDirectionalGraph(newHeap->getRoot());
	*/

	delete newHeap;

	return 0;
}

HeapNode* sample1()
{
	HeapNode* r1 = new HeapNode(12), *currentRoot;

	r1->setBrother(new HeapNode(7));

	r1->getBrother()->setChild(new HeapNode(25));

	r1->getBrother()->setBrother(new HeapNode(15));

	currentRoot = r1->getBrother()->getBrother();

	currentRoot->setChild(new HeapNode(28));

	currentRoot->getChild()->setBrother(new HeapNode(33));

	currentRoot->getChild()->setChild(new HeapNode(41));

	GraphvizOutput heap1("./diagram/Heap1.dot");

	heap1.generateDirectionalGraph(r1);

	//delete r1;

	return r1;
}

HeapNode* sample2()
{
	HeapNode* r2 = new HeapNode(18), *currentRoot;

	r2->setBrother(new HeapNode(3));

	r2->getBrother()->setBrother(new HeapNode(6));

	r2->getBrother()->setChild(new HeapNode(37));

	currentRoot = r2->getBrother()->getBrother();

	currentRoot->setChild(new HeapNode(8));

	currentRoot = currentRoot->getChild();

	currentRoot->setBrother(new HeapNode(29));

	currentRoot->getBrother()->setBrother(new HeapNode(10));

	currentRoot->getBrother()->getBrother()->setBrother(new HeapNode(44));

	currentRoot->getBrother()->getBrother()->setChild(new HeapNode(17));

	currentRoot->getBrother()->setChild(new HeapNode(48));

	currentRoot->getBrother()->getChild()->setChild(new HeapNode(50));

	currentRoot->getBrother()->getChild()->setBrother(new HeapNode(31));

	currentRoot->setChild(new HeapNode(30));

	currentRoot = currentRoot->getChild();

	currentRoot->setBrother(new HeapNode(23));

	currentRoot->getBrother()->setBrother(new HeapNode(22));

	currentRoot->getBrother()->setChild(new HeapNode(24));

	currentRoot->setChild(new HeapNode(45));

	currentRoot = currentRoot->getChild();

	currentRoot->setBrother(new HeapNode(32));

	currentRoot->setChild(new HeapNode(55));

	GraphvizOutput heap2("./diagram/Heap2.dot");

	heap2.generateDirectionalGraph(r2);

	//delete r2;

	return r2;
}