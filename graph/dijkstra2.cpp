/**
 * @file
 * @brief Dijkstra's shortest path algorithm using std::set.
 * @details Computes shortest distances from a source vertex in a weighted
 *          directed graph with non-negative edge weights. Each set entry is a
 *          pair of (distance, vertex). When a shorter distance is found, the
 *          old entry is removed before the improved entry is inserted. The
 *          adjacency list represents directed edges; add both directions for
 *          an undirected graph.
 * @see https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
 */

#include <cassert>   // for assert
#include <cstddef>   // for std::size_t
#include <cstdint>   // for std::int64_t
#include <cstdlib>   // for std::abort
#include <iostream>  // for std::cout
#include <limits>    // for std::numeric_limits
#include <random>    // for deterministic randomized tests
#include <set>       // for std::set
#include <stdexcept> // for std::invalid_argument, std::out_of_range
#include <utility>   // for std::pair
#include <vector>    // for std::vector

/**
 * @namespace graph
 * @brief Graph algorithms.
 */
namespace graph {

/**
 * @namespace dijkstra_set
 * @brief Dijkstra's shortest path algorithm using a set.
 */
namespace dijkstra_set {

using weight_type = std::int64_t;
using adjacency_list =
    std::vector<std::vector<std::pair<std::size_t, weight_type>>>;

// INF represents an unreachable vertex. A finite shortest distance must be
// strictly smaller than this sentinel.
constexpr weight_type INF = std::numeric_limits<weight_type>::max();

/**
 * @brief Computes shortest distances from a source vertex.
 * @param adj Adjacency list; each edge is a (neighbor, non-negative weight)
 *            pair.
 * @param source Source vertex, indexed from 0.
 * @returns A vector of shortest distances. Unreachable vertices have value INF.
 * @throws std::out_of_range if the source or an edge's neighbor is invalid.
 * @throws std::invalid_argument if an edge has a negative weight.
 *
 * Time complexity: O((V + E) log V).
 * Space complexity: O(V + E), including the graph and auxiliary structures.
 * Edge weights and representable shortest distances must fit in weight_type;
 * the INF sentinel itself is reserved for unreachable vertices.
 */
std::vector<weight_type> dijkstra(const adjacency_list &adj,
                                  std::size_t source) {
    const std::size_t n = adj.size();
    if (source >= n) {
        throw std::out_of_range("Source vertex is out of range");
    }

    // Validate the complete graph before starting, avoiding invalid indexing
    // or silently applying Dijkstra to a graph with negative edge weights.
    for (const auto &edges : adj) {
        for (const auto &edge : edges) {
            if (edge.first >= n) {
                throw std::out_of_range("Edge neighbor is out of range");
            }
            if (edge.second < 0) {
                throw std::invalid_argument(
                    "Dijkstra's algorithm requires non-negative weights");
            }
        }
    }

    std::vector<weight_type> dist(n, INF);
    std::set<std::pair<weight_type, std::size_t>> pending;
    dist[source] = 0;
    pending.insert({0, source});

    while (!pending.empty()) {
        const auto current = *pending.begin();
        pending.erase(pending.begin());

        const weight_type current_dist = current.first;
        const std::size_t node = current.second;

        // Ignore an entry if a better distance is already known.
        if (current_dist != dist[node]) {
            continue;
        }

        for (const auto &edge : adj[node]) {
            const std::size_t neighbor = edge.first;
            const weight_type weight = edge.second;

            // Prevent signed integer overflow when adding path weights.
            if (current_dist > INF - weight) {
                continue;
            }

            const weight_type candidate = current_dist + weight;
            if (candidate < dist[neighbor]) {
                if (dist[neighbor] != INF) {
                    pending.erase({dist[neighbor], neighbor});
                }
                dist[neighbor] = candidate;
                pending.insert({candidate, neighbor});
            }
        }
    }

    return dist;
}

}  // namespace dijkstra_set
}  // namespace graph

/**
 * @brief Checks a test condition in both debug and release builds.
 * @param condition The condition expected to be true.
 * @returns void
 */
static void check(bool condition) {
    assert(condition);
    if (!condition) {
        std::abort();
    }
}

/**
 * @brief Calculates reference shortest paths using Bellman-Ford for tests.
 * @param adj Directed weighted adjacency list with non-negative weights.
 * @param source Source vertex.
 * @returns The shortest distances, using the same INF sentinel as Dijkstra.
 * @note Test helper for small graphs only; time complexity is O(VE).
 */
