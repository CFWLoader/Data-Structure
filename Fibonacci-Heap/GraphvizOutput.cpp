#include "GraphvizOutput.h"
#include <cassert>

#include <deque>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>

#include "FibonacciHeapNode.h"
// #include <cstring>

GraphvizOutput::GraphvizOutput(const std::string& realFilename) : 
								filename(realFilename),
								output(realFilename, std::ios_base::trunc)
{
	assert((output.is_open() == true));
}

GraphvizOutput::~GraphvizOutput()
{
	output.close();
}

void GraphvizOutput::generateDirectionalGraph(FibonacciHeapNode* root)
{
	output << "digraph theGraph{" << std::endl;

	this->generateNodes(root);

	this->generateEdges(root);

	output << "}" << std::endl;

	std::string targetFilename(filename.begin(), filename.end() - 3);

	targetFilename.append("jpg");

	char command[256];

	snprintf(command, 256, "dot -Tjpg -o %s %s", targetFilename.c_str(), filename.c_str());

	system(command);
}

void GraphvizOutput::generateNodes(FibonacciHeapNode* root)
{
	if(root == nullptr) return ;

	std::deque<FibonacciHeapNode*> heapNodeQueue;

	heapNodeQueue.push_back(root);

	FibonacciHeapNode* iterator, *layerHead;

	layerHead = root;

	//bool layerPushed;

	while(!heapNodeQueue.empty())
	{
		iterator = heapNodeQueue.front();

		heapNodeQueue.pop_front();

		if(iterator->getChild() != nullptr) this->generateNodes(iterator->getChild());
		if(iterator->getRight() != layerHead) heapNodeQueue.push_back(iterator->getRight());

		output << "\tnode" << iterator->getKey() << "[ label = \"K:" << iterator->getKey() << "\\nG:" << iterator->getDegree() << "\"];" << std::endl;

		if(iterator == layerHead->getChild())layerHead = iterator;
	}
}

void GraphvizOutput::generateEdges(FibonacciHeapNode* root)
{
	if(root == nullptr) return ;

	std::deque<FibonacciHeapNode*> heapNodeQueue;

	heapNodeQueue.push_back(root);

	FibonacciHeapNode* iterator, *childIterator, *layerHead, *childLayerHead;

	layerHead = root;

	while(!heapNodeQueue.empty())
	{
		iterator = heapNodeQueue.front();

		//heapNodeQueue.pop_front();

		if(iterator->getChild() != nullptr) 
		{

			this->generateEdges(iterator->getChild());

			childIterator = iterator->getChild();

			childLayerHead = childIterator;

			do
			{
				output << "\tnode" << iterator->getKey() << "->node" << childIterator->getKey() << std::endl;

				output << "\tnode" << childIterator->getKey() << "->node" << childIterator->getParent()->getKey() << std::endl;

				childIterator = childIterator->getRight();
			} while(childIterator->getRight() != childLayerHead);
		}

		if(iterator->getRight() != layerHead)
		{ 
			heapNodeQueue.push_back(iterator->getRight());

			//output << "\tnode" << iterator->getKey() << "->node" << iterator->getBrother()->getKey() << "[label = \"PT brother\"]" << std::endl;
		}
		else
		{
			layerHead = heapNodeQueue.front()->getChild();
		}

		heapNodeQueue.pop_front();

	}
}

/*
void GraphvizOutput::generateDebuggingGraph(FibonacciHeapNode* root)
{
	output << "digraph theGraph{" << std::endl;

	this->generateDebuggingNodes(root);

	this->generateEdges(root);

	output << "}" << std::endl;

	std::string targetFilename(filename.begin(), filename.end() - 3);

	targetFilename.append("jpg");

	char command[256];

	snprintf(command, 256, "dot -Tjpg -o %s %s", targetFilename.c_str(), filename.c_str());

	system(command);
}
*/

/*
void GraphvizOutput::generateDebuggingNodes(FibonacciHeapNode* root)
{
	if(root == nullptr) return ;

	std::deque<FibonacciHeapNode*> heapNodeQueue;

	heapNodeQueue.push_back(root);

	FibonacciHeapNode* iterator;

	while(!heapNodeQueue.empty())
	{
		iterator = heapNodeQueue.front();

		heapNodeQueue.pop_front();

		if(iterator->getChild() != nullptr) heapNodeQueue.push_back(iterator->getChild());
		if(iterator->getRight() != nullptr) heapNodeQueue.push_back(iterator->getBrother());

		output << "\tnode" << iterator->getKey() 
			<< "[ label = \"T:" << iterator
			<< "\\nK:" << iterator->getKey() 
			<< "\\nG:" << iterator->getDegree() 
			<< "\\nP:" << iterator->getParent()
			<< "\\nC:" << iterator->getChild()
			<< "\\nB:" << iterator->getBrother()
			<< "\"];" << std::endl;
	}
}
*/