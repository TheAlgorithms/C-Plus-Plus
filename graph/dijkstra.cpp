/**
 * @file
 * @brief Dijkstra's Shortest Path Algorithm
 * https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
 *
 * @details
 * Finds the shortest distance from a source vertex to a target vertex
 * in a weighted directed graph with non-negative weights.
 */

#include <cassert>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

constexpr long long INF = std::numeric_limits<long long>::max();

namespace graph {

/**
 * @brief Adds a directed weighted edge to the graph
 *
 * @param adj adjacency list
 * @param u source vertex (1-based)
 * @param v destination vertex (1-based)
 * @param w weight of edge
 */
void addEdge(std::vector<std::vector<std::pair<int, int>>>& adj,
             int u, int v, int w) {
    adj[u - 1].emplace_back(v - 1, w);
}

/**
 * @brief Runs Dijkstra's algorithm
 *
 * @param adj adjacency list
 * @param source source vertex (0-based)
 * @param target target vertex (0-based)
 * @return shortest distance or -1 if unreachable
 */
long long dijkstra(const std::vector<std::vector<std::pair<int, int>>>& adj,
                   int source, int target) {
    int n = adj.size();
    std::vector<long long> dist(n, INF);

    // min-heap: {distance, vertex}
    std::priority_queue<
        std::pair<long long, int>,
        std::vector<std::pair<long long, int>>,
        std::greater<>
    > pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
    long long currentDist = pq.top().first;
    int u = pq.top().second;
    pq.pop();

    if (currentDist > dist[u]) {
        continue;
    }

    for (const auto& edge : adj[u]) {
        int v = edge.first;
        int weight = edge.second;

        if (currentDist + weight < dist[v]) {
            dist[v] = currentDist + weight;
            pq.push({dist[v], v});
        }
    }
}


    return (dist[target] == INF) ? -1 : dist[target];
}

}  // namespace graph

/** Unit tests */
void tests() {
    std::vector<std::vector<std::pair<int, int>>> adj1(4);
    graph::addEdge(adj1, 1, 2, 1);
    graph::addEdge(adj1, 4, 1, 2);
    graph::addEdge(adj1, 2, 3, 2);
    graph::addEdge(adj1, 1, 3, 5);

    assert(graph::dijkstra(adj1, 0, 2) == 3);
    assert(graph::dijkstra(adj1, 3, 2) == 5);

    std::vector<std::vector<std::pair<int, int>>> adj2(5);
    graph::addEdge(adj2, 1, 2, 4);
    graph::addEdge(adj2, 1, 3, 2);
    graph::addEdge(adj2, 2, 3, 2);
    graph::addEdge(adj2, 3, 2, 1);
    graph::addEdge(adj2, 2, 4, 2);
    graph::addEdge(adj2, 3, 5, 4);
    graph::addEdge(adj2, 5, 4, 1);
    graph::addEdge(adj2, 2, 5, 3);
    graph::addEdge(adj2, 3, 4, 4);

    assert(graph::dijkstra(adj2, 0, 4) == 6);

    std::cout << "All tests passed successfully.\n";
}

int main() {
    tests();

    int vertices, edges;
    std::cin >> vertices >> edges;

    std::vector<std::vector<std::pair<int, int>>> adj(vertices);

    while (edges--) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph::addEdge(adj, u, v, w);
    }

    int s, t;
    std::cin >> s >> t;

    long long dist = graph::dijkstra(adj, s - 1, t - 1);
    if (dist == -1) {
        std::cout << "Target not reachable from source\n";
    } else {
        std::cout << "Shortest Path Distance: " << dist << "\n";
    }
}
