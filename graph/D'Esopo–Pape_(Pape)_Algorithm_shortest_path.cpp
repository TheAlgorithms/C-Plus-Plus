/**
 * @file
 * @brief D'Esopo–Pape (Pape) Algorithm for Single-Source Shortest Paths
 *
 * @details
 * Computes shortest path distances from a source in a graph with
 * non-negative edge weights. Often performs very well in practice on sparse
 * graphs. Works for directed or undirected graphs (pass edges accordingly).
 *
 * - Typical complexity: close to O(E) on many inputs (amortized).
 * - Worst-case complexity: may degrade (can be exponential on contrived graphs).
 * - Space: O(V + E) for adjacency + O(V) for bookkeeping.
 *
 * References:
 *  - Original papers and common descriptions of the Pape algorithm
 *  - Compare with Dijkstra (binary heap) and SPFA variants
 */

#include <cassert>
#include <deque>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

namespace graph {

/**
 * @brief Adjacency list type: for each vertex, list of (neighbor, weight).
 */
using Adj = std::vector<std::vector<std::pair<int, int>>>;

/**
 * @brief Build adjacency list from an edge list.
 * @param v number of vertices
 * @param edges edges as {u, v, w}
 * @param undirected if true, inserts both (u->v) and (v->u)
 * @return adjacency list
 */
Adj make_adj(int v, const std::vector<std::vector<int>>& edges, bool undirected) {
    Adj g(v);
    g.reserve(v);
    for (const auto& e : edges) {
        int a = e[0], b = e[1], w = e[2];
        g[a].push_back({b, w});
        if (undirected) g[b].push_back({a, w});
    }
    return g;
}

/**
 * @brief D'Esopo–Pape SSSP using a deque.
 *
 * @param g adjacency list
 * @param src source vertex (0-based)
 * @return dist vector where dist[i] is the shortest distance from src to i
 *
 * @note Assumes all weights are non-negative.
 */
std::vector<int> pape_shortest_paths(const Adj& g, int src) {
    const int n = static_cast<int>(g.size());
    const int INF = std::numeric_limits<int>::max();

    std::vector<int> dist(n, INF);
    std::vector<char> in_queue(n, 0);  // 0: not in deque, 1: in deque
    std::vector<char> seen(n, 0);      // whether vertex has ever been enqueued

    std::deque<int> dq;
    dist[src] = 0;
    dq.push_back(src);
    in_queue[src] = 1;
    seen[src] = 1;

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        in_queue[u] = 0;

        for (const auto& [v, w] : g[u]) {
            if (dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;

                if (!in_queue[v]) {
                    in_queue[v] = 1;
                    if (seen[v]) {
                        // If we've seen v before, prioritize it
                        dq.push_front(v);
                    } else {
                        // First time seen -> push to back
                        dq.push_back(v);
                        seen[v] = 1;
                    }
                }
            }
        }
    }
    return dist;
}

}  // namespace graph

/* -------------------------- Unit Tests & Demo -------------------------- */

static void test_examples() {
    using graph::make_adj;
    using graph::pape_shortest_paths;

    // Example 1
    {
        int v = 5, src = 0;
        std::vector<std::vector<int>> edges = {
            {0, 1, 5}, {1, 2, 1}, {1, 3, 2}, {2, 4, 1}, {4, 3, 1}
        };
        auto g = make_adj(v, edges, /*undirected=*/true);
        auto dist = pape_shortest_paths(g, src);
        std::vector<int> expected = {0, 5, 6, 7, 7};
        assert(dist == expected);
    }

    // Example 2
    {
        int v = 5, src = 0;
        std::vector<std::vector<int>> edges = {
            {0, 1, 4}, {0, 2, 8}, {1, 4, 6}, {2, 3, 2}, {3, 4, 10}
        };
        auto g = make_adj(v, edges, /*undirected=*/true);
        auto dist = graph::pape_shortest_paths(g, src);
        std::vector<int> expected = {0, 4, 8, 10, 10};
        assert(dist == expected);
    }
}

int main() {
    test_examples();

    // Print one example to STDOUT (matching the article's output style)
    int v = 5, src = 0;
    std::vector<std::vector<int>> edges = {
        {0, 1, 5}, {1, 2, 1}, {1, 3, 2}, {2, 4, 1}, {4, 3, 1}
    };
    auto g = graph::make_adj(v, edges, /*undirected=*/true);
    auto dist = graph::pape_shortest_paths(g, src);

    for (int i = 0; i < v; ++i) {
        std::cout << dist[i] << (i + 1 == v ? '\n' : ' ');
    }
    return 0;
}
