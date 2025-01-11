/******************************************************************************
 * @file
 * @brief Depth First Search (DFS) Algorithm Implementation
 * @details
 * Depth First Search (DFS) is an algorithm used for traversing or searching
 * tree or graph data structures. The algorithm starts at a given starting node
 * and explores as far as possible along each branch before backtracking.
 *
 * This implementation uses an adjacency list for scalability and flexibility.
 *
 * ### Complexities
 * - Time complexity: O(V + E) where V is the number of vertices and E is the number of edges.
 * - Space complexity: O(V) to store the visited nodes.
 *
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept> // For error handling

/******************************************************************************
 * @brief Implements Depth First Search (DFS) using adjacency list
 * @param graph adjacency list representation of the graph
 * @param start starting node for the DFS
 * @param visited set to track visited nodes
 * @param result vector to store the traversal order
 * @throws std::invalid_argument if the start node is not in the graph
 ******************************************************************************/
void dfs(const std::unordered_map<int, std::vector<int>> &graph, int start, std::unordered_set<int> &visited, std::vector<int> &result) {
    if (graph.find(start) == graph.end()) {
        throw std::invalid_argument("Start node does not exist in the graph.");
    }

    visited.insert(start);  // Mark the current node as visited
    result.push_back(start);

    for (int neighbor : graph.at(start)) {  // Visit all neighbors
        if (visited.find(neighbor) == visited.end()) {
            dfs(graph, neighbor, visited, result);
        }
    }
}

/*******************************************************************************
 * @brief Test function to validate the DFS algorithm
 *******************************************************************************/
void test() {
    try {
        // Test Case 1: Basic graph with a single path
        // Graph:
        // 0 -> 1, 2
        // 1 -> 3, 4
        // 2 -> empty
        // 3 -> empty
        // 4 -> empty

        std::unordered_map<int, std::vector<int>> graph1 = {
            {0, {1, 2}},
            {1, {3, 4}},
            {2, {}},
            {3, {}},
            {4, {}}
        };

        std::unordered_set<int> visited1;
        std::vector<int> result1;

        dfs(graph1, 0, visited1, result1);

        std::cout << "Test Case 1 - DFS traversal: ";
        for (int node : result1) {
            std::cout << node << " ";
        }
        std::cout << std::endl;

        // Test Case 2: A disconnected graph
        // Graph:
        // 0 -> 1
        // 1 -> 2
        // 3 -> 4

        std::unordered_map<int, std::vector<int>> graph2 = {
            {0, {1}},
            {1, {2}},
            {2, {}},
            {3, {4}},
            {4, {}}
        };

        std::unordered_set<int> visited2;
        std::vector<int> result2;

        dfs(graph2, 0, visited2, result2);

        std::cout << "Test Case 2 - DFS traversal from node 0: ";
        for (int node : result2) {
            std::cout << node << " ";
        }
        std::cout << std::endl;

        std::unordered_set<int> visited3;
        std::vector<int> result3;

        dfs(graph2, 3, visited3, result3);

        std::cout << "Test Case 2 - DFS traversal from node 3: ";
        for (int node : result3) {
            std::cout << node << " ";
        }
        std::cout << std::endl;

        // Test Case 3: A cyclic graph
        // Graph:
        // 0 -> 1
        // 1 -> 2
        // 2 -> 0

        std::unordered_map<int, std::vector<int>> graph3 = {
            {0, {1}},
            {1, {2}},
            {2, {0}},
            {3, {}},
            {4, {}}
        };

        std::unordered_set<int> visited4;
        std::vector<int> result4;

        dfs(graph3, 0, visited4, result4);

        std::cout << "Test Case 3 - DFS traversal: ";
        for (int node : result4) {
            std::cout << node << " ";
        }
        std::cout << std::endl;

        // Test Case 4: Invalid start node
        try {
            std::unordered_set<int> visited5;
            std::vector<int> result5;

            dfs(graph3, 10, visited5, result5); // Node 10 does not exist
        } catch (const std::invalid_argument &e) {
            std::cout << "Test Case 4 - Exception caught: " << e.what() << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
}

/*******************************************************************************
 * @brief Main function
 * @returns 0 on exit
 *******************************************************************************/
int main() {
    test();  // run the test function
    return 0;
}
