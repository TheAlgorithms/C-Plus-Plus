/**
 * @file floyd_warshall.cpp
 * @brief Implementation of the Floyd-Warshall algorithm in C++
 * @details 
 * The Floyd-Warshall algorithm is used to find the shortest paths between all pairs of vertices
 * in a weighted graph. It is particularly useful for dense graphs where the number of edges is
 * close to the number of vertices squared. The algorithm can handle graphs with positive or negative
 * edge weights but will not correctly handle graphs with negative weight cycles.
 * 
 * The algorithm works by initializing a distance matrix with the direct distances between vertices.
 * Then, it iteratively updates the matrix by considering each vertex as an intermediate point and
 * checks if a shorter path exists through that vertex. The time complexity of the algorithm is O(V^3),
 * where V is the number of vertices in the graph, and the space complexity is O(V^2).
 * 
 * Limitations:
 * 1. High time complexity: O(V^3), which may be impractical for very large graphs.
 * 2. High space complexity: O(V^2), requiring significant memory for large graphs.
 * 3. Cannot handle negative weight cycles: If such cycles exist, the algorithm cannot provide correct shortest paths.
 * 
 * Usage:
 * This implementation reads the number of vertices and edges of the graph from standard input.
 * The resulting shortest path distances between all pairs of vertices are printed to the standard output.
 * If a negative weight cycle exists, a message is printed instead of the distances.
 * 
 * Example input:
 * 4 4
 * 0 1 3
 * 1 3 4
 * 3 2 2
 * 2 0 1
 * 
 * Example output:
 * 0 3 7 7
 * 7 0 4 4
 * 3 6 0 6
 * 1 4 2 0
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

const int INF = std::numeric_limits<int>::max();

/**
 * @brief Displays the distance matrix.
 * 
 * This function prints the distance matrix. For unreachable vertices, it displays "INF".
 * 
 * @param graph The matrix representing the shortest path distances between all pairs of vertices.
 */
void display(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == INF) {
                std::cout << "INF ";
            } else {
                std::cout << graph[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Implements the Floyd-Warshall algorithm to find the shortest paths between all pairs of vertices.
 * 
 * This function updates the distance matrix `dist` with the shortest path distances by considering
 * each vertex as an intermediate point. If a shorter path through an intermediate vertex is found,
 * it updates the distance.
 * 
 * @param graph The input adjacency matrix representing direct distances between vertices.
 * @param dist The matrix where the shortest path distances between all pairs of vertices will be stored.
 * @return Returns `false` if a negative weight cycle is detected, otherwise returns `true`.
 */
bool floyd_warshall(const std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& dist) {
    int n = graph.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            return false; // Negative cycle detected
        }
    }
    return true;
}

/**
 * @brief Handles the input and invokes the Floyd-Warshall algorithm.
 * 
 * This function reads the number of vertices and edges from standard input, builds the adjacency matrix,
 * and then calls the `floyd` function to compute the shortest path between all pairs of vertices.
 * If a negative weight cycle is detected, it prints a message; otherwise, it prints the shortest path matrix.
 */
void test() {
    int N, M;
    std::cout << "Enter the number of vertices and edges: ";
    std::cin >> N >> M;
    
    // Initialize the graph with infinite distances
    std::vector<std::vector<int>> graph(N, std::vector<int>(N, INF));
    
    // Distance to self is zero
    for (int i = 0; i < N; i++) {
        graph[i][i] = 0;
    }

    // Input edges with their weights
    std::cout << "Enter the edges (from to length):\n";
    for (int i = 0; i < M; i++) {
        int from, to, length;
        std::cin >> from >> to >> length;
        graph[from][to] = length;
    }
    
    // The shortest distance matrix initialized with the graph's adjacency matrix
    std::vector<std::vector<int>> min_len = graph;
    
    // Apply the Floyd-Warshall algorithm
    if (floyd_warshall(graph, min_len)) {
        std::cout << "Shortest path matrix:\n";
        display(min_len); // Display the result matrix
    } else {
        std::cout << "Graph contains a negative weight cycle.\n";
    }
}

/**
 * @brief Main function that starts the program by invoking the test function.
 * 
 * This function serves as the entry point of the program, calling the `test` function
 * to perform the Floyd-Warshall algorithm on the given input graph.
 */
int main() {
    test(); // Run the test case
    return 0;
}