static std::vector<graph::dijkstra_set::weight_type> bellman_ford_reference(
    const graph::dijkstra_set::adjacency_list &adj, std::size_t source) {
    using graph::dijkstra_set::INF;
    using graph::dijkstra_set::weight_type;

    const std::size_t n = adj.size();
    std::vector<weight_type> dist(n, INF);
    dist[source] = 0;

    for (std::size_t iteration = 1; iteration < n; ++iteration) {
        bool changed = false;
        for (std::size_t node = 0; node < n; ++node) {
            if (dist[node] == INF) {
                continue;
            }
            for (const auto &edge : adj[node]) {
                const std::size_t neighbor = edge.first;
                const weight_type weight = edge.second;
                if (dist[node] <= INF - weight) {
                    const weight_type candidate = dist[node] + weight;
                    if (candidate < dist[neighbor]) {
                        dist[neighbor] = candidate;
                        changed = true;
                    }
                }
            }
        }
        if (!changed) {
            break;
        }
    }
    return dist;
}

/**
 * @brief Verifies Dijkstra's algorithm with deterministic and randomized tests.
 * @returns void
 */
static void tests() {
    using graph::dijkstra_set::INF;
    using graph::dijkstra_set::adjacency_list;
    using graph::dijkstra_set::dijkstra;
    using graph::dijkstra_set::weight_type;

    // Test 1: A shorter route is found through an intermediate vertex.
    adjacency_list graph1(5);
    graph1[0] = {{1, 4}, {2, 2}};
    graph1[1] = {{0, 4}, {2, 1}, {3, 5}};
    graph1[2] = {{0, 2}, {1, 1}, {3, 8}, {4, 10}};
    graph1[3] = {{1, 5}, {2, 8}, {4, 2}};
    graph1[4] = {{2, 10}, {3, 2}};
    check((dijkstra(graph1, 0) ==
            std::vector<weight_type>{0, 3, 2, 8, 10}));

    // Test 2: An unreachable vertex remains at INF.
    adjacency_list graph2(3);
    graph2[0] = {{1, 7}};
    graph2[1] = {{0, 7}};
    check((dijkstra(graph2, 0) == std::vector<weight_type>{0, 7, INF}));

    // Test 3: Zero-weight edges are supported.
    adjacency_list graph3(3);
    graph3[0] = {{1, 0}, {2, 5}};
    graph3[1] = {{0, 0}, {2, 2}};
    graph3[2] = {{0, 5}, {1, 2}};
    check((dijkstra(graph3, 0) == std::vector<weight_type>{0, 0, 2}));

    // Test 4: Directed edges and a source other than vertex 0.
    adjacency_list graph4(3);
    graph4[2] = {{0, 2}};
    graph4[0] = {{1, 3}};
    check((dijkstra(graph4, 2) == std::vector<weight_type>{2, 5, 0}));

    // Test 5: Parallel edges and a self-loop do not break relaxation.
    adjacency_list graph5(3);
    graph5[0] = {{0, 0}, {1, 20}, {1, 3}, {2, 4}};
    graph5[2] = {{1, 1}};
    check((dijkstra(graph5, 0) == std::vector<weight_type>{0, 3, 4}));

    // Test 6: A path whose sum would overflow is not accepted as finite.
    adjacency_list graph6(3);
    graph6[0] = {{1, INF - 2}};
    graph6[1] = {{2, 10}};
    check((dijkstra(graph6, 0) ==
            std::vector<weight_type>{0, INF - 2, INF}));

    // Test 7: Invalid sources, neighbors, and negative weights are rejected.
    bool caught = false;
    try {
        (void)dijkstra(adjacency_list(1), 1);
    } catch (const std::out_of_range &) {
        caught = true;
    }
    check(caught);

    caught = false;
    try {
        adjacency_list invalid_neighbor(1);
        invalid_neighbor[0] = {{1, 2}};
        (void)dijkstra(invalid_neighbor, 0);
    } catch (const std::out_of_range &) {
        caught = true;
    }
    check(caught);

    caught = false;
    try {
        adjacency_list negative_edge(2);
        negative_edge[0] = {{1, -1}};
        (void)dijkstra(negative_edge, 0);
    } catch (const std::invalid_argument &) {
        caught = true;
    }
    check(caught);

    // Test 8: Compare against Bellman-Ford on reproducible random small graphs.
    std::mt19937 generator(123456U);
    std::uniform_int_distribution<int> vertex_count(1, 8);
    std::uniform_int_distribution<int> edge_weight(0, 20);
    std::uniform_int_distribution<int> edge_chance(0, 3);

    for (int trial = 0; trial < 200; ++trial) {
        const std::size_t n =
            static_cast<std::size_t>(vertex_count(generator));
        adjacency_list random_graph(n);
        for (std::size_t from = 0; from < n; ++from) {
            for (std::size_t to = 0; to < n; ++to) {
                if (edge_chance(generator) == 0) {
                    random_graph[from].push_back(
                        {to, static_cast<weight_type>(edge_weight(generator))});
                }
            }
        }

        for (std::size_t source = 0; source < n; ++source) {
            check(dijkstra(random_graph, source) ==
                  bellman_ford_reference(random_graph, source));
        }
    }

    std::cout << "All Dijkstra using set tests passed!\n";
}

/**
 * @brief Main function.
 * @returns 0 on successful completion.
 */
int main() {
    tests();
    return 0;
}
