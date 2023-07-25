#include <array>     /// for array
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace
 * @brief Greedy Algorithms
 */
namespace greedy_algorithms {
/**
 * @brief Finds the minimum edge of the given graph.
 * @param infinity Defines the infinity of the graph
 * @param graph The graph that will be used to find the edge
 * @returns void
 */
template <typename T>
void findMinimumEdge(const int &infinity,
                     const std::array<std::array<T, 6>, 6> &graph) {
    for (int i = 0; i < graph.size(); i++) {
        int min = infinity;
        int minIndex = 0;
        for (int j = 0; j < graph.size(); j++) {
            if (graph[i][j] != 0 && graph[i][j] < min) {
                min = graph[i][j];
                minIndex = j;
            }
        }
        std::cout << i << "  -  " << minIndex << "\t" << graph[i][minIndex]
                  << "\n";
    }
}
}  // namespace greedy_algorithms

/**
 * @brief Test function to verify the findMinimumEdge function.
 * @returns void
 */
static void test() {
    const int MAX_WEIGHT = 99999;
    std::array<std::array<int, 6>, 6> graph;
    graph[0][0] = 0;
    graph[0][1] = 4;
    graph[0][2] = 1;
    graph[0][3] = 4;
    graph[0][4] = MAX_WEIGHT;
    graph[0][5] = MAX_WEIGHT;

    graph[1][0] = 4;
    graph[1][1] = 0;
    graph[1][2] = 3;
    graph[1][3] = 8;
    graph[1][4] = 3;
    graph[1][5] = MAX_WEIGHT;

    graph[2][0] = 1;
    graph[2][1] = 3;
    graph[2][2] = 0;
    graph[2][3] = MAX_WEIGHT;
    graph[2][4] = 1;
    graph[2][5] = MAX_WEIGHT;

    graph[3][0] = 4;
    graph[3][1] = 8;
    graph[3][2] = MAX_WEIGHT;
    graph[3][3] = 0;
    graph[3][4] = 5;
    graph[3][5] = 7;

    graph[4][0] = MAX_WEIGHT;
    graph[4][1] = 3;
    graph[4][2] = 1;
    graph[4][3] = 5;
    graph[4][4] = 0;
    graph[4][5] = MAX_WEIGHT;

    graph[5][0] = MAX_WEIGHT;
    graph[5][1] = MAX_WEIGHT;
    graph[5][2] = MAX_WEIGHT;
    graph[5][3] = 7;
    graph[5][4] = MAX_WEIGHT;
    graph[5][5] = 0;

    // Test case 1
    std::cout << "Test case 1:\n";
    std::cout << "Expected Output:\n";
    std::cout << "0 - 2\t1\n";
    std::cout << "1 - 4\t3\n";
    std::cout << "2 - 0\t1\n";
    std::cout << "3 - 0\t4\n";
    std::cout << "4 - 2\t1\n";
    std::cout << "5 - 3\t7\n";
    std::cout << "Actual Output:\n";
    greedy_algorithms::findMinimumEdge(MAX_WEIGHT, graph);
    std::cout << "Test case 1 passed.\n\n";

    // Test case 2 with a graph that has no edges (all MAX_WEIGHT)
    std::array<std::array<int, 6>, 6> graphNoEdges;
    for (int i = 0; i < graphNoEdges.size(); i++) {
        for (int j = 0; j < graphNoEdges[i].size(); j++) {
            graphNoEdges[i][j] = MAX_WEIGHT;
        }
    }
    std::cout << "Test case 2:\n";
    std::cout << "Expected Output:\n";
    std::cout << "0 - 0\t0\n";
    std::cout << "1 - 0\t99999\n";
    std::cout << "2 - 0\t99999\n";
    std::cout << "3 - 0\t99999\n";
    std::cout << "4 - 0\t99999\n";
    std::cout << "5 - 0\t99999\n";
    std::cout << "Actual Output:\n";
    greedy_algorithms::findMinimumEdge(MAX_WEIGHT, graphNoEdges);
    std::cout << "Test case 2 passed.\n";

    // Use assert to check the test cases
    assert((greedy_algorithms::findMinimumEdge(MAX_WEIGHT, graph),
            true));  // Test case 1
    assert((greedy_algorithms::findMinimumEdge(MAX_WEIGHT, graphNoEdges),
            true));  // Test case 2
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}
