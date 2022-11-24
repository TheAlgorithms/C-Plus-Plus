/**
 * @file
 * @brief The implementation of [Hamilton's
 * cycle](https://en.wikipedia.org/wiki/Hamiltonian_path) backtracking solution for
 * vertices number less than 5.
 * @details
 * A code for the same problem was already present in this repo using dp, but I tried to implement it using recursion.
 *
 * @author [aditi-dey29](https://github.com/aditi-dey29)
 */

/* Hamiltonian Cycle detection algorithm using backtracking */
#include <cassert>
#include <bits/stdc++.h>
using namespace std;

// Number of vertices in the graph
#define V 5

void printSolution(int path[]);

// Checks if the vertex v can be added at index 'pos'
// in the Hamiltonian Cycle constructed so far (stored in 'path[]') 
// graph[V][V] is the adjacency matrix of the given graph.
bool isSafe(int v, bool graph[V][V],
			int path[], int pos){
	// Vertex should be an adjacent vertex of the previously added vertex. 
	if (graph [path[pos - 1]][ v ] == 0)
		return false;

	// Vertex should not have been included already.
	for (int i = 0; i < pos; i++)
		if (path[i] == v)
			return false;

	return true;
}

// A recursive function to recursively solve the hamiltonian cycle problem
bool hamCycleUtil(bool graph[V][V], int path[], int pos){
	// If all vertices are included, we check if there is an edge from the last edge to the first edge. If there is an edge, we return true, else false.
	if (pos == V){
		if (graph[path[pos - 1]][path[0]] == 1) return true;
		else return false;
	}

	// We try the isSafe function for different vertices, and if isSafe returns true, we
    // use the current vertice and recurse for the next vertex. If adding the vertex doesn't give a solution, we remove it by putting -1 in the position.
	for (int v = 1; v < V; v++){
		if (isSafe(v, graph, path, pos)){
			path[pos] = v;
			if (hamCycleUtil (graph, path, pos + 1) == true) return true;
			path[pos] = -1;
		}
	}

	// We return false if no vertex can be added.
	return false;
}

bool hamCycle(bool graph[V][V]){
	int *path = new int[V];
	for (int i = 0; i < V; i++) path[i] = -1;

	// Uisng vertex 0 as the first vertex.
	path[0] = 0;
	if (hamCycleUtil(graph, path, 1) == false ){
		cout << "\nSolution does not exist";
		return false;
	}
    
    cout << "Solution Exists:"
			" Following is one Hamiltonian Cycle \n";
    for (int i = 0; i < V; i++) cout << path[i] << " ";
    cout << path[0] << " "; // Printing the first vertex again to complete the cycle.
	cout << endl;
	return true;
}

// Driver Code
int main(){
	// taking the following graph as example.
	//	(0)--(1)--(2)
	//	| / \ |
	//	| / \ |
	//	| / \ |
	//	(3)-------(4) 
	bool graph1[V][V] = {{0, 1, 0, 1, 0},
			     {1, 0, 1, 1, 1},
			     {0, 1, 0, 0, 1},
			     {1, 1, 0, 0, 1},
			     {0, 1, 1, 1, 0}};
	
	// Printing the solution
	hamCycle(graph1);
	return 0;
}
