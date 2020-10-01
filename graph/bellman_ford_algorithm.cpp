// A C++ program for Bellman-Ford's Single Source Shortest Path Algorithm. 
// The output is the shortest distance to all vertices from the source vertex. 
// If a negative weight cycle exists, then shortest distances are not calculated and negative weight cycle is reported.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>  

/* The main function finds the shortest distances from the source vertex to all other vertices present in the graph using Bellman-Ford algorithm. 
The function also detects negative weight cycle, if present in the graph.
The row graph[i] represents i-th edge with three values u, v and w. */

void BellmanFord(int graph[][3], int m, int n, int source) 
{ 
	// Initialize distance from the source vertex to all other vertices as infinite. 
	int distance[m]; 
	for (int i = 0; i < m; i++) 
		{
		    distance[i] = INT_MAX;
		} 

	// Initialize distance of source as 0 
	distance[source] = 0; 

	// Relax all edges |V| - 1 times. 
	// A simple shortest path from source vertex to any other vertex can have at-most |V| - 1 edges 
	for (int i = 0; i < m - 1; i++) 
	{ 
		for (int j = 0; j < n; j++) 
		{ 
			if (distance[graph[j][0]] + graph[j][2] < distance[graph[j][1]]) 
				{
				    distance[graph[j][1]] = distance[graph[j][0]] + graph[j][2]; 
				}
		} 
	} 

	// Check for negative-weight cycles in the graph. 
	// The above step confirms shortest distances if graph doesn't contain negative weight cycle.
	for (int i = 0; i < n; i++) 
	{ 
		int x = graph[i][0]; 
		int y = graph[i][1]; 
		int weight = graph[i][2]; 
		if (distance[x] != INT_MAX && distance[x] + weight < distance[y]) 
			{
			    std::cout << "Graph contains negative weight cycle \n"; 
			}
    } 

	std::cout<< "Vertex \t\t Distance of the vertex from the source vertex \n"; 
	for (int i = 0; i < m; i++) 
		{
			std::cout << i << "\t\t\t\t" << distance[i] <<"\n"; 
		}
} 

// Driver program to test the previous functions 
int main() 
{ 
	int m = 4; // Total number of vertices in graph 
	int n = 6; // Total number of edges in graph 

	/* Every edge has three values (u, v, w) where 
		u = start vertex of the edge (u,v)
		v = end vertex of the edge (u,v)
		w is the weight of the edge (u,v)
    */
	int graph[][3] = {   { 0, 1, -2 }, { 0, 2, 5 }, 
					     { 1, 2, 4 },  { 1, 3, 1 }, 
					     { 3, 2, 4 },  { 3, 1, 2 }   }; 

	BellmanFord(graph, m, n, 0); 
	return 0; 
} 
