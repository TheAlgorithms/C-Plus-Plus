
#include <iostream>
#include <cstdio>
#include <cstdlib>
#define V 5
using namespace std;
void printSolution(int path[]);
bool isSafe(int v, bool graph[V][V], int path[], int pos)
{
	if (graph[path[pos - 1]][v] == 0)
		return false;
	for (int i = 0; i < pos; i++)
		if (path[i] == v)
			return false;
	return true;
}

/* solve hamiltonian cycle problem */
bool hamCycleUtil(bool graph[V][V], int path[], int pos)
{
	if (pos == V)
	{
		if (graph[path[pos - 1]][path[0]] == 1)
			return true;
		else
			return false;
	}

	for (int v = 1; v < V; v++)
	{
		if (isSafe(v, graph, path, pos))
		{
			path[pos] = v;
			if (hamCycleUtil(graph, path, pos + 1) == true)
				return true;
			path[pos] = -1;
		}
	}
	return false;
}

/* solves the Hamiltonian Cycle problem using Backtracking.*/
bool hamCycle(bool graph[V][V])
{
	int *path = new int[V];
	for (int i = 0; i < V; i++)
		path[i] = -1;
	path[0] = 0;
	if (hamCycleUtil(graph, path, 1) == false)
	{
		cout << "\nSolution does not exist" << endl;
		return false;
	}
	printSolution(path);
	return true;
}

/* Main */
void printSolution(int path[])
{
	cout << "Solution Exists:";
	cout << " Following is one Hamiltonian Cycle \n" << endl;
	for (int i = 0; i < V; i++)
		cout << path[i] << "  ";
	cout << path[0] << endl;
}

int main()
{
	/* Let us create the following graph
	   (0)--(1)--(2)
		|   / \   |
		|  /   \  |
		| /     \ |
	   (3)-------(4)    */
	bool graph1[V][V] = { {0, 1, 0, 1, 0},
					   {1, 0, 1, 1, 1},
					   {0, 1, 0, 0, 1},
					   {1, 1, 0, 0, 1},
					   {0, 1, 1, 1, 0},
	};
	hamCycle(graph1);

	/* Let us create the following graph
	   (0)--(1)--(2)
		|   / \   |
		|  /   \  |
		| /     \ |
	   (3)       (4)    */
	bool graph2[V][V] = { {0, 1, 0, 1, 0},
					  {1, 0, 1, 1, 1},
					  {0, 1, 0, 0, 1},
					  {1, 1, 0, 0, 0},
					  {0, 1, 1, 0, 0},
	};
	hamCycle(graph2);
	return 0;
}
