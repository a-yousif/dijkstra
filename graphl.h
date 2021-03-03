// ----------------------------- graphl.h ----------------------------------
// Ahmad Yousif - CSS 343A
// Created:       10/28/2020
// Last Modified: 11/10/2020
// ----------------------------------------------------------------------------
// Header file for the GraphL class.
// ----------------------------------------------------------------------------
// Assumptions: 
// - Program assumes all input is valid.
// ----------------------------------------------------------------------------

#include "nodedata.h"

class GraphL
{
public:
	// Each table has at most 100 nodes with one based nodes. The zero element
	// will be left empty.
	const static int MAXNODES = 101;

	// Default constructor for GraphL class
	GraphL();

	// Destructor for GraphL class
	~GraphL();

	// Builds the graph based on loaded input data
	void buildGraph(ifstream& ins);

	// Prints the graph with correct formatting to the console
	void displayGraph();

	// Prints the order of the depth-first search to the console
	void depthFirstSearch();

private:
	int size;					// number of nodes in the graph

	struct EdgeNode;			// forward reference for the compiler
	struct GraphNode {			// structs used for simplicity, use classes if desired
		EdgeNode* edgeHead;		// head of the list of edges
		NodeData* data;			// data information about each node
		bool visited;
	};

	struct EdgeNode {
		int adjGraphNode;		// subscript of the adjacent graph node
		EdgeNode* nextEdge;
	};

	GraphNode node_data[MAXNODES];

	// Prints the current edge to the console
	void displayEdge(EdgeNode* edge, int row);

	// Helper function to print the order of the depth-first search to the console
	void depthFirstSearch(int row);

	// Helper function to print the order of the depth-first search to the console
	void depthFirstSearch(EdgeNode* edge, int row);
};