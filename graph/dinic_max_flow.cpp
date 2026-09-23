/**
 * @file dinic_max_flow.cpp
 * @brief Dinic's algorithm for finding maximum flow in a directed graph.
 *
 * Dinic's algorithm builds a level graph using BFS and sends blocking flow
 * using DFS. Its worst-case complexity is O(V^2 E).
 */

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <queue>
#include <vector>

/**
 * @brief Computes maximum flow using Dinic's algorithm.
 */
class Dinic {
    struct Edge {
        int to;
        int reverse_edge;
        std::int64_t capacity;
    };

    std::vector<std::vector<Edge>> graph;
    std::vector<int> level;
    std::vector<int> next_edge;

    bool build_level_graph(int source, int sink) {
        std::fill(level.begin(), level.end(), -1);

        std::queue<int> vertices;
        vertices.push(source);
        level[source] = 0;

        while (!vertices.empty()) {
            const int current = vertices.front();
            vertices.pop();

            for (const Edge& edge : graph[current]) {
                if (edge.capacity > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[current] + 1;
                    vertices.push(edge.to);
                }
            }
        }

        return level[sink] != -1;
    }

    std::int64_t send_flow(int current, int sink, std::int64_t flow) {
        if (current == sink) {
            return flow;
        }

        for (int& index = next_edge[current];
             index < static_cast<int>(graph[current].size()); ++index) {
            Edge& edge = graph[current][index];

            if (edge.capacity <= 0 ||
                level[edge.to] != level[current] + 1) {
                continue;
            }

            const std::int64_t pushed_flow =
                send_flow(edge.to, sink, std::min(flow, edge.capacity));

            if (pushed_flow == 0) {
                continue;
            }

            edge.capacity -= pushed_flow;
            graph[edge.to][edge.reverse_edge].capacity += pushed_flow;
            return pushed_flow;
        }

        return 0;
    }

public:
    explicit Dinic(int node_count)
        : graph(node_count), level(node_count), next_edge(node_count) {
        assert(node_count > 0);
    }

    /**
     * @brief Adds a directed edge with the given capacity.
     */
    void add_edge(int from, int to, std::int64_t capacity) {
        assert(from >= 0 && from < static_cast<int>(graph.size()));
        assert(to >= 0 && to < static_cast<int>(graph.size()));
        assert(from != to);
        assert(capacity >= 0);

        const int reverse_index = static_cast<int>(graph[to].size());

        graph[from].push_back({to, reverse_index, capacity});
        graph[to].push_back(
            {from, static_cast<int>(graph[from].size()) - 1, 0});
    }

    /**
     * @brief Returns the maximum flow from source to sink.
     */
    std::int64_t max_flow(int source, int sink) {
        assert(source >= 0 && source < static_cast<int>(graph.size()));
        assert(sink >= 0 && sink < static_cast<int>(graph.size()));

        if (source == sink) {
            return 0;
        }

        std::int64_t total_flow = 0;
        const std::int64_t infinity =
            std::numeric_limits<std::int64_t>::max() / 4;

        while (build_level_graph(source, sink)) {
            std::fill(next_edge.begin(), next_edge.end(), 0);

            while (const std::int64_t pushed_flow =
                       send_flow(source, sink, infinity)) {
                total_flow += pushed_flow;
            }
        }

        return total_flow;
    }
};

bool test_classic_network() {
    Dinic network(6);

    network.add_edge(0, 1, 16);
    network.add_edge(0, 2, 13);
    network.add_edge(1, 2, 10);
    network.add_edge(2, 1, 4);
    network.add_edge(1, 3, 12);
    network.add_edge(3, 2, 9);
    network.add_edge(2, 4, 14);
    network.add_edge(4, 3, 7);
    network.add_edge(3, 5, 20);
    network.add_edge(4, 5, 4);

    return network.max_flow(0, 5) == 23;
}

bool test_parallel_edges() {
    Dinic network(4);

    network.add_edge(0, 1, 5);
    network.add_edge(0, 1, 7);
    network.add_edge(1, 2, 10);
    network.add_edge(2, 3, 10);
    network.add_edge(1, 3, 2);

    return network.max_flow(0, 3) == 12;
}

bool test_unreachable_sink() {
    Dinic network(3);
    network.add_edge(0, 1, 5);

    return network.max_flow(0, 2) == 0;
}

int main() {
    const bool all_tests_passed = test_classic_network() &&
                                  test_parallel_edges() &&
                                  test_unreachable_sink();

    assert(all_tests_passed);
    return all_tests_passed ? 0 : 1;
}