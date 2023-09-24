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
static void tests()		//test case functions, for adding more test cases
{
    constexpr int INFINITY = 99999;
    std::array<std::array<int, 6>, 6> graph1{
        0,        1,        2,        6,        INFINITY, INFINITY,
        2,        0,        3,        8,        3,        INFINITY,
        1,        3,        0,        INFINITY, 1,        INFINITY,
        4,        8,        INFINITY, 0,        5,        7,
        INFINITY, 3,        1,        5,        0,        INFINITY,
        INFINITY, INFINITY, INFINITY, 7,        INFINITY, 0};

        std::array<std::array<int, 6>, 6> graph2{
        3,        1,               7,        9,        INFINITY,    INFINITY,
        4,        INFINITY,        1,        9,        2,           INFINITY,
        6,        7,               2,        0,        9,           1,
        9,        7,               INFINITY, 2,        2,           3,
        INFINITY, 1,               6,        3,        INFINITY,    5,
        5,        3,               1,        2,        INFINITY,    7};

    std::cout<<"First test case:\n";
    greedy_algorithms::findMinimumEdge(INFINITY, graph1);
    std::cout<<"Second test case:\n";
    greedy_algorithms::findMinimumEdge(INFINITY, graph2);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
