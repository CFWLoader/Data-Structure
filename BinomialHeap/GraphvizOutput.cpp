#include "GraphvizOutput.h"
#include <cassert>

#include <deque>

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

void GraphvizOutput::generateDirectionalGraphviz(const HeapNode* root)
{
	output << "digraph theGraph{" << std::endl;

	this->generateNodes(root);

	output << "}" << std::endl;
}

void GraphvizOutput::generateNodes(const HeapNode* root)
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

		output << "\tnode" << iterator->getKey() << "[ label = \"K:" << iterator->getKey() << "\nG:" << iterator->getDegree() << "\"];" << std::endl;
	}
}