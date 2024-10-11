/**
 * @file
 * @brief [Dijkstra](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm) algorithm
 * implementation
 * @details
 * _Quote from Wikipedia._
 * 
 * **Dijkstra's algorithm** is an algorithm for finding the
 * shortest paths between nodes in a weighted graph, which may represent, for
 * example, road networks. It was conceived by computer scientist Edsger W.
 * Dijkstra in 1956 and published three years later.
 *
 * @author [David Leal](https://github.com/Panquesito7)
 * @author [Arpan Jain](https://github.com/arpanjain97)
 */

#include <cassert>   /// for assert
#include <climits>   /// for INT_MAX
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace
 * @brief Greedy Algorithms
 */
namespace greedy_algorithms {
/**
 * @namespace
 * @brief Functions for the [Dijkstra](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm) algorithm implementation
 */
namespace dijkstra {
/**
 * @brief Wrapper class for storing a graph
 */
class Graph {
 public:
    int vertexNum = 0;
    std::vector<std::vector<int>> edges{};

    /**
     * @brief Constructs a graph
     * @param V number of vertices of the graph
     */
    explicit Graph(const int V) {
        // Initialize the array edges
        this->edges = std::vector<std::vector<int>>(V, std::vector<int>(V, 0));
        for (int i = 0; i < V; i++) {
            edges[i] = std::vector<int>(V, 0);
        }

        // Fills the array with zeros
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                edges[i][j] = 0;
            }
        }

        this->vertexNum = V;
    }

    /**
     * @brief Adds an edge to the graph
     * @param src the graph the edge should be added to
     * @param dst the position where the edge should be added to
     * @param weight the weight of the edge that should be added
     * @returns void
     */
    void add_edge(int src, int dst, int weight) {
        this->edges[src][dst] = weight;
    }
};

/**
 * @brief Utility function that finds
 * the vertex with the minimum distance in `mdist`.
 *
 * @param mdist array of distances to each vertex
 * @param vset array indicating inclusion in the shortest path tree
 * @param V the number of vertices in the graph
 * @returns index of the vertex with the minimum distance
 */
int minimum_distance(std::vector<int> mdist, std::vector<bool> vset, int V) {
    int minVal = INT_MAX, minInd = 0;
    for (int i = 0; i < V; i++) {
        if (!vset[i] && (mdist[i] < minVal)) {
            minVal = mdist[i];
            minInd = i;
        }
    }

    return minInd;
}

/**
 * @brief Utility function to print the distances to vertices.
 *
 * This function prints the distances to each vertex in a tabular format. If the
 * distance is equal to INT_MAX, it is displayed as "INF".
 *
 * @param dist An array representing the distances to each vertex.
 * @param V The number of vertices in the graph.
 * @return void
 */
void print(std::vector<int> dist, int V) {
    std::cout << "\nVertex  Distance\n";
    for (int i = 0; i < V; i++) {
        if (dist[i] < INT_MAX) {
            std::cout << i << "\t" << dist[i] << "\n";
        }
        else {
            std::cout << i << "\tINF" << "\n";
        }
    }
}

/**
 * @brief The main function that finds the shortest path from a given source
 * to all other vertices using Dijkstra's Algorithm.
 * @note This doesn't work on negative weights.
 * @param graph the graph to be processed
 * @param src the source of the given vertex
 * @returns void
 */
void dijkstra(Graph graph, int src) {
    int V = graph.vertexNum;
    std::vector<int> mdist{};  // Stores updated distances to the vertex
    std::vector<bool> vset{};  // `vset[i]` is true if the vertex `i` is included in the shortest path tree

    // Initialize `mdist and `vset`. Set the distance of the source as zero
    for (int i = 0; i < V; i++) {
        mdist[i] = INT_MAX;
        vset[i] = false;
    }

    mdist[src] = 0;

    // iterate to find the shortest path
    for (int count = 0; count < V - 1; count++) {
        int u = minimum_distance(mdist, vset, V);

        vset[u] = true;

        for (int v = 0; v < V; v++) {
            if (!vset[v] && graph.edges[u][v] &&
                mdist[u] + graph.edges[u][v] < mdist[v]) {
                mdist[v] = mdist[u] + graph.edges[u][v];
            }
        }
    }

    print(mdist, V);
}
}  // namespace dijkstra
}  // namespace greedy_algorithms

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    greedy_algorithms::dijkstra::Graph graph(8);

    // 1st test.
    graph.add_edge(6, 2, 4);
    graph.add_edge(2, 6, 4);

    assert(graph.edges[6][2] == 4);

    // 2nd test.
    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 0, 1);

    assert(graph.edges[0][1] == 1);

    // 3rd test.
    graph.add_edge(0, 2, 7);
    graph.add_edge(2, 0, 7);
    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 1, 1);

    assert(graph.edges[0][2] == 7);

    // 4th test.
    graph.add_edge(1, 3, 3);
    graph.add_edge(3, 1, 3);
    graph.add_edge(1, 4, 2);
    graph.add_edge(4, 1, 2);
    graph.add_edge(2, 3, 2);

    assert(graph.edges[1][3] == 3);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
