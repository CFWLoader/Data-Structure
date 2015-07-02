#ifndef GRAPHVIZOUTPUT_H_
#define GRAPHVIZOUTPUT_H_

#include <fstream>
#include <string>

class FibonacciHeapNode;

//The class is for debugging the heap via viewing the visual diagram.
//The class generates the tree.
class GraphvizOutput
{
public:

	explicit GraphvizOutput(const std::string&);

	~GraphvizOutput();

	void generateDirectionalGraph(FibonacciHeapNode*);

	void generateNodes(FibonacciHeapNode*);

	void generateEdges(FibonacciHeapNode*);

	void generateDebuggingGraph(FibonacciHeapNode*);

	void generateDebuggingNodes(FibonacciHeapNode*);

	void resetFile(const std::string&);

	//void generateGraph();

private:

	std::string filename;

	std::ofstream output;
};

#endif