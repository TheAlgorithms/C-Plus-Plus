/**
 * @file
 * @brief prints the assigned colors
 */
#include <iostream>

/** \namespace
 * \brief Backtracking algorithms
 */
namespace {
/** A utility function to print solution
 * @param color description
 * @param V number of vertices in the graph
 */
void printSolution(const int *color, int V) {
    std::cout << "Following are the assigned colors\n";
    for (int i = 0; i < V; i++) {
        std::cout << color[i];
    }
    std::cout << "\n";
}

/** A utility function to check if the current color assignment is safe for
 * vertex v
 * @tparam V number of vertices in the graph
 * @param v description
 * @param graph description
 * @param color description
 * @param c description
 * @returns `true` if ....
 * @returns `false` if ....
 */
template <int V>
bool isSafe(int v, const bool graph[V][V], const int *color, int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && c == color[i]) {
            return false;
        }
    }
    return true;
}

/** A recursive utility function to solve m coloring problem
 * @tparam V number of vertices in the graph
 * @param graph description
 * @param m description
 * @param [in,out] color description // used in,out to notify in documentation
 * that this parameter gets modified by the function
 * @param v description
 */
template <int V>
void graphColoring(bool graph[V][V], int m, int color[V], int v) {
    // base case:
    // If all vertices are assigned a color then return true
    if (v == V) {
        printSolution(color, V);
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
}  // namespace

/**
 * Main function
 */
int main() {
    // Create following graph and test whether it is 3 colorable
    // (3)---(2)
    // |   / |
    // |  /  |
    // | /   |
    // (0)---(1)

    const int V = 4;  // number of vertices in the graph
    bool graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    };
    int m = 3;  // Number of colors

    int color[V];

    for (int i = 0; i < V; i++) {
        color[i] = 0;
    }

    graphColoring<V>(graph, m, color, 0);
    return 0;
}
