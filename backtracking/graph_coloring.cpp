/**
 * @file
 * @brief prints the assigned colors
 * using [Graph Coloring](https://en.wikipedia.org/wiki/Graph_coloring)
 * algorithm
 *
 * @details
 * In graph theory, graph coloring is a special case of graph labeling;
 * it is an assignment of labels traditionally called "colors" to elements of a
 * graph subject to certain constraints. In its simplest form, it is a way of
 * coloring the vertices of a graph such that no two adjacent vertices are of
 * the same color; this is called a vertex coloring. Similarly, an edge coloring
 * assigns a color to each edge so that no two adjacent edges are of the same
 * color, and a face coloring of a planar graph assigns a color to each face or
 * region so that no two faces that share a boundary have the same color.
 *
 * @author [Anup Kumar Panwar](https://github.com/AnupKumarPanwar)
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <array>     /// for std::array
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
/**
 * @namespace graph_coloring
 * @brief Functions for the [Graph
 * Coloring](https://en.wikipedia.org/wiki/Graph_coloring) algorithm,
 */
namespace graph_coloring {
/**
 * @brief A utility function to print the solution
 * @tparam V number of vertices in the graph
 * @param color array of colors assigned to the nodes
 */
template <size_t V>
void printSolution(const std::array<int, V>& color) {
    std::cout << "Following are the assigned colors\n";
    for (auto& col : color) {
        std::cout << col;
    }
    std::cout << "\n";
}

/**
 * @brief Utility function to check if the current color assignment is safe for
 * vertex v
 * @tparam V number of vertices in the graph
 * @param v index of graph vertex to check
 * @param graph matrix of graph nonnectivity
 * @param color vector of colors assigned to the graph nodes/vertices
 * @param c color value to check for the node `v`
 * @returns `true` if the color is safe to be assigned to the node
 * @returns `false` if the color is not safe to be assigned to the node
 */
template <size_t V>
bool isSafe(int v, const std::array<std::array<int, V>, V>& graph,
            const std::array<int, V>& color, int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && c == color[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Recursive utility function to solve m coloring problem
 * @tparam V number of vertices in the graph
 * @param graph matrix of graph nonnectivity
 * @param m number of colors
 * @param [in,out] color description // used in,out to notify in documentation
 * that this parameter gets modified by the function
 * @param v index of graph vertex to check
 */
template <size_t V>
void graphColoring(const std::array<std::array<int, V>, V>& graph, int m,
                   std::array<int, V> color, int v) {
    // base case:
    // If all vertices are assigned a color then return true
    if (v == V) {
        printSolution<V>(color);
        return;
    }

    // Consider this vertex v and try different colors
    for (int c = 1; c <= m; c++) {
        // Check if assignment of color c to v is fine
        if (isSafe<V>(v, graph, color, c)) {
            color[v] = c;

            // recur to assign colors to rest of the vertices
            graphColoring<V>(graph, m, color, v + 1);

            // If assigning color c doesn't lead to a solution then remove it
            color[v] = 0;
        }
    }
}
}  // namespace graph_coloring
}  // namespace backtracking

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // Create following graph and test whether it is 3 colorable
    // (3)---(2)
    // |   / |
    // |  /  |
    // | /   |
    // (0)---(1)

    const int V = 4;  // number of vertices in the graph
    std::array<std::array<int, V>, V> graph = {
        std::array<int, V>({0, 1, 1, 1}), std::array<int, V>({1, 0, 1, 0}),
        std::array<int, V>({1, 1, 0, 1}), std::array<int, V>({1, 0, 1, 0})};

    int m = 3;  // Number of colors
    std::array<int, V> color{};

    backtracking::graph_coloring::graphColoring<V>(graph, m, color, 0);
    return 0;
}
