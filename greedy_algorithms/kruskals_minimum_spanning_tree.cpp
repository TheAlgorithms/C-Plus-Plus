/**
 * @file
 * @brief [Kruskals Minimum Spanning
 * Tree](https://www.simplilearn.com/tutorials/data-structure-tutorial/kruskal-algorithm)
 * implementation
 *
 * @details
 * _Quoted from
 * [Simplilearn](https://www.simplilearn.com/tutorials/data-structure-tutorial/kruskal-algorithm)._
 *
 * Kruskal’s algorithm is the concept that is introduced in the graph theory of
 * discrete mathematics. It is used to discover the shortest path between two
 * points in a connected weighted graph. This algorithm converts a given graph
 * into the forest, considering each node as a separate tree. These trees can
 * only link to each other if the edge connecting them has a low value and
 * doesn’t generate a cycle in MST structure.
 *
 * @author [coleman2246](https://github.com/coleman2246)
 */

#include <array>     /// for array
#include <iostream>  /// for IO operations
#include <limits>    /// for numeric limits
#include <cstdint>   /// for uint32_t

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
template <typename T, std::size_t N, std::size_t M>
void findMinimumEdge(const T &infinity,
                     const std::array<std::array<T, N>, M> &graph) {
    if (N != M) {
        std::cout << "\nWrong input passed. Provided array has dimensions " << N
                  << "x" << M << ". Please provide a square matrix.\n";
        return;
    }
    for (int i = 0; i < graph.size(); i++) {
        int min = infinity;
        int minIndex = 0;
        for (int j = 0; j < graph.size(); j++) {
            if (i != j && graph[i][j] != 0 && graph[i][j] < min) {
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
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /**
     * define a large value for int
     * define a large value for float
     * define a large value for double
     * define a large value for uint32_t
     */
    constexpr int INFINITY_INT = std::numeric_limits<int>::max();
    constexpr float INFINITY_FLOAT = std::numeric_limits<float>::max();
    constexpr double INFINITY_DOUBLE = std::numeric_limits<double>::max();
    constexpr uint32_t INFINITY_UINT32 = UINT32_MAX;
  
    // Test case with integer values
    std::cout << "\nTest Case 1 :\n";
    std::array<std::array<int, 6>, 6> graph1{
             0,            4,            1,             4,        INFINITY_INT,   INFINITY_INT,
             4,            0,            3,             8,             3,         INFINITY_INT,
             1,            3,            0,        INFINITY_INT,       1,         INFINITY_INT,
             4,            8,       INFINITY_INT,        0,            5,              7,
        INFINITY_INT,      3,            1,              5,            0,         INFINITY_INT,
        INFINITY_INT, INFINITY_INT, INFINITY_INT,        7,       INFINITY_INT,       0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph1);

    // Test case with floating values
    std::cout << "\nTest Case 2 :\n";
     std::array<std::array<float, 3>, 3> graph2{
             0.0f,           2.5f,  INFINITY_FLOAT,
             2.5f,           0.0f,       3.2f,
        INFINITY_FLOAT,      3.2f,       0.0f};
    greedy_algorithms::findMinimumEdge(INFINITY_FLOAT, graph2);

    // Test case with double values
    std::cout << "\nTest Case 3 :\n";
   std::array<std::array<double, 5>, 5> graph3{
               0.0,             10.5,       INFINITY_DOUBLE,        6.7,              3.3,
               10.5,            0.0,              8.1,              15.4,       INFINITY_DOUBLE,
        INFINITY_DOUBLE,        8.1,              0.0,        INFINITY_DOUBLE,         7.8,
               6.7,             15.4,       INFINITY_DOUBLE,        0.0,               9.9,
               3.3,       INFINITY_DOUBLE,        7.8,              9.9,               0.0};
    greedy_algorithms::findMinimumEdge(INFINITY_DOUBLE, graph3);

    // Test Case with negative weights
    std::cout << "\nTest Case 4 :\n";
    std::array<std::array<int, 3>, 3> graph_neg{
        0,   -2,   4,
       -2,    0,   3,
        4,    3,   0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph_neg);

    // Test Case with Self-Loops
    std::cout << "\nTest Case 5 :\n";
    std::array<std::array<int, 3>, 3> graph_self_loop{
               2,       1, INFINITY_INT,
        INFINITY_INT,   0,        4,
        INFINITY_INT,   4,        0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph_self_loop);

    // Test Case with no edges
    std::cout << "\nTest Case 6 :\n";
    std::array<std::array<int, 4>, 4> no_edges{
               0,       INFINITY_INT,   INFINITY_INT,   INFINITY_INT,
        INFINITY_INT,         0,        INFINITY_INT,   INFINITY_INT,
        INFINITY_INT,   INFINITY_INT,          0,       INFINITY_INT,
        INFINITY_INT,   INFINITY_INT,   INFINITY_INT,           0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, no_edges);

    // Test Case with a non-connected graph
    std::cout << "\nTest Case 7:\n";
    std::array<std::array<int, 4>, 4> partial_graph{
                0,             2,    INFINITY_INT,         6,
                2,             0,            3,     INFINITY_INT,
        INFINITY_INT,          3,            0,             4,
                6,     INFINITY_INT,         4,             0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, partial_graph);

    // Test Case with Directed weighted graph. The Krushkal algorithm does not give
    // optimal answer
    std::cout << "\nTest Case 8:\n";
    std::array<std::array<int, 4>, 4> directed_graph{
                0,            3,            7,   INFINITY_INT,  // Vertex 0 has edges to Vertex 1 and Vertex 2
        INFINITY_INT,         0,            2,           5,  // Vertex 1 has edges to Vertex 2 and Vertex 3
        INFINITY_INT, INFINITY_INT,         0,           1,  // Vertex 2 has an edge to Vertex 3
        INFINITY_INT, INFINITY_INT, INFINITY_INT,        0};  // Vertex 3 has no outgoing edges
    greedy_algorithms::findMinimumEdge(INFINITY_INT, directed_graph);

    // Test case with wrong input passed
    std::cout << "\nTest Case 9:\n";
   std::array<std::array<int, 4>, 3> graph9{
        0,        5,        5,        5,
        5,        0,        5,        5,        
        5,        5,        5,        5};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph9);

    // Test case with all the same values between every edge
    std::cout << "\nTest Case 10:\n";
    std::array<std::array<int, 5>, 5> graph10{
        0,        5,        5,        5,        5,
        5,        0,        5,        5,        5,
        5,        5,        0,        5,        5,
        5,        5,        5,        0,        5,
        5,        5,        5,        5,        0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph10);

  // Test Case with uint32_t values
    std::cout << "\nTest Case 11 :\n";
    std::array<std::array<uint32_t, 4>, 4> graph_uint32{
                0,                      5,        INFINITY_UINT32,          9,
                5,                      0,                2,        INFINITY_UINT32,
        INFINITY_UINT32,                2,                0,                6,
                9,               INFINITY_UINT32,         6,                0};
    greedy_algorithms::findMinimumEdge(INFINITY_UINT32, graph_uint32);

    std::cout << "\nAll tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */

int main() {
    test();  // run Self-test implementation
    return 0;
}

