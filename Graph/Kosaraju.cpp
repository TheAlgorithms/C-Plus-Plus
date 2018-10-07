#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
Kosaraju's Double Pass Algorithm to find Strongly Connected Components

A linear time Algorithm to find SCC.

Refer: https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm
*/

const int MAXN = 1e5;
vector <int> adjacencyList[MAXN];
vector <int> reverseAdjacencyList[MAXN];
vector <bool> isVisited(MAXN, false);
stack <int> ordering;
int nodeCount, edgeCount;

/*
void dfs(int): A function to do DFS and
store the last seen time of nodes
*/

void dfs(int startVertex)
{
	isVisited[startVertex] = true;
	for(int i : adjacencyList[startVertex])
	{
		if(!isVisited[i])
		{
			dfs(i);
		}
	}
	ordering.push(startVertex);
}

/*
void dfsAgain(int): A Function to print the nodes in a 
particular SCC.
*/

void dfsAgain(int startVertex)
{
	isVisited[startVertex] = true;
	cout << startVertex << ' ';
	for(int i : reverseAdjacencyList[startVertex])
	{
		if(!isVisited[i])
		{
			dfsAgain(i);
		}
	}
}

/*
void kosaraju(): A function to call the dfsAgain function
based on the Stack ordering.
*/

void kosaraju()
{
	while(!ordering.empty())
	{
		int currentVertex = ordering.top();
		ordering.pop();
		if(!isVisited[currentVertex])
		{
			dfsAgain(currentVertex);
			cout << '\n';
		}
	}
}

int main()
{
	// Input part
	cin >> nodeCount >> edgeCount;
	for(int i = 0; i < edgeCount; i++)
	{
		int source, destination;
		cin >> source >> destination;
		// Storing the Graph in adjacency list and reverse graph
		// in reverse adjacency list
		adjacencyList[source].push_back(destination);
		reverseAdjacencyList[destination].push_back(source);
	}
	/* // Uncomment this part to Test the program manually
	// Expected answer
	nodeCount = 5;
	edgeCount = 5;
	adjacencyList[2].push_back(1);
	adjacencyList[1].push_back(3);
	adjacencyList[3].push_back(2);
	adjacencyList[1].push_back(4);
	adjacencyList[4].push_back(5);
	reverseAdjacencyList[1].push_back(2);
	reverseAdjacencyList[3].push_back(1);
	reverseAdjacencyList[2].push_back(3);
	reverseAdjacencyList[4].push_back(1);
	reverseAdjacencyList[5].push_back(4); 
	// Expected answer is: 
	// 1 2 3
	// 4
	// 5*/
	for(int i = 1; i <= nodeCount; i++)
	{
		if(!isVisited[i])
		{
			dfs(i);
		}
	}
	// Fill the visited with false
	fill(isVisited.begin(), isVisited.end(), false);
	kosaraju();
	return 0;
}