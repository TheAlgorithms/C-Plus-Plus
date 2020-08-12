/**
 *
 * \file
 * \brief [Breadth First Search Algorithm
 * (Breadth First Search)](https://en.wikipedia.org/wiki/Breadth-first_search)
 *
 * \author [Ayaan Khan](http://github.com/ayaankhan98)
 *
 * \details
 * Breadth First Search also quoted as BFS is a Graph Traversal Algorithm.
 * Time Complexity O(|V| + |E|) where V are the number of vertices and E
 * are the number of edges in the graph.
 *
 * Applications of Breadth First Search are
 *
 * 1. Finding shortest path between two vertices say u and v, with path
 *    length measured by number of edges (an advantage over depth first
 *    search algorithm)
 * 2. Ford-Fulkerson Method for computing the maximum flow in a flow network.
 * 3. Testing bipartiteness of a graph.
 * 4. Cheney's Algorithm, Copying garbage collection.
 *
 * And there are many more...
 *
 * <h4>working</h4>
 * In the implementation below we first created a graph using the adjacency
 * list representation of graph.
 * Breadth First Search Works as follows
 * it requires a vertex as a start vertex, Start vertex is that vertex
 * from where you want to start traversing the graph.
 * We maintain a bool array or a vector to keep track of the vertices
 * which we have visited so that we do not traverse the visited vertices
 * again and again and eventually fall into an infinite loop. Along with this
 * boolen array we use a Queue.
 *
 * 1. First we mark the start vertex as visited.
 * 2. Push this visited vertex in the Queue.
 * 3. while the queue is not empty we repeat the following steps
 *
 *      1. Take out an element from the front of queue
 *      2. Explore the adjacency list of this vertex
 *         if element in the adjacency list is not visited then we
 *         push that element into the queue and mark this as visited
 *
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

/**
 * \namespace graph
 * \brief Graph algorithms
 */
namespace graph {
/**
 * \brief
 * Adds a directed edge from vertex u to vertex v.
 *
 * @param graph Adjacency list representation of graph
 * @param u first vertex
 * @param v second vertex
 *
 */
void add_directed_edge(std::vector<std::vector<int>> *graph, int u, int v) {
    (*graph)[u].push_back(v);
}

/**
 * \brief
 * Adds an undirected edge from vertex u to vertex v.
 * Essentially adds too directed edges to the adjacency list reprsentation
 * of the graph.
 *
 * @param graph Adjacency list representation of graph
 * @param u first vertex
 * @param v second vertex
 *
 */
void add_undirected_edge(std::vector<std::vector<int>> *graph, int u, int v) {
    add_directed_edge(graph, u, v);
    add_directed_edge(graph, v, u);
}

/**
 * \brief
 * Function performs the breadth first search algorithm over the graph
 *
 * @param graph Adjacency list representation of graph
 * @param start vertex from where traversing starts
 * @returns a binary vector indicating which vertices were visited during the search.
 *
 */
std::vector<bool> breadth_first_search(const std::vector<std::vector<int>> &graph,
                                      int start) {
    /// vector to keep track of visited vertices
    std::vector<bool> visited(graph.size(), false);
    /// a queue that stores vertices that need to be further explored
    std::queue<int> tracker;

    /// mark the starting vertex as visited
    visited[start] = true;
    tracker.push(start);
    while (!tracker.empty()) {
        size_t vertex = tracker.front();
        tracker.pop();
        for (auto x : graph[vertex]) {
            /// if the vertex is not visited then mark it as visited
            /// and push it to the queue
            if (!visited[x]) {
                visited[x] = true;
                tracker.push(x);
            }
        }
    }
    return visited;
}
}  // namespace graph

void tests() {
    /// Test 1 Begin
    std::vector<std::vector<int>> graph(4, std::vector<int>());
    graph::add_undirected_edge(&graph, 0, 1);
    graph::add_undirected_edge(&graph, 1, 2);
    graph::add_undirected_edge(&graph, 2, 3);

    std::vector<bool> returned_result = graph::breadth_first_search(graph, 2);
    std::vector<bool> correct_result = {true, true, true, true};

    assert(std::equal(correct_result.begin(), correct_result.end(),
                      returned_result.begin()));
    std::cout << "Test 1 Passed..." << std::endl;

    /// Test 2 Begin
    returned_result = graph::breadth_first_search(graph, 0);

    assert(std::equal(correct_result.begin(), correct_result.end(),
                      returned_result.begin()));
    std::cout << "Test 2 Passed..." << std::endl;

    /// Test 3 Begins
    graph.clear();
    graph.resize(6);
    graph::add_directed_edge(&graph, 0, 1);
    graph::add_directed_edge(&graph, 0, 2);
    graph::add_directed_edge(&graph, 1, 3);
    graph::add_directed_edge(&graph, 2, 3);
    graph::add_directed_edge(&graph, 1, 4);
    graph::add_directed_edge(&graph, 3, 5);

    returned_result = graph::breadth_first_search(graph, 2);
    correct_result = {false, false, true, true, false, true};

    assert(std::equal(correct_result.begin(), correct_result.end(),
                      returned_result.begin()));
    std::cout << "Test 3 Passed..." << std::endl;
}

/** Main function */
int main() {
    tests();

    size_t vertices = 0, edges = 0;
    std::cout << "Enter the number of vertices: ";
    std::cin >> vertices;
    std::cout << "Enter the number of edges: ";
    std::cin >> edges;

    std::vector<std::vector<int>> graph(vertices);

    std::cout << "Enter space-separated pairs of vertices that form edges: "
              << std::endl;
    while (edges--) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        // Decrement the vertex index so that we can read more convenint
        // 1-based indexing from the user input.
        graph::add_directed_edge(&graph, u - 1, v - 1);
    }

    graph::breadth_first_search(graph, 0);
    return 0;
}
