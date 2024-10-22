/**
 * @file
 * @brief [Topological Sort
 * Algorithm](https://en.wikipedia.org/wiki/Topological_sorting)
 * @details
 * Topological sorting of a directed graph is a linear ordering or its vertices
 * such that for every directed edge (u,v) from vertex u to vertex v, u comes
 * before v in the oredering.
 *
 * A topological sort is possible only in a directed acyclic graph (DAG).
 * This file contains code of finding topological sort using Kahn's Algorithm
 * which involves using Depth First Search technique
 */

#include <algorithm>  // For std::reverse
#include <cassert>    // For assert
#include <iostream>   // For IO operations
#include <stack>      // For std::stack
#include <stdexcept>  // For std::invalid_argument
#include <vector>     // For std::vector

/**
 * @namespace graph
 * @brief Graph algorithms
 */
namespace graph {

/**
 * @namespace topological_sort
 * @brief Topological Sort Algorithm
 */
namespace topological_sort {
/**
 * @class Graph
 * @brief Class that represents a directed graph and provides methods for
 * manipulating the graph
 */
class Graph {
 private:
    int n;                              // Number of nodes
    std::vector<std::vector<int>> adj;  // Adjacency list representation

 public:
    /**
     * @brief Constructor for the Graph class
     * @param nodes Number of nodes in the graph
     */
    Graph(int nodes) : n(nodes), adj(nodes) {}

    /**
     * @brief Function that adds an edge between two nodes or vertices of graph
     * @param u Start node of the edge
     * @param v End node of the edge
     */
    void addEdge(int u, int v) { adj[u].push_back(v); }

    /**
     * @brief Get the adjacency list of the graph
     * @returns A reference to the adjacency list
     */
    const std::vector<std::vector<int>>& getAdjacencyList() const {
        return adj;
    }

    /**
     * @brief Get the number of nodes in the graph
     * @returns The number of nodes
     */
    int getNumNodes() const { return n; }
};

/**
 * @brief Function to perform Depth First Search on the graph
 * @param v Starting vertex for depth-first search
 * @param visited Array representing whether each node has been visited
 * @param graph Adjacency list of the graph
 * @param s Stack containing the vertices for topological sorting
 */
void dfs(int v, std::vector<int>& visited,
         const std::vector<std::vector<int>>& graph, std::stack<int>& s) {
    visited[v] = 1;
    for (int neighbour : graph[v]) {
        if (!visited[neighbour]) {
            dfs(neighbour, visited, graph, s);
        }
    }
    s.push(v);
}

/**
 * @brief Function to get the topological sort of the graph
 * @param g Graph object
 * @returns A vector containing the topological order of nodes
 */
std::vector<int> topologicalSort(const Graph& g) {
    int n = g.getNumNodes();
    const auto& adj = g.getAdjacencyList();
    std::vector<int> visited(n, 0);
    std::stack<int> s;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, visited, adj, s);
        }
    }

    std::vector<int> ans;
    while (!s.empty()) {
        int elem = s.top();
        s.pop();
        ans.push_back(elem);
    }

    if (ans.size() < n) {  // Cycle detected
        throw std::invalid_argument("cycle detected in graph");
    }
    return ans;
}
}  // namespace topological_sort
}  // namespace graph

/**
 * @brief Self-test implementation
 * @returns void
 */
static void test() {
    // Test 1
    std::cout << "Testing for graph 1\n";
    int n_1 = 6;
    graph::topological_sort::Graph graph1(n_1);
    graph1.addEdge(4, 0);
    graph1.addEdge(5, 0);
    graph1.addEdge(5, 2);
    graph1.addEdge(2, 3);
    graph1.addEdge(3, 1);
    graph1.addEdge(4, 1);
    std::vector<int> ans_1 = graph::topological_sort::topologicalSort(graph1);
    std::vector<int> expected_1 = {5, 4, 2, 3, 1, 0};
    std::cout << "Topological Sorting Order: ";
    for (int i : ans_1) {
        std::cout << i << " ";
    }
    std::cout << '\n';
    assert(ans_1 == expected_1);
    std::cout << "Test Passed\n\n";

    // Test 2
    std::cout << "Testing for graph 2\n";
    int n_2 = 5;
    graph::topological_sort::Graph graph2(n_2);
    graph2.addEdge(0, 1);
    graph2.addEdge(0, 2);
    graph2.addEdge(1, 2);
    graph2.addEdge(2, 3);
    graph2.addEdge(1, 3);
    graph2.addEdge(2, 4);
    std::vector<int> ans_2 = graph::topological_sort::topologicalSort(graph2);
    std::vector<int> expected_2 = {0, 1, 2, 4, 3};
    std::cout << "Topological Sorting Order: ";
    for (int i : ans_2) {
        std::cout << i << " ";
    }
    std::cout << '\n';
    assert(ans_2 == expected_2);
    std::cout << "Test Passed\n\n";

    // Test 3 - Graph with cycle
    std::cout << "Testing for graph 3\n";
    int n_3 = 3;
    graph::topological_sort::Graph graph3(n_3);
    graph3.addEdge(0, 1);
    graph3.addEdge(1, 2);
    graph3.addEdge(2, 0);
    try {
        graph::topological_sort::topologicalSort(graph3);
    } catch (std::invalid_argument& err) {
        assert(std::string(err.what()) == "cycle detected in graph");
    }
    std::cout << "Test Passed\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self test implementations
    return 0;
}
