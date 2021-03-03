// ----------------------------- graphl.cpp ----------------------------------
// Ahmad Yousif - CSS 343A
// Created:       10/28/2020
// Last Modified: 11/10/2020
// ----------------------------------------------------------------------------
// Implementation file for the GraphL class. This class represents a graph with
// edges between every node. It is able to compute the order of a depth-first search,
// as well as print the path to the console. It is also able to display the edge
// between nodes.
// ----------------------------------------------------------------------------
// Assumptions:
// - Program assumes all input is valid.
// ----------------------------------------------------------------------------

#include "graphl.h"
#include <iomanip>
#include <climits>

// Default constructor for GraphL class
GraphL::GraphL()
{
	for (int row = 0; row < MAXNODES; row++)
	{
	    node_data[row].data = nullptr;
	    node_data[row].visited = false;
	    node_data[row].edgeHead = nullptr;
	}

	size = 0;
}

// Destructor for GraphL class
GraphL::~GraphL()
{
	for (int row = 0; row <= size; row++)
	{
		delete node_data[row].data;
		node_data[row].data = nullptr;
		node_data[row].visited = false;
		
		while (node_data[row].edgeHead != nullptr)
		{
			EdgeNode* next = node_data[row].edgeHead->nextEdge;
			delete node_data[row].edgeHead;
			node_data[row].edgeHead = nullptr;
			node_data[row].edgeHead = next;
		}
	}
}

// Builds the graph based on loaded input data
void GraphL::buildGraph(ifstream& ins)
{
	// First line of the file is the node size
	ins >> size;

	for (int i = 0; i <= size; i++)
	{
		NodeData* data = new NodeData();
		if (data->setData(ins))
		{
			node_data[i].data = data;
		}
		else
		{
			delete data;
			return; // set we reached eof
		}
	}

	// row is the from node, col is the to node in the graph
	int row, col;
	while (!ins.eof())
	{
		ins >> row >> col;

		if (row == 0 && col == 0)
		{
			return;
		}

		if (node_data[row].edgeHead != nullptr)
		{
			EdgeNode* node = new EdgeNode();
			node->adjGraphNode = col;
			node->nextEdge = node_data[row].edgeHead;
			node_data[row].edgeHead = node;
		}
		else 
		{
			EdgeNode* node = new EdgeNode();
			node->adjGraphNode = col;           
			node_data[row].edgeHead = node;
		}
	}
}

// Prints the graph with correct formatting to the console
void GraphL::displayGraph()
{
	cout << endl << "Graph:" << endl;

	for (int row = 1; row <= size; row++)
	{
		cout << "Node " << setw(25) << left << row << *node_data[row].data
			<< endl << endl;
		displayEdge(node_data[row].edgeHead, row);
	}
}

// Prints the current edge to the console
void GraphL::displayEdge(EdgeNode* edge, int row)
{
	if (edge == nullptr)
	{
		return;
	}

	cout << setw(10) << right << "edge" << " " << row << " " << edge->adjGraphNode << endl;
	displayEdge(edge->nextEdge, row);
}

// Prints the order of the depth-first search to the console
void GraphL::depthFirstSearch()
{
	cout << endl << "Depth-first ordering: ";

	for (int row = 1; row <= size; row++)
	{
		if (!node_data[row].visited)
		{
			depthFirstSearch(row);
		}
	}

	cout << endl;
}

// Helper function to print the order of the depth-first search to the console
void GraphL::depthFirstSearch(int row)
{
	cout << row << " ";
	node_data[row].visited = true;

	depthFirstSearch(node_data[row].edgeHead, row);
}

// Helper function to print the order of the depth-first search to the console
void GraphL::depthFirstSearch(EdgeNode* edge, int row)
{
	if (edge == nullptr)
	{
		return;
	}

	if (!node_data[edge->adjGraphNode].visited)
	{
		depthFirstSearch(edge->adjGraphNode);
	}

	depthFirstSearch(edge->nextEdge, row);
}