// C++ Program for Dijkstra's dial implementation

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdint>
constexpr int64_t INF = 0x3f3f3f3f;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
    int64_t V; // No. of vertices
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    std::list<std::pair<int64_t, int64_t>> *adj;

public:
	// Graph(int V); // Constructor
    explicit Graph(int64_t V) : V(V), adj(new std::list<std::pair<int64_t, int64_t>>[V]) {}

	// function to add an edge to graph
	void addEdge(int64_t u, int64_t v, int64_t w);

	// prints shortest path from s
	std::vector<int64_t> shortestPath(int64_t s, int64_t W);
};

// adds edge between u and v of weight w
void Graph::addEdge(int64_t u, int64_t v, int64_t w)
{
	adj[u].emplace_back(std::make_pair(v, w));
	adj[v].emplace_back(std::make_pair(u, w));
}

// Prints shortest paths from src to all other vertices.
// W is the maximum weight of an edge
std::vector<int64_t> Graph::shortestPath(int64_t src, int64_t W)
{
	/* With each distance, iterator to that vertex in
	its bucket is stored so that vertex can be deleted
	in O(1) at time of updation. So
	dist[i].first = distance of ith vertex from src vertex
	dist[i].second = iterator to vertex i in bucket number */
	std::vector<std::pair<int64_t, std::list<int64_t>::iterator> > dist(V);

	// Initialize all distances as infinite (INF)
	for (int64_t i = 0; i < V; i++) {
        dist[i].first = INF;
    }

	// Create buckets B[].
	// B[i] keep vertex of distance label i
	std::vector<std::list<int64_t>> B(W * V + 1);

	B[0].emplace_back(src);
	dist[src].first = 0;

	//
	int64_t idx = 0;
	while (true)
	{
		// Go sequentially through buckets till one non-empty
		// bucket is found
		while (B[idx].size() == 0 && idx < W*V) {
            idx++;
        }

		// If all buckets are empty, we are done.
		if (idx == W * V) {
            break;
        }
			

		// Take top vertex from bucket and pop it
		int64_t u = B[idx].front();
		B[idx].pop_front();

		// Process all adjacents of extracted vertex 'u' and
		// update their distanced if required.
		for (auto i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			int64_t v = (*i).first;
			int64_t weight = (*i).second;

			int64_t du = dist[u].first;
			int64_t dv = dist[v].first;

			// If there is shorted path to v through u.
			if (dv > du + weight)
			{
				// If dv is not INF then it must be in B[dv]
				// bucket, so erase its entry using iterator
				// in O(1)
				if (dv != INF) {
                    B[dv].erase(dist[v].second);
                }

				// updating the distance
				dist[v].first = du + weight;
				dv = dist[v].first;

				// pushing vertex v into updated distance's bucket
				B[dv].push_front(v);

				// storing updated iterator in dist[v].second
				dist[v].second = B[dv].begin();
			}
		}
	}

	// Print shortest distances stored in dist[]
    std::vector<int64_t> result;
	for (int64_t i = 0; i < V; ++i) {
        result.emplace_back(dist[i].first);
    }
    return result;
}

/*******************************************************************************
 * @brief Self-test implementations
 * @returns void
 *******************************************************************************/
static void test() {
    int64_t V = 9;
	Graph g(V);

	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	// maximum weighted edge - 14
	g.shortestPath(0, 14);
    std::vector<uint64_t> expected_result = {0, 4, 12, 19, 21, 11, 9, 8, 14};
    std::vector<int64_t> derived_result = g.shortestPath(0, 14);
    std::cout << "1st test: ";

    if (std::equal(expected_result.begin(), expected_result.end(), derived_result.begin())) {
        std::cout << "Passed!" << std::endl;
    }
    else {
        std::cout << "Failed!" << std::endl;
    }
}

// Driver program to test methods of graph class
int main()
{
    test();
	return 0;
}
