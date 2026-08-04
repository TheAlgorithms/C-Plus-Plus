/**
 * @file
 * @brief [Graph Bellman-Ford Shortest Path Algorithm]
 * (https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm)
 *
 * @author [Het Prajapati](http://github.com/DeadJoker24)
 * @details
 * Bellman-Ford algorithm computes the shortest distance from a source
 * vertex to every other vertex in a weighted graph.
 *
 * Unlike Dijkstra's algorithm, Bellman-Ford can handle graphs
 * containing negative edge weights.
 *
 * The algorithm repeatedly relaxes all edges exactly (V-1) times,
 * where V is the number of vertices.
 *
 * A final pass over all edges determines whether a negative weight
 * cycle exists.
 */
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

constexpr int64_t INF = std::numeric_limits<int64_t>::max();

/**
 * @namespace graph
 * @brief Graph Algorithms
 */
namespace graph {
/**
 * @brief Edge list representation: each edge is (u, v, weight)
 */
using Edge = std::tuple<int, int, int64_t>;

/**
 * @brief Adds a directed edge to the edge list
 * @param edges the edge list to append to
 * @param u source vertex
 * @param v destination vertex
 * @param weight edge weight (can be negative)
 */
void addEdge(std::vector<Edge> &edges, int u, int v, int64_t weight) {
    edges.emplace_back(u, v, weight);
}

/**
 * @brief Runs Bellman-Ford from a source vertex
 *
 * Time Complexity : O(V * E)
 * Space Complexity : O(V)
 *
 * @param V number of vertices (labeled 0..V-1)
 * @param edges list of directed edges (u, v, weight)
 * @param source the source vertex
 *
 * @returns pair of (distance vector, bool indicating whether a
 *          negative-weight cycle reachable from source exists)
 */
std::pair<std::vector<int64_t>, bool> bellmanFord(
    int V, const std::vector<Edge> &edges, int source) {
    std::vector<int64_t> dist(V, INF);
    dist[source] = 0;

    /// Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        bool updated = false;
        for (const auto &[u, v, weight] : edges) {
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                updated = true;
            }
        }
        // Early exit if no updates happened this pass
        if (!updated) {
            break;
        }
    }

    /// Detect negative weight cycle
    bool hasNegativeCycle = false;
    for (const auto &[u, v, weight] : edges) {
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            hasNegativeCycle = true;
            break;
        }
    }

    return std::make_pair(dist, hasNegativeCycle);
}
}  // namespace graph

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    // Test 1: Simple graph, no negative cycle
    {
        std::cout << "Initiating Test 1..." << std::endl;
        int V = 5;
        std::vector<graph::Edge> edges;
        graph::addEdge(edges, 0, 1, -1);
        graph::addEdge(edges, 0, 2, 4);
        graph::addEdge(edges, 1, 2, 3);
        graph::addEdge(edges, 1, 3, 2);
        graph::addEdge(edges, 1, 4, 2);
        graph::addEdge(edges, 3, 2, 5);
        graph::addEdge(edges, 3, 1, 1);
        graph::addEdge(edges, 4, 3, -3);

        auto [dist, hasNegCycle] = graph::bellmanFord(V, edges, 0);

        assert(!hasNegCycle);
        assert(dist[0] == 0);
        assert(dist[1] == -1);
        assert(dist[2] == 2);
        assert(dist[3] == -2);
        assert(dist[4] == 1);
        std::cout << "Test 1 Passed..." << std::endl;
    }

    // Test 2: Graph with a negative-weight cycle
    {
        std::cout << "Initiating Test 2..." << std::endl;
        int V = 3;
        std::vector<graph::Edge> edges;
        graph::addEdge(edges, 0, 1, 1);
        graph::addEdge(edges, 1, 2, -1);
        graph::addEdge(edges, 2, 0, -1);

        auto [dist, hasNegCycle] = graph::bellmanFord(V, edges, 0);

        assert(hasNegCycle);
        std::cout << "Test 2 Passed..." << std::endl;
    }

    // Test 3: Unreachable vertex stays at INF
    {
        std::cout << "Initiating Test 3..." << std::endl;
        int V = 4;
        std::vector<graph::Edge> edges;
        graph::addEdge(edges, 0, 1, 5);
        graph::addEdge(edges, 1, 2, 3);
        // vertex 3 is unreachable from 0

        auto [dist, hasNegCycle] = graph::bellmanFord(V, edges, 0);

        assert(!hasNegCycle);
        assert(dist[3] == INF);
        std::cout << "Test 3 Passed..." << std::endl;
    }

    // Test 4: Single vertex graph
    {
        std::cout << "Initiating Test 4..." << std::endl;
        int V = 1;
        std::vector<graph::Edge> edges;

        auto [dist, hasNegCycle] = graph::bellmanFord(V, edges, 0);

        assert(!hasNegCycle);
        assert(dist[0] == 0);
        std::cout << "Test 4 Passed..." << std::endl;
    }

    std::cout << "All Tests Passed..." << std::endl << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}