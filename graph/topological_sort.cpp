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
 * @brief Function that add edge between two nodes or vertices of graph
 * @param u any node or vertex of graph
 * @param v any node or vertex of graph
 * @returns None
 */
void addEdge(std::vector<std::vector<int>>& adj, int u, int v) {
    adj[u].push_back(v);
}

/**
 * @brief Function to perform Depth First Search on the graph
 * @param v starting vertex for depth first search
 * @param vistied array representing if a node is visited
 * @param graph adjecancy list of the graph
 * @param s stack containing the vertex of topological sort
 * @returns None
 */
void dfs(int v, std::vector<int>& visited, std::vector<std::vector<int>>& graph,
         std::stack<int>& s) {
    visited[v] = 1;
    for (int i = 0; i < graph[v].size(); i++) {
        int neighbour = graph[v][i];
        if (!visited[neighbour]) {
            dfs(neighbour, visited, graph, s);
        }
    }
    s.push(v);
}

/**
 * @brief Function to get the topological sort of the graph
 * @param graph adjecancy list of the graph
 * @param n number of nodes in the graph
 */
std::vector<int> topological_sort(std::vector<std::vector<int>>& graph, int n) {
    std::vector<int> visited(n, 0);
    std::stack<int> s;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, visited, graph, s);
        }
    }
    std::vector<int> ans;
    while (!s.empty()) {
        int elem = s.top();
        s.pop();
        ans.push_back(elem);
    }
    if (ans.size() < n) {  // Cycle detected
        throw std::invalid_argument("cycle present in graph");
    }
    return ans;
}
}  // namespace graph

/**
 * @brief Self-test implementation
 * @returns void
 */
static void test() {
    // Test 1;
    std::cout << "Testing for graph 1\n";
    int n_1 = 6;
    std::vector<std::vector<int>> adj_1(n_1);
    graph::addEdge(adj_1, 4, 0);
    graph::addEdge(adj_1, 5, 0);
    graph::addEdge(adj_1, 5, 2);
    graph::addEdge(adj_1, 2, 3);
    graph::addEdge(adj_1, 3, 1);
    graph::addEdge(adj_1, 4, 1);
    std::vector<int> ans_1 = graph::topological_sort(adj_1, n_1);
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
    std::vector<std::vector<int>> adj_2(n_2);
    graph::addEdge(adj_2, 0, 1);
    graph::addEdge(adj_2, 0, 2);
    graph::addEdge(adj_2, 1, 2);
    graph::addEdge(adj_2, 2, 3);
    graph::addEdge(adj_2, 1, 3);
    graph::addEdge(adj_2, 2, 4);
    std::vector<int> ans_2 = graph::topological_sort(adj_2, n_2);
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
    std::vector<std::vector<int>> adj_3(n_3);
    graph::addEdge(adj_3, 0, 1);
    graph::addEdge(adj_3, 1, 2);
    graph::addEdge(adj_3, 2, 0);
    try {
        graph::topological_sort(adj_3, n_3);
    } catch (std::invalid_argument& err) {
        assert(std::string(err.what()) == "cycle detected in graph");
    }
    std::cout << "Test Passed \n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // Self - test implementation
    return 0;
}
