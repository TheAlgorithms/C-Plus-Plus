/**
 * @file
 * @brief Find the shortest paths between all pairs of vertices in a graph using
 * the [Floyd-Warshall Algorithm](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm).
 * @details
 * The Floyd-Warshall algorithm is an algorithm for finding shortest paths in a 
 * weighted graph with positive or negative edge weights (but with no negative cycles).
 * The algorithm works for both directed and undirected graphs. 
 * It uses dynamic programming to iteratively improve the estimate of the shortest path 
 * between two vertices by considering each vertex as an intermediate point.
 * 
 * Time Complexity: O(n^3)
 * where n is the number of vertices in the graph.
 * 
 * Space Complexity: O(n^2)
 * 
 * @author [Naman Jain](https://github.com/namanmodi65)
 */

#include <cassert>   /// for std::assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector
#include <limits>    /// for std::numeric_limits

/**
 * @brief Function to implement Floyd-Warshall Algorithm
 * @param graph The input adjacency matrix of the graph, where graph[i][j] 
 * represents the weight of the edge from vertex i to vertex j.
 * If there is no edge, it should be set to infinity.
 * @return A matrix of shortest distances between all pairs of vertices.
 */

std::vector<std::vector<int>> floyd_warshall(std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<std::vector<int>> dist = graph;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != std::numeric_limits<int>::max() && 
                    dist[k][j] != std::numeric_limits<int>::max()) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (dist[i][i] < 0) {
            std::cerr << "Graph contains a negative cycle\n";
            return {};
        }
    }

    return dist;
}


/**
 * @brief Test cases for Floyd-Warshall algorithm
 * @returns void
 */
static void tests() {
    const int INF = std::numeric_limits<int>::max();

    std::vector<std::vector<int>> graph1 = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };

    std::vector<std::vector<int>> expected1 = {
        {0, 5, 8, 9},
        {INF, 0, 3, 4},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };

    assert(floyd_warshall(graph1) == expected1);

    std::vector<std::vector<int>> graph2 = {
        {0, 1, INF, INF},
        {INF, 0, -1, INF},
        {INF, INF, 0, -1},
        {-1, INF, INF, 0}
    };

    std::vector<std::vector<int>> expected2 = {
        {0, 1, 0, -1},
        {-1, 0, -1, -2},
        {-2, -1, 0, -1},
        {-1, 0, -1, 0}
    };

    assert(floyd_warshall(graph2) == expected2);

    std::vector<std::vector<int>> graph3 = {{0}};
    std::vector<std::vector<int>> expected3 = {{0}};
    assert(floyd_warshall(graph3) == expected3);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function to run tests
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
