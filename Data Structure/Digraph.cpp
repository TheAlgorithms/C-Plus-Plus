#include <iostream>
#include <vector>
using namespace std;

struct Edge {
	int src, dest;
};

class Graph
{
public:
	vector<vector<int>> adjList;

	Graph(vector<Edge> const &edges, int N)
	{
		adjList.resize(N);

		for (auto &edge : edges)
		{
			adjList[edge.src].push_back(edge.dest);
		}
	}
};

void printGraph(Graph const& graph, int N)
{
	for (int i = 0; i < N; i++)
	{
		cout << i << "-->";

		for (int v : graph.adjList[i])
			cout << v << " ";
		cout << endl;
	}
}

int main()
{
	vector<Edge> edges =
	{
		{0,1},{1,2},{2,0},{2,1},
	{3,2},{4,5},{5,4}
	};

	int N = 6;
	Graph graph(edges, N);

	printGraph(graph, N);

	return 0;
}
