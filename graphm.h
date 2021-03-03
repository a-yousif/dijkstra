// ----------------------------- graphm.h ----------------------------------
// Ahmad Yousif - CSS 343A
// Created:       10/28/2020
// Last Modified: 11/10/2020
// ----------------------------------------------------------------------------
// Header file for the GraphM class. This class represents a graph with
// edges between every node. It can use Dijkstra's algorithm to find the shortest
// path between each node to every other node, as well as print the path to the
// console.
// ----------------------------------------------------------------------------
// Assumptions: 
// - Program assumes all input is valid.
// ----------------------------------------------------------------------------

#include "nodedata.h"

class GraphM
{
public:
	// Each table has at most 100 nodes with one based nodes. The zero element
	// will be left empty.
	const static int MAXNODES = 101;
	
	// Default constructor for GraphM class
	GraphM();

	// Builds the graph based on loaded input data
	void buildGraph(ifstream& ins);

	// Inserts an edge into the graph between two given nodes
	bool insertEdge(int start, int end, int dist);

	// Remove an edge between two given nodes
	bool removeEdge(int start, int end);

	// Uses Dijkstra's Algorithm to find the shortest path from every node to every
	// other node.
	void findShortestPath();

	// Prints all required data fields to the console.
	void displayAll();

	// Displays path from start node to end node
	void display(int start, int end);

private:
	struct TableType
	{
		bool visited;                       // whether node has been visited
		int dist;                           // shortest distance from source known so far
		int path;                           // previous node in path of min dist
	};

	NodeData data[MAXNODES];				// data for graph nodes
	int C[MAXNODES][MAXNODES];				// Cost array; the adjacency matrix
	int size;								// number of nodes in the graph
	TableType T[MAXNODES][MAXNODES];		// stores visted, distance, path

	// Helper function for findShortestPath; necessary to execute Dijkstra's Algorithm.
	int findMinNotVisted(int row);

	// Helper function to display function. Displays the information of each node
	// in the segment.
	void displaySegment(int start, int end);

	// Helper function to display function. Displays the information of each node
	// in the segment.
	void printPath(int start, int end, bool isDisplayName);

	// Helper function to check whether edge input is valid
	bool isValidInput(int start, int end);

	// Helper function to check whether edge input is valid
	bool isValidInput(int start, int end, int dist);
};