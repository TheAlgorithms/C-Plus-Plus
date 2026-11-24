/**
 * @file
 * @brief Implementation of
 * [Maximum Weight Independent Set on a Tree](https://en.wikipedia.org/wiki/Independent_set_(graph_theory))
 * using Tree Dynamic Programming.
 * @details
 * Given an undirected tree with vertex weights, finds the maximum total weight
 * of a subset of vertices such that no two selected vertices share an edge.
 * Runs in O(V) time and O(V) space using iterative post-order traversal.
 */

#include <algorithm>  /// for std::max
#include <cassert>    /// for assert
#include <cstddef>    /// for std::size_t
#include <cstdint>    /// for std::int64_t
#include <iostream>   /// for std::cout
#include <stdexcept>  /// for std::invalid_argument
#include <utility>    /// for std::pair
#include <vector>     /// for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic programming algorithms
 */
namespace dynamic_programming {

/**
 * @namespace tree_dp
 * @brief Tree dynamic programming algorithms
 */
namespace tree_dp {

/**
 * @brief Compute the maximum weight of an independent set in a tree.
 * @param weights vertex weights of length n (n >= 1)
 * @param edges undirected tree edges as 0-indexed (u, v) pairs (must have n - 1 edges)
 * @return maximum weight sum of an independent set
 * @throws std::invalid_argument if the input is not a valid tree
 */
std::int64_t max_weight_independent_set(
    const std::vector<std::int64_t>& weights,
    const std::vector<std::pair<std::size_t, std::size_t>>& edges) {
    const std::size_t n = weights.size();
    if (n == 0 || edges.size() + 1 != n) {
        throw std::invalid_argument("a tree with n >= 1 vertices must have n - 1 edges");
    }

    std::vector<std::vector<std::size_t>> adj(n);
    for (const auto& [u, v] : edges) {
        if (u >= n || v >= n || u == v) {
            throw std::invalid_argument("invalid edge endpoint or self-loop");
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Build an iterative topological order from root 0 to avoid recursion
    // stack overflow on deep path-like trees.
    std::vector<std::size_t> parent(n, n);
    std::vector<std::size_t> order;
    order.reserve(n);
    std::vector<bool> visited(n, false);

    std::vector<std::size_t> stack = {0};
    visited[0] = true;
    while (!stack.empty()) {
        const std::size_t u = stack.back();
        stack.pop_back();
        order.push_back(u);
        for (const std::size_t v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                stack.push_back(v);
            }
        }
    }

    if (order.size() != n) {
        throw std::invalid_argument("input graph is disconnected");
    }

    std::vector<std::int64_t> dp_exclude(n, 0);
    std::vector<std::int64_t> dp_include(weights);

    for (std::size_t idx = n; idx-- > 0;) {
        const std::size_t u = order[idx];
        for (const std::size_t v : adj[u]) {
            if (v == parent[u]) {
                continue;
            }
            dp_include[u] += dp_exclude[v];
            dp_exclude[u] += std::max(dp_include[v], dp_exclude[v]);
        }
    }

    return std::max(dp_include[0], dp_exclude[0]);
}

}  // namespace tree_dp
}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    using dynamic_programming::tree_dp::max_weight_independent_set;

    // Single-node tree
    assert(max_weight_independent_set({42}, {}) == 42);

    // Path graph: 0(3) - 1(2) - 2(1) - 3(10) -> pick {0, 3} = 13
    assert(max_weight_independent_set({3, 2, 1, 10}, {{0, 1}, {1, 2}, {2, 3}}) == 13);

    // Star graph: center 0(10), leaves 1..4(3 each) -> pick leaves = 12
    assert(max_weight_independent_set({10, 3, 3, 3, 3},
                                      {{0, 1}, {0, 2}, {0, 3}, {0, 4}}) == 12);

    // 7-node weighted tree
    const std::vector<std::int64_t> weights = {1, 5, 3, 2, 4, 6, 2};
    const std::vector<std::pair<std::size_t, std::size_t>> edges = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}};
    // Optimal set: {0, 3, 4, 5, 6} -> 1 + 2 + 4 + 6 + 2 = 15
    assert(max_weight_independent_set(weights, edges) == 15);

    // Disconnected graph should throw
    bool threw_disconnected = false;
    try {
        (void)max_weight_independent_set({1, 2, 3}, {{0, 1}, {0, 1}});
    } catch (const std::invalid_argument&) {
        threw_disconnected = true;
    }
    assert(threw_disconnected);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
