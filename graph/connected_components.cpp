/**
 *
 * \file
 * \brief [Graph Connected Components
 * (Connected Components)]
 * (https://en.wikipedia.org/wiki/Component_(graph_theory))
 *
 * \author [Ayaan Khan](http://github.com/ayaankhan98)
 *
 * \details
 * A graph is a collection of nodes also called vertices and these vertices
 * are connected by edges. A connected component in a graph refers to a set of
 * vertices which are reachable form one another.
 *
 * <pre>
 * Example - Here is graph with 3 connected components
 *
 *      1   4           5               8
 *     / \ /           / \             / \
 *    2---3           6   7           9   10
 *
 *    first          second           third
 *    component      component        component
 * </pre>
 *
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/**
 * @namespace graph
 * @brief Graph Algorithms
 */

namespace graph {
/**
 * @brief Function that add edge between two nodes or vertices of graph
 *
 * @param adj adjacency list of graph.
 * @param u any node or vertex of graph.
 * @param v any node or vertex of graph.
 */
void addEdge(std::vector<std::vector<int>> *adj, int u, int v) {
    (*adj)[u - 1].push_back(v - 1);
    (*adj)[v - 1].push_back(u - 1);
}

/**
 * @brief Utility function for depth first seach algorithm
 * this function explores the vertex which is passed into.
 *
 * @param adj adjacency list of graph.
 * @param u vertex or node to be explored.
 * @param visited already visited vertices.
 */
void explore(const std::vector<std::vector<int>> *adj, int u,
             std::vector<bool> *visited) {
    (*visited)[u] = true;
    for (auto v : (*adj)[u]) {
        if (!(*visited)[v]) {
            explore(adj, v, visited);
        }
    }
}

/**
 * @brief Function that perfoms depth first search algorithm on graph
 * and calculated the number of connected components.
 *
 * @param adj adjacency list of graph.
 *
 * @return connected_components number of connected components in graph.
 */
int getConnectedComponents(const std::vector<std::vector<int>> *adj) {
    int n = adj->size();
    int connected_components = 0;
    std::vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            explore(adj, i, &visited);
            connected_components++;
        }
    }
    return connected_components;
}
}  // namespace graph

/** Function to test the algorithm */
void tests() {
    std::cout << "Running predefined tests..." << std::endl;
    std::cout << "Initiating Test 1..." << std::endl;
    std::vector<std::vector<int>> adj1(9, std::vector<int>());
    graph::addEdge(&adj1, 1, 2);
    graph::addEdge(&adj1, 1, 3);
    graph::addEdge(&adj1, 3, 4);
    graph::addEdge(&adj1, 5, 7);
    graph::addEdge(&adj1, 5, 6);
    graph::addEdge(&adj1, 8, 9);

    assert(graph::getConnectedComponents(&adj1) == 3);
    std::cout << "Test 1 Passed..." << std::endl;

    std::cout << "Innitiating Test 2..." << std::endl;
    std::vector<std::vector<int>> adj2(10, std::vector<int>());
    graph::addEdge(&adj2, 1, 2);
    graph::addEdge(&adj2, 1, 3);
    graph::addEdge(&adj2, 1, 4);
    graph::addEdge(&adj2, 2, 3);
    graph::addEdge(&adj2, 3, 4);
    graph::addEdge(&adj2, 4, 8);
    graph::addEdge(&adj2, 4, 10);
    graph::addEdge(&adj2, 8, 10);
    graph::addEdge(&adj2, 8, 9);
    graph::addEdge(&adj2, 5, 7);
    graph::addEdge(&adj2, 5, 6);
    graph::addEdge(&adj2, 6, 7);

    assert(graph::getConnectedComponents(&adj2) == 2);
    std::cout << "Test 2 Passed..." << std::endl;
}

/** Main function */
int main() {
    /// running predefined tests
    tests();

    int vertices = int(), edges = int();
    std::cout << "Enter the number of vertices : ";
    std::cin >> vertices;
    std::cout << "Enter the number of edges : ";
    std::cin >> edges;

    std::vector<std::vector<int>> adj(vertices, std::vector<int>());

    int u = int(), v = int();
    while (edges--) {
        std::cin >> u >> v;
        graph::addEdge(&adj, u, v);
    }

    int cc = graph::getConnectedComponents(&adj);
    std::cout << cc << std::endl;
    return 0;
}
