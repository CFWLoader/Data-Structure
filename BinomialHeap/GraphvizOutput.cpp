#include "GraphvizOutput.h"
#include <cassert>

#include <deque>

#include <stdlib.h>
#include <stdio.h>
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

void GraphvizOutput::generateDirectionalGraph(HeapNode* root)
{
	output << "digraph theGraph{" << std::endl;

	this->generateNodes(root);

	this->generateEdges(root);

	output << "}" << std::endl;

	char command[256];

	snprintf(command, 256, "dot -Tjpg -o theHeap.jpg %s", filename.c_str());

	system(command);
}

void GraphvizOutput::generateNodes(HeapNode* root)
{
	if(root == nullptr) return ;

	std::deque<HeapNode*> heapNodeQueue;

	heapNodeQueue.push_back(root);

	HeapNode* iterator;

	while(!heapNodeQueue.empty())
	{
		iterator = heapNodeQueue.front();

		heapNodeQueue.pop_front();

		if(iterator->getChild() != nullptr) heapNodeQueue.push_back(iterator->getChild());
		if(iterator->getBrother() != nullptr) heapNodeQueue.push_back(iterator->getBrother());

		output << "\tnode" << iterator->getKey() << "[ label = \"K:" << iterator->getKey() << "\\nG:" << iterator->getDegree() << "\"];" << std::endl;
	}
}

void GraphvizOutput::generateEdges(HeapNode* root)
{
	if(root == nullptr) return ;

	std::deque<HeapNode*> heapNodeQueue;

	heapNodeQueue.push_back(root);

	HeapNode* iterator, *childIterator;

	while(!heapNodeQueue.empty())
	{
		iterator = heapNodeQueue.front();

		heapNodeQueue.pop_front();

		if(iterator->getChild() != nullptr) 
		{

			heapNodeQueue.push_back(iterator->getChild());

			childIterator = iterator->getChild();

			while(childIterator != nullptr)
			{
				output << "\tnode" << iterator->getKey() << "->node" << childIterator->getKey() << std::endl;

				childIterator = childIterator->getBrother();
			}
		}

		if(iterator->getBrother() != nullptr) heapNodeQueue.push_back(iterator->getBrother());	

	}
}