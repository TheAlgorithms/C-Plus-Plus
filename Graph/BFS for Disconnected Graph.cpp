// C++ implementation of modified BFS 
#include<bits/stdc++.h> 
using namespace std; 

// A utility function to add an edge in an 
// undirected graph. 
void addEdge(vector<int> adj[], int u, int v) 
{ 
	adj[u].push_back(v); 
} 

// A utility function to do BFS of graph 
// from a given vertex u. 
void BFSUtil(int u, vector<int> adj[], 
			vector<bool> &visited) 
{ 

	// Create a queue for BFS 
	list<int> q; 

	// Mark the current node as visited and enqueue it 
	visited[u] = true; 
	q.push_back(u); 

	// 'i' will be used to get all adjacent vertices 4 
	// of a vertex list<int>::iterator i; 

	while(!q.empty()) 
	{ 
		// Dequeue a vertex from queue and print it 
		u = q.front(); 
		cout << u << " "; 
		q.pop_front(); 

		// Get all adjacent vertices of the dequeued 
		// vertex s. If an adjacent has not been visited, 
		// then mark it visited and enqueue it 
		for (int i = 0; i != adj[u].size(); ++i) 
		{ 
			if (!visited[adj[u][i]]) 
			{ 
				visited[adj[u][i]] = true; 
				q.push_back(adj[u][i]); 
			} 
		} 
	} 
} 

// This function does BFSUtil() for all 
// unvisited vertices. 
void BFS(vector<int> adj[], int V) 
{ 
	vector<bool> visited(V, false); 
	for (int u=0; u<V; u++) 
		if (visited[u] == false) 
			BFSUtil(u, adj, visited); 
} 

// Driver code 
int main() 
{ 
	int V = 5; 
	vector<int> adj[V]; 

	addEdge(adj, 0, 4); 
	addEdge(adj, 1, 2); 
	addEdge(adj, 1, 3); 
	addEdge(adj, 1, 4); 
	addEdge(adj, 2, 3); 
	addEdge(adj, 3, 4); 
	BFS(adj, V); 
	return 0; 
}
