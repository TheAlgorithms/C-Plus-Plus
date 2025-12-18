/**
 * @file
 * @brief [Floyd-Warshall Algorithm
 * (Floyd-Warshall All-Pairs Shortest Path)]
 * (https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm)
 *
 * @author [Mikes Tsampounaris](https://github.com/mikestsa)
 *
 * @details
 * Floyd-Warshall Algorithm is used to find the shortest paths between
 * all pairs of vertices in a weighted graph. The algorithm works with
 * both positive and negative edge weights (but no negative cycles).
 *
 * The algorithm uses dynamic programming approach. For each pair of
 * vertices (i, j), it checks if going through an intermediate vertex k
 * provides a shorter path than the current known path.
 *
 * Time Complexity: O(V^3) where V is the number of vertices.
 * Space Complexity: O(V^2) for the distance matrix.
 *
 */
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

constexpr int64_t INF = std::numeric_limits<int64_t>::max();

/**
 * @namespace graph
 * @brief Graph Algorithms
 */
namespace graph {

/**
 * @brief Function that adds a directed edge between two vertices
 *
 * @param adj adjacency matrix representation of the graph
 * @param u source vertex (1-indexed)
 * @param v destination vertex (1-indexed)
 * @param w weight of the edge
 */
void addEdge(std::vector<std::vector<int64_t>>* adj, int u, int v, int64_t w) {
    (*adj)[u - 1][v - 1] = w;
}

/**
 * @brief Function runs the Floyd-Warshall algorithm and computes
 * shortest paths between all pairs of vertices.
 *
 * @param adj adjacency matrix of the graph
 *
 * @return matrix containing shortest distances between all pairs
 */
std::vector<std::vector<int64_t>> floydWarshall(
    std::vector<std::vector<int64_t>>* adj) {
    /// n denotes the number of vertices in graph
    int n = adj->size();

    /// copy the adjacency matrix to dist
    std::vector<std::vector<int64_t>> dist = *adj;

    /// for each intermediate vertex k
    for (int k = 0; k < n; k++) {
        /// for each source vertex i
        for (int i = 0; i < n; i++) {
            /// for each destination vertex j
            for (int j = 0; j < n; j++) {
                /// if path through k is shorter, update distance
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    return dist;
}

/**
 * @brief Function to check if the graph contains a negative cycle
 *
 * @param dist the distance matrix after running Floyd-Warshall
 *
 * @return true if negative cycle exists, false otherwise
 */
bool hasNegativeCycle(const std::vector<std::vector<int64_t>>& dist) {
    int n = dist.size();
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Function to get shortest path distance between two vertices
 *
 * @param dist the distance matrix
 * @param s source vertex (0-indexed)
 * @param t target vertex (0-indexed)
 *
 * @return shortest distance if target is reachable from source else -1
 */
int64_t getDistance(const std::vector<std::vector<int64_t>>& dist, int s,
                    int t) {
    if (dist[s][t] != INF) {
        return dist[s][t];
    }
    return -1;
}

}  // namespace graph

/** Function to test the Algorithm */
void tests() {
    std::cout << "Initiating Predefined Tests..." << std::endl;
    std::cout << "Initiating Test 1..." << std::endl;

    std::vector<std::vector<int64_t>> adj1(4, std::vector<int64_t>(4, INF));
    for (int i = 0; i < 4; i++) {
        adj1[i][i] = 0;
    }
    graph::addEdge(&adj1, 1, 2, 3);
    graph::addEdge(&adj1, 1, 4, 5);
    graph::addEdge(&adj1, 2, 1, 2);
    graph::addEdge(&adj1, 2, 4, 4);
    graph::addEdge(&adj1, 3, 2, 1);
    graph::addEdge(&adj1, 4, 3, 2);

    auto dist1 = graph::floydWarshall(&adj1);

    assert(graph::getDistance(dist1, 0, 2) == 7);  // 1 -> 4 -> 3 = 5 + 2 = 7
    std::cout << "Test 1 Passed..." << std::endl;

    std::cout << "Initiating Test 2..." << std::endl;
    assert(graph::getDistance(dist1, 2, 0) == 3);  // 3 -> 2 -> 1 = 1 + 2 = 3
    std::cout << "Test 2 Passed..." << std::endl;

    std::cout << "Initiating Test 3..." << std::endl;
    std::vector<std::vector<int64_t>> adj2(4, std::vector<int64_t>(4, INF));
    for (int i = 0; i < 4; i++) {
        adj2[i][i] = 0;
    }
    graph::addEdge(&adj2, 1, 2, 4);
    graph::addEdge(&adj2, 2, 3, -2);
    graph::addEdge(&adj2, 3, 4, 3);

    auto dist2 = graph::floydWarshall(&adj2);

    assert(graph::getDistance(dist2, 0, 2) == 2);  // 1 -> 2 -> 3 = 4 + (-2) = 2
    assert(graph::getDistance(dist2, 0, 3) ==
           5);  // 1 -> 2 -> 3 -> 4 = 4 + (-2) + 3 = 5
    assert(!graph::hasNegativeCycle(dist2));
    std::cout << "Test 3 Passed..." << std::endl;

    std::cout << "Initiating Test 4..." << std::endl;
    std::vector<std::vector<int64_t>> adj3(1, std::vector<int64_t>(1, 0));
    auto dist3 = graph::floydWarshall(&adj3);
    assert(graph::getDistance(dist3, 0, 0) == 0);
    std::cout << "Test 4 Passed..." << std::endl;

    std::cout << "All Tests Passed..." << std::endl << std::endl;
}

/** Main function */
int main() {
    // running predefined tests
    tests();

    int vertices = int(), edges = int();
    std::cout << "Enter the number of vertices : ";
    std::cin >> vertices;
    std::cout << "Enter the number of edges : ";
    std::cin >> edges;

    std::vector<std::vector<int64_t>> adj(vertices,
                                          std::vector<int64_t>(vertices, INF));
    for (int i = 0; i < vertices; i++) {
        adj[i][i] = 0;
    }

    int u = int(), v = int();
    int64_t w = int64_t();
    std::cout << "Enter edges (u v weight):" << std::endl;
    while (edges--) {
        std::cin >> u >> v >> w;
        graph::addEdge(&adj, u, v, w);
    }

    auto dist = graph::floydWarshall(&adj);

    if (graph::hasNegativeCycle(dist)) {
        std::cout << "Graph contains a negative cycle!" << std::endl;
    } else {
        int s = int(), t = int();
        std::cout << "Enter source and target vertices : ";
        std::cin >> s >> t;
        int64_t result = graph::getDistance(dist, s - 1, t - 1);
        if (result == -1) {
            std::cout << "Target not reachable from source" << std::endl;
        } else {
            std::cout << "Shortest Path Distance : " << result << std::endl;
        }
    }
    return 0;
}