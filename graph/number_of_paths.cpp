/**
 * @file
 * @brief Algorithm to count paths between two nodes in a directed graph using DFS
 * @details
 * This algorithm implements Depth First Search (DFS) to count the number of 
 * possible paths between two nodes in a directed graph. It is represented using 
 * an adjacency matrix. The algorithm recursively traverses the graph to find 
 * all paths from the source node `u` to the destination node `v`.
 * 
 * @author [Aditya Borate](https://github.com/adi776borate)
 * @see https://en.wikipedia.org/wiki/Path_(graph_theory)
 */

#include <vector>   /// for std::vector
#include <iostream> /// for IO operations
#include <cassert>  /// for assert
#include <cstdint>  /// for fixed-size integer types (e.g., std::uint32_t)

/**
 * @namespace graph
 * @brief Graph algorithms
 */
namespace graph {

    /**
     * @brief Helper function to perform DFS and count the number of paths from node `u` to node `v`
     * @param A adjacency matrix representing the graph (1: edge exists, 0: no edge)
     * @param u the starting node
     * @param v the destination node
     * @param n the number of nodes in the graph
     * @param visited a vector to keep track of visited nodes in the current DFS path
     * @returns the number of paths from node `u` to node `v`
     */
    std::uint32_t count_paths_dfs(const std::vector<std::vector<std::uint32_t>>& A, 
                              std::uint32_t u, 
                              std::uint32_t v, 
                              std::uint32_t n, 
                              std::vector<bool>& visited) {
        if (u == v) {
            return 1;  // Base case: Reached the destination node
        }

        visited[u] = true;  // Mark the current node as visited
        std::uint32_t path_count = 0;  // Count of all paths from `u` to `v`

        for (std::uint32_t i = 0; i < n; i++) {
            if (A[u][i] == 1 && !visited[i]) {  // Check if there is an edge and the node is not visited
                path_count += count_paths_dfs(A, i, v, n, visited);  // Recursively explore paths from `i` to `v`
            }
        }

        visited[u] = false;  // Unmark the current node as visited (backtracking)
        return path_count;
    }


    /**
     * @brief Counts the number of paths from node `u` to node `v` in a directed graph
     * using Depth First Search (DFS)
     * 
     * @param A adjacency matrix representing the graph (1: edge exists, 0: no edge)
     * @param u the starting node
     * @param v the destination node
     * @param n the number of nodes in the graph
     * @returns the number of paths from node `u` to node `v`
     */
    std::uint32_t count_paths(const std::vector<std::vector<std::uint32_t>>& A, 
                          std::uint32_t u, 
                          std::uint32_t v, 
                          std::uint32_t n) {
        // Check for invalid nodes or empty graph
        if (u >= n || v >= n || A.empty() || A[0].empty()) {
            return 0;  // No valid paths if graph is empty or nodes are out of bounds
        }

        std::vector<bool> visited(n, false);  // Initialize a visited vector for tracking nodes
        return count_paths_dfs(A, u, v, n, visited);  // Start DFS
    }

} // namespace graph

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // Test case 1: Simple directed graph with multiple paths
    std::vector<std::vector<std::uint32_t>> graph1 = {
        {0, 1, 0, 1, 0}, 
        {0, 0, 1, 0, 1}, 
        {0, 0, 0, 0, 1}, 
        {0, 0, 1, 0, 0}, 
        {0, 0, 0, 0, 0}  
    };
    std::uint32_t n1 = 5, u1 = 0, v1 = 4;
    assert(graph::count_paths(graph1, u1, v1, n1) == 3);  // There are 3 paths from node 0 to 4

    // Test case 2: No possible path (disconnected graph)
    std::vector<std::vector<std::uint32_t>> graph2 = {
        {0, 1, 0, 0, 0}, 
        {0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 1}, 
        {0, 0, 1, 0, 0}, 
        {0, 0, 0, 0, 0}  
    };
    std::uint32_t n2 = 5, u2 = 0, v2 = 4;
    assert(graph::count_paths(graph2, u2, v2, n2) == 0);  // No path from node 0 to 4

    // Test case 3: Cyclic graph with multiple paths
    std::vector<std::vector<std::uint32_t>> graph3 = {
        {0, 1, 0, 0, 0}, 
        {0, 0, 1, 1, 0}, 
        {1, 0, 0, 0, 1}, 
        {0, 0, 1, 0, 1}, 
        {0, 0, 0, 0, 0}  
    };
    std::uint32_t n3 = 5, u3 = 0, v3 = 4;
    assert(graph::count_paths(graph3, u3, v3, n3) == 3);  // There are 3 paths from node 0 to 4

    // Test case 4: Single node graph (self-loop)
    std::vector<std::vector<std::uint32_t>> graph4 = {
        {0}
    };
    std::uint32_t n4 = 1, u4 = 0, v4 = 0;
    assert(graph::count_paths(graph4, u4, v4, n4) == 1);  // There is self-loop, so 1 path from node 0 to 0

    // Test case 5: Empty graph (no nodes, no paths)
    std::vector<std::vector<std::uint32_t>> graph5 = {{}};
    int n5 = 0, u5 = 0, v5 = 0;
    assert(graph::count_paths(graph5, u5, v5, n5) == 0);  // There are no paths in an empty graph

    // Test case 6: Invalid nodes (out of bounds)
    std::vector<std::vector<std::uint32_t>> graph6 = {
        {0, 1, 0}, 
        {0, 0, 1}, 
        {0, 0, 0}
    };
    int n6 = 3, u6 = 0, v6 = 5;  // Node `v` is out of bounds (n = 3, so valid indices are 0, 1, 2)
    assert(graph::count_paths(graph6, u6, v6, n6) == 0);  // Should return 0 because `v = 5` is invalid

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test(); // Run self-test implementations
    return 0;
}
