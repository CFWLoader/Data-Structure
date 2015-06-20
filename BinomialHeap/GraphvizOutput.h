#ifndef GRAPHVIZOUTPUT_H_
#define GRAPHVIZOUTPUT_H_

#include <string>
#include <fstream>

#include "HeapNode.h"

class GraphvizOutput
{
public:

	explicit GraphvizOutput(const std::string&);

	~GraphvizOutput();

	void generateDirectionalGraph(HeapNode*);

	void generateNodes(HeapNode*);

	void generateEdges(HeapNode*);

	//void generateGraph();

private:

	std::string filename;

	std::ofstream output;
};

#endif