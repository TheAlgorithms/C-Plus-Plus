/**
 * @author [Jason Nardoni](https://github.com/JNardoni)
 * @file
 *
 * @brief
 * [Borůvkas Algorithm](https://en.wikipedia.org/wiki/Borůvka's_algorithm) to
 *find the Minimum Spanning Tree
 *
 *
 * @details
 * Boruvka's algorithm is a greepy algorithm to find the MST by starting with
 *small trees, and combining them to build bigger ones.
 *	1. Creates a group for every vertex.
 *	2. looks through each edge of every vertex for the smallest weight. Keeps
 *track of the smallest edge for each of the current groups.
 *  3. Combine each group with the group it shares its smallest edge, adding the
 *smallest edge to the MST.
 *  4. Repeat step 2-3 until all vertices are combined into a single group.
 *
 * It assumes that the graph is connected. Non-connected edges can be
 *represented using 0 or INT_MAX
 *
 */

#include <cassert>   /// for assert
#include <climits>   /// for INT_MAX
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace greedy_algorithms
 * @brief Greedy Algorithms
 */
namespace greedy_algorithms {
/**
 * @namespace boruvkas_minimum_spanning_tree
 * @brief Functions for the [Borůvkas
 * Algorithm](https://en.wikipedia.org/wiki/Borůvka's_algorithm) implementation
 */
namespace boruvkas_minimum_spanning_tree {
/**
 * @brief Recursively returns the vertex's parent at the root of the tree
 * @param parent the array that will be checked
 * @param v vertex to find parent of
 * @returns the parent of the vertex
 */
int findParent(std::vector<std::pair<int, int>> parent, const int v) {
    if (parent[v].first != v) {
        parent[v].first = findParent(parent, parent[v].first);
    }

    return parent[v].first;
}

/**
 * @brief the implementation of boruvka's algorithm
 * @param adj a graph adjancency matrix stored as 2d vectors.
 * @returns the MST as 2d vectors
 */
std::vector<std::vector<int>> boruvkas(std::vector<std::vector<int>> adj) {
    size_t size = adj.size();
    size_t total_groups = size;

    if (size <= 1) {
        return adj;
    }

    // Stores the current Minimum Spanning Tree. As groups are combined, they
    // are added to the MST
    std::vector<std::vector<int>> MST(size, std::vector<int>(size, INT_MAX));
    for (int i = 0; i < size; i++) {
        MST[i][i] = 0;
    }

    // Step 1: Create a group for each vertex

    // Stores the parent of the vertex and its current depth, both initialized
    // to 0
    std::vector<std::pair<int, int>> parent(size, std::make_pair(0, 0));

    for (int i = 0; i < size; i++) {
        parent[i].first =
            i;  // Sets parent of each vertex to itself, depth remains 0
    }

    // Repeat until all are in a single group
    while (total_groups > 1) {
        std::vector<std::pair<int, int>> smallest_edge(
            size, std::make_pair(-1, -1));  // Pairing: start node, end node

        // Step 2: Look throught each vertex for its smallest edge, only using
        // the right half of the adj matrix
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (adj[i][j] == INT_MAX || adj[i][j] == 0) {  // No connection
                    continue;
                }

                // Finds the parents of the start and end points to make sure
                // they arent in the same group
                int parentA = findParent(parent, i);
                int parentB = findParent(parent, j);

                if (parentA != parentB) {
                    // Grabs the start and end points for the first groups
                    // current smallest edge
                    int start = smallest_edge[parentA].first;
                    int end = smallest_edge[parentA].second;

                    // If there is no current smallest edge, or the new edge is
                    // smaller, records the new smallest
                    if (start == -1 || adj[i][j] < adj[start][end]) {
                        smallest_edge[parentA].first = i;
                        smallest_edge[parentA].second = j;
                    }

                    // Does the same for the second group
                    start = smallest_edge[parentB].first;
                    end = smallest_edge[parentB].second;

                    if (start == -1 || adj[j][i] < adj[start][end]) {
                        smallest_edge[parentB].first = j;
                        smallest_edge[parentB].second = i;
                    }
                }
            }
        }

        // Step 3: Combine the groups based off their smallest edge

        for (int i = 0; i < size; i++) {
            // Makes sure the smallest edge exists
            if (smallest_edge[i].first != -1) {
                // Start and end points for the groups smallest edge
                int start = smallest_edge[i].first;
                int end = smallest_edge[i].second;

                // Parents of the two groups - A is always itself
                int parentA = i;
                int parentB = findParent(parent, end);

                // Makes sure the two nodes dont share the same parent. Would
                // happen if the two groups have been
                // merged previously through a common shortest edge
                if (parentA == parentB) {
                    continue;
                }

                // Tries to balance the trees as much as possible as they are
                // merged. The parent of the shallower
                // tree will be pointed to the parent of the deeper tree.
                if (parent[parentA].second < parent[parentB].second) {
                    parent[parentB].first = parentA;  // New parent
                    parent[parentB].second++;         // Increase depth
                } else {
                    parent[parentA].first = parentB;
                    parent[parentA].second++;
                }
                // Add the connection to the MST, using both halves of the adj
                // matrix
                MST[start][end] = adj[start][end];
                MST[end][start] = adj[end][start];
                total_groups--;  // one fewer group
            }
        }
    }
    return MST;
}

/**
 * @brief counts the sum of edges in the given tree
 * @param adj 2D vector adjacency matrix
 * @returns the int size of the tree
 */
int test_findGraphSum(std::vector<std::vector<int>> adj) {
    size_t size = adj.size();
    int sum = 0;

    // Moves through one side of the adj matrix, counting the sums of each edge
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (adj[i][j] < INT_MAX) {
                sum += adj[i][j];
            }
        }
    }
    return sum;
}
}  // namespace boruvkas_minimum_spanning_tree
}  // namespace greedy_algorithms

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    std::cout << "Starting tests...\n\n";
    std::vector<std::vector<int>> graph = {
        {0, 5, INT_MAX, 3, INT_MAX}, {5, 0, 2, INT_MAX, 5},
        {INT_MAX, 2, 0, INT_MAX, 3}, {3, INT_MAX, INT_MAX, 0, INT_MAX},
        {INT_MAX, 5, 3, INT_MAX, 0},
    };
    std::vector<std::vector<int>> MST =
        greedy_algorithms::boruvkas_minimum_spanning_tree::boruvkas(graph);
    assert(greedy_algorithms::boruvkas_minimum_spanning_tree::test_findGraphSum(
               MST) == 13);
    std::cout << "1st test passed!" << std::endl;

    graph = {{0, 2, 0, 6, 0},
             {2, 0, 3, 8, 5},
             {0, 3, 0, 0, 7},
             {6, 8, 0, 0, 9},
             {0, 5, 7, 9, 0}};
    MST = greedy_algorithms::boruvkas_minimum_spanning_tree::boruvkas(graph);
    assert(greedy_algorithms::boruvkas_minimum_spanning_tree::test_findGraphSum(
               MST) == 16);
    std::cout << "2nd test passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
