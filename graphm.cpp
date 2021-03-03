// ----------------------------- graphm.cpp ----------------------------------
// Ahmad Yousif - CSS 343A
// Created:       10/28/2020
// Last Modified: 11/10/2020
// ----------------------------------------------------------------------------
// Implementation file for the GraphM class. This class represents a graph with
// edges between every node. It can use Dijkstra's algorithm to find the shortest
// path between each node to every other node, as well as print the path to the
// console.
// ----------------------------------------------------------------------------
// Assumptions: 
// - Program assumes all input is valid.
// ----------------------------------------------------------------------------

#include "graphm.h"
#include <iomanip>
#include <climits>

// Default constructor for GraphM class
GraphM::GraphM() 
{
	for (int row = 0; row < MAXNODES; row++)
	{
		for (int col = 0; col < MAXNODES; col++) 
		{
			C[row][col] = INT_MAX;
			T[row][col].dist = INT_MAX;
			T[row][col].visited = false;
			T[row][col].path = 0;
		}
	}

	size = 0;
}

// Builds the graph based on loaded input data
void GraphM::buildGraph(ifstream& ins)
{
	// First line of the file is the node size
	ins >> size;

	for (int i = 0; i <= size; i++) 
	{
		if (!data[i].setData(ins))
		{
			return;		// set we reached eof
		}
	}

	// row is the from node, col is the to node in the cost table array
	int row, col, cost;
	while (!ins.eof())
	{
		ins >> row >> col >> cost;

		if (row == 0 && col == 0 && cost == 0)
		{
			break;
		}

		C[row][col] = cost;
	}
}

// Inserts an edge into the graph between two given nodes
bool GraphM::insertEdge(int start, int end, int dist)
{
	bool result = false;
	if (isValidInput(start, end, dist))
	{
		C[start][end] = dist;
		findShortestPath();
		result = true;
	}
	return result;
}

// Remove an edge between two given nodes
bool GraphM::removeEdge(int start, int end)
{
	bool result = false;
	if (isValidInput(start, end))
	{
		C[start][end] = INT_MAX;
		T[start][end].visited = false;
		T[start][end].path = 0;
		T[start][end].dist = INT_MAX;

		findShortestPath();
		result = true;
	}

	return result;
}

// Helper function to check whether edge input is valid
bool GraphM::isValidInput(int start, int end)
{
	return !(start > size || end > size || start <= 0 || end <= 0);
}

// Helper function to check whether edge input is valid
bool GraphM::isValidInput(int start, int end, int dist)
{
	return isValidInput(start, end) && !(dist < 0 || (start == end && dist != 0));
}

// Uses Dijkstra's Algorithm to find the shortest path from every node to every
// other node.
void GraphM::findShortestPath()
{
	for (int source = 1; source <= size; source++)
	{
		int nextNode = source;
		T[source][nextNode].dist = 0;
		while (nextNode <= size)
		{
			T[source][nextNode].visited = true;
			// Find connecting nodes and set the cost;
			for (int i = 1; i <= size; i++)
			{
				int updatedDist = T[source][nextNode].dist + C[nextNode][i];
				if (C[nextNode][i] != INT_MAX && !T[source][i].visited
					&& updatedDist < T[source][i].dist)
				{
					T[source][i].dist = updatedDist;
					T[source][i].path = nextNode;
				}
			}

			if (nextNode == size)
			{
				break;
			}

			nextNode = findMinNotVisted(nextNode);
		}
	}
}

// Helper function for findShortestPath; necessary to execute Dijkstra's Algorithm.
int GraphM::findMinNotVisted(int row) 
{
	int minCostNode = C[row][0];
	int minNode = size + 1;
	for (int i = 1; i <= size; i++)
	{
		if (!T[row][i].visited && C[row][i] < minCostNode)
		{
			minCostNode = C[row][i];
			minNode = i;
		}
	}

	return minNode;
}

// Prints all required data fields to the console.
void GraphM::displayAll()
{
	cout << "Description" << setw(25) 
		 << "From node"	  << setw(10) 
		 << "To node"	  << setw(15) 
		 << "Dijkstra's"  << setw(10) 
		 << "Path" << endl;

	for (int start = 1; start <= size; start++)
	{
		cout << data[start] << endl;
		for (int end = 1; end <= size; end++)
		{
			cout << setw(33);
			if (start != end)
			{
				displaySegment(start, end);
			}
		}
		cout << endl;
	}
}

// Displays path from start node to end node
void GraphM::display(int start, int end)
{
	cout << setw(8);
	displaySegment(start, end);
	if (T[start][end].dist != INT_MAX)
	{
		printPath(start, end, true);
		cout << data[end] << endl << endl;
	}
}

// Helper function to display function. Displays the information of each node
// in the segment.
void GraphM::displaySegment(int start, int end)
{
	cout << start << setw(10) << end << setw(15);
	if (T[start][end].dist != INT_MAX)
	{
		cout << T[start][end].dist << setw(10);
		printPath(start, end, false);
		cout << end;
	}
	else
	{
		cout << "---";
	}

	cout << endl;
}

// Helper function to display function. Displays the information of each node
// in the segment.
void GraphM::printPath(int start, int end, bool isDisplayName)
{
	if (start == end)
	{
		return;
	}

	printPath(start, T[start][end].path, isDisplayName);
	if (isDisplayName)
	{
		cout << data[T[start][end].path] << endl << endl;
	}
	else
	{
		cout << T[start][end].path << " ";
	}
}