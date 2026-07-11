/**
 * @file
 * @brief Implementation of [Dijkstra's Shortest Path Algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
 * using an Adjacency Matrix representation (O(V^2) approach, without a
 * priority queue).
 *
 * @details
 * This version of Dijkstra's algorithm is best suited for dense graphs
 * where the number of edges is close to V^2, since it avoids the overhead
 * of a priority queue and instead uses a simple linear scan to find the
 * next closest unvisited vertex.
 *
 * ### Algorithm
 * 1. Initialize distance of source vertex as 0 and all others as infinity.
 * 2. Repeat V times:
 *    a. Pick the unvisited vertex with the smallest known distance.
 *    b. Mark it visited.
 *    c. Update (relax) the distances of its neighbors.
 * 3. After all vertices are visited, `dist[]` holds shortest distances.
 *
 * ### Complexity
 * - Time: O(V^2) - for each of the V vertices, we scan all V vertices to
 *   find the minimum and relax edges.
 * - Space: O(V^2) for the adjacency matrix.
 *
 * @author [binarymind-dev](https://github.com/binarymind-dev)
 */

#include <cassert>   /// for assert
#include <climits>   /// for INT_MAX
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace graph
 * @brief Graph algorithms
 */
namespace graph {
/**
 * @namespace dijkstra_adjacency_matrix
 * @brief Functions for the [Dijkstra's Shortest Path]
 * (https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm) implementation
 * using an adjacency matrix
 */
namespace dijkstra_adjacency_matrix {
/**
 * @brief Finds the unvisited vertex with the minimum distance value
 * @param dist Vector of current shortest distances from source
 * @param visited Vector tracking which vertices have been finalized
 * @param numVertices Total number of vertices in the graph
 * @returns Index of the vertex with minimum distance, or -1 if none found
 */
int findMinDistanceVertex(const std::vector<int> &dist,
                           const std::vector<bool> &visited,
                           int numVertices) {
    int minDist = INT_MAX;
    int minIndex = -1;

    for (int v = 0; v < numVertices; v++) {
        if (!visited[v] && dist[v] <= minDist) {
            minDist = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

/**
 * @brief Computes shortest distances from a source vertex to all other
 * vertices using an adjacency matrix representation of the graph.
 * @param graphMatrix Adjacency matrix where graphMatrix[i][j] is the edge
 * weight between i and j (0 means no edge)
 * @param source The starting vertex
 * @returns A vector containing shortest distances from source;
 * unreachable vertices are marked with INT_MAX
 */
std::vector<int> dijkstra(const std::vector<std::vector<int>> &graphMatrix,
                           int source) {
    int numVertices = graphMatrix.size();
    std::vector<int> dist(numVertices, INT_MAX);
    std::vector<bool> visited(numVertices, false);

    dist[source] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = findMinDistanceVertex(dist, visited, numVertices);

        if (u == -1) {
            break;  // remaining vertices are unreachable
        }

        visited[u] = true;

        for (int v = 0; v < numVertices; v++) {
            bool hasEdge = graphMatrix[u][v] != 0;
            bool isUnvisited = !visited[v];
            bool isReachable = dist[u] != INT_MAX;

            if (hasEdge && isUnvisited && isReachable &&
                dist[u] + graphMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graphMatrix[u][v];
            }
        }
    }

    return dist;
}
}  // namespace dijkstra_adjacency_matrix
}  // namespace graph

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // Test case 1: standard weighted graph
    std::vector<std::vector<int>> graph1 = {
        {0, 4, 1, 0, 0},
        {4, 0, 2, 1, 0},
        {1, 2, 0, 5, 0},
        {0, 1, 5, 0, 3},
        {0, 0, 0, 3, 0}
    };

    std::vector<int> result1 =
        graph::dijkstra_adjacency_matrix::dijkstra(graph1, 0);
    assert(result1[0] == 0);
    assert(result1[1] == 3);
    assert(result1[2] == 1);
    assert(result1[3] == 4);
    assert(result1[4] == 7);

    // Test case 2: single vertex, no edges
    std::vector<std::vector<int>> graph2 = {{0}};
    std::vector<int> result2 =
        graph::dijkstra_adjacency_matrix::dijkstra(graph2, 0);
    assert(result2[0] == 0);

    // Test case 3: disconnected graph (unreachable vertex)
    std::vector<std::vector<int>> graph3 = {
        {0, 2, 0},
        {2, 0, 0},
        {0, 0, 0}
    };
    std::vector<int> result3 =
        graph::dijkstra_adjacency_matrix::dijkstra(graph3, 0);
    assert(result3[0] == 0);
    assert(result3[1] == 2);
    assert(result3[2] == INT_MAX);  // vertex 2 is unreachable

    std::cout << "All test cases passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
