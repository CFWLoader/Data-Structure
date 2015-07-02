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

	//std::cout << "Command generating, filename: " << targetFilename << std::endl;

	char command[256];

	snprintf(command, 256, "dot -Tjpg -o %s %s", targetFilename.c_str(), filename.c_str());

	system(command);
}

void GraphvizOutput::generateNodes(FibonacciHeapNode* root)
{
	if(root == nullptr) return ;

	std::deque<FibonacciHeapNode*> heapNodeQueue;

	std::deque<FibonacciHeapNode*> childContainer;

	heapNodeQueue.push_back(root);

	FibonacciHeapNode* iterator, *layerHead;

	layerHead = root;

	//bool layerPushed;

	while(!heapNodeQueue.empty())
	{
		iterator = heapNodeQueue.front();

		heapNodeQueue.pop_front();

		if(iterator->getChild() != nullptr) 
		{
			childContainer.push_back(iterator->getChild());

			//output << "\t\t//Adding child key:  " << iterator->getChild()->getKey() << std::endl;
		}

		if(iterator->getRight() != layerHead)
		{
			heapNodeQueue.push_back(iterator->getRight());
		}
		else if(heapNodeQueue.empty())
		{
			heapNodeQueue.assign(childContainer.begin(), childContainer.end());

			//output << "\t\t//Next Iteration Container Size:  " << heapNodeQueue.size() << std::endl;

			childContainer.clear();

			layerHead = heapNodeQueue.front();
		}
		else
		{
			layerHead = heapNodeQueue.front();
		}

		output << "\tnode" << iterator->getKey() << "[ label = \"K:" << iterator->getKey() << "\\nG:" << iterator->getDegree() << "\\nM:" << iterator->isMarked() << "\"];" << std::endl;
	}
}

void GraphvizOutput::generateEdges(FibonacciHeapNode* root)
{
	if(root == nullptr) return ;

	std::deque<FibonacciHeapNode*> heapNodeQueue;

	std::deque<FibonacciHeapNode*> childContainer;

	heapNodeQueue.push_back(root);

	FibonacciHeapNode* iterator, *childIterator, *layerHead, *childLayerHead;

	layerHead = root;

	while(!heapNodeQueue.empty())
	{
		iterator = heapNodeQueue.front();

		heapNodeQueue.pop_front();

		if(iterator->getChild() != nullptr) 
		{
			childIterator = iterator->getChild();

			childLayerHead = childIterator;

			do
			{
				childContainer.push_back(childIterator);

				output << "\tnode" << iterator->getKey() << "->node" << childIterator->getKey() << std::endl;

				output << "\tnode" << childIterator->getKey() << "->node" << childIterator->getParent()->getKey() << std::endl;

				//output << "\t\t//Next Child key:  " << childIterator->getRight()->getKey() << std::endl;

				childIterator = childIterator->getRight();
			} while(childIterator != childLayerHead);

		}

		if(iterator->getRight() != layerHead)
		{
			heapNodeQueue.push_back(iterator->getRight());
		}
		else if(heapNodeQueue.empty())
		{
			heapNodeQueue.assign(childContainer.begin(), childContainer.end());

			//output << "\t\t//Next Iteration Container Size:  " << heapNodeQueue.size() << std::endl;

			childContainer.clear();

			layerHead = heapNodeQueue.front();
		}
		else
		{
			layerHead = heapNodeQueue.front();
		}

	}
}


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



void GraphvizOutput::generateDebuggingNodes(FibonacciHeapNode* root)
{
	if(root == nullptr) return ;

	std::deque<FibonacciHeapNode*> heapNodeQueue;

	std::deque<FibonacciHeapNode*> childContainer;

	heapNodeQueue.push_back(root);

	FibonacciHeapNode* iterator, *layerHead;

	layerHead = root;

	//bool layerPushed;

	while(!heapNodeQueue.empty())
	{
		iterator = heapNodeQueue.front();

		heapNodeQueue.pop_front();

		if(iterator->getChild() != nullptr) 
		{
			childContainer.push_back(iterator->getChild());

			//output << "\t\t//Adding child key:  " << iterator->getChild()->getKey() << std::endl;
		}

		if(iterator->getRight() != layerHead)
		{
			heapNodeQueue.push_back(iterator->getRight());
		}
		else if(heapNodeQueue.empty())
		{
			heapNodeQueue.assign(childContainer.begin(), childContainer.end());

			//output << "\t\t//Next Iteration Container Size:  " << heapNodeQueue.size() << std::endl;

			childContainer.clear();

			layerHead = heapNodeQueue.front();
		}
		else
		{
			layerHead = heapNodeQueue.front();
		}

		output << "\tnode" << iterator->getKey() 
				<< "[ label = \"K:" << iterator->getKey() 
				<< "  G:" << iterator->getDegree()
				<< "\\nM:" << iterator->isMarked()
				<< "\\n--------------"
				<< "\\nP:";

		if(iterator->getParent() == nullptr)
		{
			output << "NULL";
		}
		else
		{
			output << iterator->getParent()->getKey();
		}

		output << "\\nL:" << iterator->getLeft()->getKey()
				<< "  R:" << iterator->getRight()->getKey()
				<< "\\nC:";

		if(iterator->getChild() == nullptr)
		{
			output << "NULL";
		}
		else
		{
			output << iterator->getChild()->getKey();
		}
		
		output << "\"];" << std::endl;
	}
}


void GraphvizOutput::resetFile(const std::string& newFilename)
{
	filename = newFilename;

	output.close();

	output.open(newFilename, std::ios_base::trunc);

	assert((output.is_open() == true));
}