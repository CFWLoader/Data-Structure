#ifndef GRAPHVIZOUTPUT_H_
#define GRAPHVIZOUTPUT_H_

#include <string>
#include <fstream>

#include "HeapNode.h"

//The class is for debugging the heap via viewing the visual diagram.
//The class generates the tree.
class GraphvizOutput
{
public:

	explicit GraphvizOutput(const std::string&);

	~GraphvizOutput();

	void generateDirectionalGraph(HeapNode*);

	void generateNodes(HeapNode*);

	void generateEdges(HeapNode*);

	void generateDebuggingGraph(HeapNode*);

	void generateDebuggingNodes(HeapNode*);

	//void generateGraph();

private:

	std::string filename;

	std::ofstream output;
};

#endif