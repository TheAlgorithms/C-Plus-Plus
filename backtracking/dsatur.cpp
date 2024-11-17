/**
 * @file
 * @brief prints the assigned colors
 * using [DSatur](https://en.wikipedia.org/wiki/DSatur)
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
 * @author https://github.com/graph-theorist
 */

#include <array>     /// for std::array
#include <iostream>  /// for IO operations

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
 * @brief The DSatur graph coloring algorithm
 * @tparam V number of vertices in the graph
 * @param graph matrix of graph connectivity
 * @param color description
 */
template <size_t V>
void graphColoring(const std::array<std::array<int, V>, V>& graph,
                   std::array<int, V> color) {
    // colorIsUsedByNeighbors[v][c] = 1 means at least one of v's neighbors is assigned c
    std::array<std::array<int, V + 1>, V> colorIsUsedByNeighbors{};

    // Number of different colors that a vertex's neighbors are assigned
    std::array<int, V> saturation{};

    // The degree of a vertex in the subgraph induced by the uncolored vertices
    std::array<int, V> currentDegree{};

    for (int v = 0; v < V; v++) {
        currentDegree[v] = 0;

        for (int c = 1; c <= V; c++) {
            colorIsUsedByNeighbors[v][c] = 0;
        }

        for (int w = 0; w < V; w++) {
            if (graph[v][w]) {
                currentDegree[v]++;
            }
        }

        saturation[v] = 0;
        color[v] = 0;
    }

    for (int i = 0; i < V; i++) {
        // Determine the vertex that is uncolored and has the largest saturation
        // If there is a tie, take the vertex with largest currentDegree
        int maxSaturation = 0;
        int v = -1;

        for (int j = 0; j < V; j++) {
            if (color[j] >= 1) {
                continue;
            }

            if (maxSaturation < saturation[j]) {
                maxSaturation = saturation[j];
                v = j;
            } else if (maxSaturation == saturation[j] && (v < 0 || currentDegree[j] > currentDegree[v])) {
                v = j;
            }
        }

        // Determine the lowest color label that can be assigned to v
        // Start with marking the colors that are assigned to v's neighbors
        std::array<int, V + 1> neighborsUsedColor{};
        for (int w = 0; w < V; w++) {
            if (graph[v][w] && color[w] >= 1) {
                neighborsUsedColor[color[w]] = 1;
            }
        }

        color[v] = 1;
        while (color[v] <= V && neighborsUsedColor[color[v]]) {
            color[v]++;
        }

        // Update the degrees of v's neighbors in the subgraph induced by the uncolored vertices 
        // Update the saturation of v's uncolored neighbors
        for (int w = 0; w < V; w++) {
            if (!graph[v][w]) {
                continue;
            }

            if (color[w] < 1) {
                currentDegree[w]--;
            }

            if (!colorIsUsedByNeighbors[w][color[v]]) {
                colorIsUsedByNeighbors[w][color[v]] = 1;
                saturation[w]++;
            }
        }
    }

    printSolution<V>(color);
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

    backtracking::graph_coloring::graphColoring<V>(graph, color);
    return 0;
}
