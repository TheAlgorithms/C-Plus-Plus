/**
 * @file floyd_warshall.cpp
 * @brief Implementation of the Floyd-Warshall algorithm in C++
 * 
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
 * This implementation reads the number of vertices and the adjacency matrix of the graph from standard input.
 * The resulting shortest path distances between all pairs of vertices are printed to the standard output.
 * 
 * Example input:
 * 4
 * 0 3 INF 5
 * 2 0 INF 4
 * INF 1 0 INF
 * INF INF 2 0
 * 
 * Example output:
 * 0 3 7 5
 * 2 0 6 4
 * 3 1 0 5
 * 5 3 2 0
 */

#include <iostream>
#include <vector>
#include <algorithm>

const int inf = 1e8;

void display(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == inf) {
                std::cout << "INF ";
            } else {
                std::cout << graph[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

void floyd(const std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& dist) {
    int n = graph.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < inf && dist[k][j] < inf) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main() {
    int N, M;
    std::cin >> N >> M; // N - number of vertices; M - number of edges.
    std::vector<std::vector<int>> graph(N, std::vector<int>(N, inf));
    for (int i = 0; i < N; i++) {
        graph[i][i] = 0;
    }
    for (int i = 0; i < M; i++) {
        int from, to, length;
        std::cin >> from >> to >> length;
        graph[from][to] = length;
    }
    
    // min_len[a][b] : the shortest distance from a to b.  
    std::vector<std::vector<int>> min_len = graph;
    
    floyd(graph, min_len);
    display(min_len);

    return 0;
}
