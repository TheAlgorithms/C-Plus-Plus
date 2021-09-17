/**
 * @file
 * @brief [Travelling Salesman Problem]
 * (https://en.wikipedia.org/wiki/Travelling_salesman_problem) implementation
 *
 * @author [Mayank Mamgain](http://github.com/Mayank17M)
 *
 * @details
 * Travelling salesman problem asks:
 * Given a list of cities and the distances between each pair of cities, what is
 * the shortest possible route that visits each city exactly once and returns to
 * the origin city?
 * TSP can be modeled as an undirected weighted graph, such that cities are the
 * graph's vertices, paths are the graph's edges, and a path's distance is the
 * edge's weight. It is a minimization problem starting and finishing at a
 * specified vertex after having visited each other vertex exactly once.
 * This is the naive implementation of the problem.
 */

#include <algorithm>  /// for std::min
#include <cassert>    /// for assert
#include <iostream>   /// for IO operations
#include <limits>     /// for limits of integral types
#include <vector>     /// for std::vector

/**
 * @namespace graph
 * @brief Graph Algorithms
 */
namespace graph {
/**
 * @brief Function calculates the minimum path distance that will cover all the
 * cities starting from the source.
 *
 * @param cities matrix representation of cities
 * @param src Point from where salesman is starting
 * @param V number of vertices in the graph
 *
 */
int TravellingSalesmanProblem(std::vector<std::vector<uint32_t>> *cities,
                              int32_t src, uint32_t V) {
    //// vtx stores the vertexs of the graph
    std::vector<uint32_t> vtx;
    for (uint32_t i = 0; i < V; i++) {
        if (i != src) {
            vtx.push_back(i);
        }
    }

    //// store minimum weight Hamiltonian Cycle.
    int32_t min_path = 2147483647;
    do {
        //// store current Path weight(cost)
        int32_t curr_weight = 0;

        //// compute current path weight
        int k = src;
        for (int i : vtx) {
            curr_weight += (*cities)[k][i];
            k = i;
        }
        curr_weight += (*cities)[k][src];

        //// update minimum
        min_path = std::min(min_path, curr_weight);

    } while (next_permutation(vtx.begin(), vtx.end()));

    return min_path;
}
}  // namespace graph

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    std::cout << "Initiatinig Predefined Tests..." << std::endl;
    std::cout << "Initiating Test 1..." << std::endl;
    std::vector<std::vector<uint32_t>> cities = {
        {0, 20, 42, 35}, {20, 0, 30, 34}, {42, 30, 0, 12}, {35, 34, 12, 0}};
    uint32_t V = cities.size();
    assert(graph::TravellingSalesmanProblem(&cities, 0, V) == 97);
    std::cout << "1st test passed..." << std::endl;

    std::cout << "Initiating Test 2..." << std::endl;
    cities = {{0, 5, 10, 15}, {5, 0, 20, 30}, {10, 20, 0, 35}, {15, 30, 35, 0}};
    V = cities.size();
    assert(graph::TravellingSalesmanProblem(&cities, 0, V) == 75);
    std::cout << "2nd test passed..." << std::endl;

    std::cout << "Initiating Test 3..." << std::endl;
    cities = {
        {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
    V = cities.size();
    assert(graph::TravellingSalesmanProblem(&cities, 0, V) == 80);
    std::cout << "3rd test passed..." << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    std::vector<std::vector<uint32_t>> cities = {
        {0, 5, 10, 15}, {5, 0, 20, 30}, {10, 20, 0, 35}, {15, 30, 35, 0}};
    uint32_t V = cities.size();
    std::cout << graph::TravellingSalesmanProblem(&cities, 0, V) << std::endl;
    return 0;
}
