/**
 * @file
 * @brief [Graph Coloring](https://en.wikipedia.org/wiki/Graph_coloring)
 * algorithm
 * @details
 * Graph coloring assigns colors to vertices of a graph such that no two
 * adjacent vertices share the same color. This implementation uses backtracking
 * to find a valid coloring for a given graph and number of colors (m). It is
 * useful for problems like scheduling, map coloring, and register allocation.
 *
 * ### Algorithm
 * 1. Start with vertex 0, assign colors from 1 to m.
 * 2. Check if a color is safe for a vertex (no adjacent vertex has the same
 * color).
 * 3. If safe, assign the color and recurse to the next vertex.
 * 4. If all vertices are colored, a solution is found.
 * 5. Backtrack if no valid color works for a vertex.
 *
 * ### Complexity
 * - Time: O(m^V) worst-case (exponential, m=colors, V=vertices)
 * - Space: O(V) for recursion stack and color array
 *
 * ### Example
 * For graph: (3)---(2)
 *            |   / |
 *            |  /  |
 *            | /   |
 *           (0)---(1)
 * With 3 colors: Possible coloring: 1 2 3 2
 *
 * @author [Anup Kumar Panwar](https://github.com/AnupKumarPanwar)
 * @author [David Leal](https://github.com/Panquesito7)
 * @author [Contributor] (fix Test 5 for 2-colorable disconnected graph)
 * @author [Contributor] (added Add comprehensive test cases for backtracking
 * algorithms)(https://github.com/kokatesaurabh)
 */

#include <array>     /// for std::array
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
/**
 * @namespace graph_coloring
 * @brief Functions for the [Graph
 * Coloring](https://en.wikipedia.org/wiki/Graph_coloring) algorithm
 */
namespace graph_coloring {
/**
 * @brief Prints the color assignments for vertices
 * @tparam V number of vertices in the graph
 * @param color array of colors assigned to vertices
 */
template <size_t V>
void printSolution(const std::array<int, V>& color) {
    std::cout << "Following are the assigned colors\n";
    for (const auto& col : color) {
        std::cout << col << " ";
    }
    std::cout << "\n";
}

/**
 * @brief Checks if assigning color c to vertex v is safe
 * @tparam V number of vertices in the graph
 * @param v index of the vertex to check
 * @param graph adjacency matrix of the graph
 * @param color array of colors assigned to vertices
 * @param c color to check for vertex v
 * @returns true if the color is safe, false otherwise
 */
template <size_t V>
bool isSafe(int v, const std::array<std::array<int, V>, V>& graph,
            const std::array<int, V>& color, int c) {
    for (int i = 0; i < V; ++i) {
        if (graph[v][i] && color[i] == c) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Recursive function to solve the graph coloring problem
 * @tparam V number of vertices in the graph
 * @param graph adjacency matrix of the graph
 * @param m number of colors
 * @param color array to store colors assigned to vertices
 * @param v current vertex index
 * @returns true if a valid coloring is found, false otherwise
 */
template <size_t V>
bool graphColoringUtil(const std::array<std::array<int, V>, V>& graph, int m,
                       std::array<int, V>& color, int v) {
    if (v == V) {
        return true;
    }

    for (int c = 1; c <= m; ++c) {
        if (isSafe<V>(v, graph, color, c)) {
            color[v] = c;
            if (graphColoringUtil<V>(graph, m, color, v + 1)) {
                return true;
            }
            color[v] = 0;  // Backtrack
        }
    }
    return false;
}

/**
 * @brief Solves the graph coloring problem
 * @tparam V number of vertices in the graph
 * @param graph adjacency matrix of the graph
 * @param m number of colors
 * @returns true if a valid coloring exists, false otherwise
 */
template <size_t V>
bool graphColoring(const std::array<std::array<int, V>, V>& graph, int m) {
    std::array<int, V> color{};
    if (!graphColoringUtil<V>(graph, m, color, 0)) {
        std::cout << "Solution does not exist\n";
        return false;
    }
    printSolution<V>(color);
    return true;
}
}  // namespace graph_coloring
}  // namespace backtracking

/**
 * @brief Self-test implementations for graph coloring
 */
static void test() {
    std::cout << "Running comprehensive graph coloring tests...\n";

    // Test 1: Basic 4-vertex graph with 3 colors
    {
        const int V = 4;
        std::array<std::array<int, V>, V> graph1 = {
            {{{0, 1, 1, 1}}, {{1, 0, 1, 0}}, {{1, 1, 0, 1}}, {{1, 0, 1, 0}}}};
        assert(backtracking::graph_coloring::graphColoring<V>(graph1, 3) ==
               true);
        std::cout << "Test 1 passed\n";
    }

    // Test 2: Complete graph K4 with 4 colors
    {
        const int V = 4;
        std::array<std::array<int, V>, V> graph2 = {
            {{{0, 1, 1, 1}}, {{1, 0, 1, 1}}, {{1, 1, 0, 1}}, {{1, 1, 1, 0}}}};
        assert(backtracking::graph_coloring::graphColoring<V>(graph2, 4) ==
               true);
        std::cout << "Test 2 passed\n";
    }

    // Test 3: Triangle graph with 2 colors (no solution)
    {
        const int V = 3;
        std::array<std::array<int, V>, V> graph3 = {
            {{{0, 1, 1}}, {{1, 0, 1}}, {{1, 1, 0}}}};
        assert(backtracking::graph_coloring::graphColoring<V>(graph3, 2) ==
               false);
        std::cout << "Test 3 passed\n";
    }

    // Test 4: Single vertex graph with 1 color
    {
        const int V = 1;
        std::array<std::array<int, V>, V> graph4 = {{{{0}}}};
        assert(backtracking::graph_coloring::graphColoring<V>(graph4, 1) ==
               true);
        std::cout << "Test 4 passed\n";
    }

    // Test 5: Disconnected 2-colorable graph
    {
        const int V = 5;
        std::array<std::array<int, V>, V> graph5 = {{{{0, 1, 0, 0, 0}},
                                                     {{1, 0, 0, 0, 0}},
                                                     {{0, 0, 0, 1, 0}},
                                                     {{0, 0, 1, 0, 0}},
                                                     {{0, 0, 0, 0, 0}}}};
        assert(backtracking::graph_coloring::graphColoring<V>(graph5, 2) ==
               true);
        std::cout << "Test 5 passed\n";
    }

    // Test 6: Star graph with 2 colors
    {
        const int V = 5;
        std::array<std::array<int, V>, V> graph6 = {{{{0, 1, 1, 1, 1}},
                                                     {{1, 0, 0, 0, 0}},
                                                     {{1, 0, 0, 0, 0}},
                                                     {{1, 0, 0, 0, 0}},
                                                     {{1, 0, 0, 0, 0}}}};
        assert(backtracking::graph_coloring::graphColoring<V>(graph6, 2) ==
               true);
        std::cout << "Test 6 passed\n";
    }

    std::cout << "All tests passed successfully!\n\n";
}

/**
 * @brief Main function
 */
int main() {
    test();

    std::cout << "Demo graph:\n";
    const int V = 4;
    std::array<std::array<int, V>, V> graph = {
        {{{0, 1, 1, 1}}, {{1, 0, 1, 0}}, {{1, 1, 0, 1}}, {{1, 0, 1, 0}}}};
    int m = 3;
    backtracking::graph_coloring::graphColoring<V>(graph, m);

    return 0;
}
