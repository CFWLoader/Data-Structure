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

	std::string targetFilename(filename.begin(), filename.end() - 3);

	targetFilename.append("jpg");

	char command[256];

	snprintf(command, 256, "dot -Tjpg -o %s %s", targetFilename.c_str(), filename.c_str());

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

				output << "\tnode" << childIterator->getKey() << "->node" << childIterator->getParent()->getKey() << std::endl;

				childIterator = childIterator->getBrother();
			}
		}

		if(iterator->getBrother() != nullptr)
		{ 
			heapNodeQueue.push_back(iterator->getBrother());

			//output << "\tnode" << iterator->getKey() << "->node" << iterator->getBrother()->getKey() << "[label = \"PT brother\"]" << std::endl;
		}

	}
}

void GraphvizOutput::generateDebuggingGraph(HeapNode* root)
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

void GraphvizOutput::generateDebuggingNodes(HeapNode* root)
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