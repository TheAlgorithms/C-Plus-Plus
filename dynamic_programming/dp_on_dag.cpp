#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

/**
 * @brief Dynamic programming on a directed acyclic graph.
 *
 * Given a weighted DAG and a source vertex, this implementation computes the
 * shortest distance from the source to every other vertex. The algorithm first
 * performs a topological ordering using DFS and then relaxes edges in that
 * order.
 *
 * Time complexity: O(V + E)
 * Space complexity: O(V)
 */
namespace dynamic_programming {
namespace dp_on_dag {

constexpr std::int64_t kInfinity = std::numeric_limits<std::int64_t>::max();

using Edge = std::pair<std::size_t, std::int64_t>;
using Graph = std::vector<std::vector<Edge>>;

void depth_first_search(const Graph &graph, std::size_t vertex,
                        std::vector<bool> *visited,
                        std::vector<std::size_t> *order) {
    (*visited)[vertex] = true;

    for (const auto &[neighbor, weight] : graph[vertex]) {
        (void)weight;
        if (neighbor >= graph.size()) {
            throw std::out_of_range("Edge points to a vertex outside graph");
        }
        if (!(*visited)[neighbor]) {
            depth_first_search(graph, neighbor, visited, order);
        }
    }

    order->push_back(vertex);
}

std::vector<std::size_t> topological_sort(const Graph &graph) {
    std::vector<bool> visited(graph.size(), false);
    std::vector<std::size_t> order;
    order.reserve(graph.size());

    for (std::size_t vertex = 0; vertex < graph.size(); ++vertex) {
        if (!visited[vertex]) {
            depth_first_search(graph, vertex, &visited, &order);
        }
    }

    std::reverse(order.begin(), order.end());
    return order;
}

std::vector<std::int64_t> shortest_path(const Graph &graph,
                                        std::size_t source) {
    if (source >= graph.size()) {
        throw std::out_of_range("Source vertex is outside graph");
    }

    std::vector<std::int64_t> distance(graph.size(), kInfinity);
    distance[source] = 0;

    const auto order = topological_sort(graph);

    for (const auto vertex : order) {
        if (distance[vertex] == kInfinity) {
            continue;
        }

        for (const auto &[neighbor, weight] : graph[vertex]) {
            const auto candidate = distance[vertex] + weight;
            if (candidate < distance[neighbor]) {
                distance[neighbor] = candidate;
            }
        }
    }

    return distance;
}

}  // namespace dp_on_dag
}  // namespace dynamic_programming

static void test_shortest_path_from_source() {
    using dynamic_programming::dp_on_dag::Graph;
    using dynamic_programming::dp_on_dag::shortest_path;

    const Graph graph = {
        {{1, 5}, {2, 3}},  // 0
        {{3, 6}, {2, 2}},  // 1
        {{4, 4}, {5, 2}, {3, 7}},  // 2
        {{4, -1}, {5, 1}},  // 3
        {{5, -2}},  // 4
        {},  // 5
    };

    const auto distance = shortest_path(graph, 1);

    assert(distance[0] ==
           dynamic_programming::dp_on_dag::kInfinity);
    assert(distance[1] == 0);
    assert(distance[2] == 2);
    assert(distance[3] == 6);
    assert(distance[4] == 5);
    assert(distance[5] == 3);
}

static void test_invalid_source_throws() {
    using dynamic_programming::dp_on_dag::Graph;
    using dynamic_programming::dp_on_dag::shortest_path;

    bool exception_thrown = false;
    try {
        const Graph graph = {{{1, 4}}, {}};
        shortest_path(graph, 3);
    } catch (const std::out_of_range &) {
        exception_thrown = true;
    }

    assert(exception_thrown);
}

static void test_disconnected_vertices_remain_unreachable() {
    using dynamic_programming::dp_on_dag::Graph;
    using dynamic_programming::dp_on_dag::kInfinity;
    using dynamic_programming::dp_on_dag::shortest_path;

    const Graph graph = {
        {{1, 10}},
        {},
        {{3, 5}},
        {},
    };

    const auto distance = shortest_path(graph, 0);

    assert(distance[0] == 0);
    assert(distance[1] == 10);
    assert(distance[2] == kInfinity);
    assert(distance[3] == kInfinity);
}

int main() {
    test_shortest_path_from_source();
    test_invalid_source_throws();
    test_disconnected_vertices_remain_unreachable();

    std::cout << "All tests have successfully passed!\n";
    return 0;
}
