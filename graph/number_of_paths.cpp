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

/**
 * @namespace graph
 * @brief Graph algorithms
 */
namespace graph {

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
    int count_paths(const std::vector<std::vector<int>> &A, int u, int v, int n) {
        if (u == v) {
            return 1; // Base case: Reached the destination node
        }

        int path_count = 0; // Count of all paths from `u` to `v`

        for (int i = 0; i < n; i++) {
            if (A[u][i] == 1) { // Check if there is an edge from `u` to `i`
                path_count += count_paths(A, i, v, n); // Recursively explore paths from `i` to `v`
            }
        }

        return path_count;
    }

} // namespace graph

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // Test case 1: Simple directed graph with multiple paths
    std::vector<std::vector<int>> graph1 = {
        {0, 1, 0, 1, 0}, 
        {0, 0, 1, 0, 1}, 
        {0, 0, 0, 0, 1}, 
        {0, 0, 1, 0, 0}, 
        {0, 0, 0, 0, 0}  
    };
    int n1 = 5, u1 = 0, v1 = 4;
    assert(graph::count_paths(graph1, u1, v1, n1) == 3);  // There are 3 paths from node 0 to 4
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
