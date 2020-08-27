/**
 * @file
 *
 * @brief Algorithm to check whether a graph is
 * [bipartite](https://en.wikipedia.org/wiki/Bipartite_graph)
 *
 * @details
 * A graph is a collection of nodes also called vertices and these vertices
 * are connected by edges. A graph is bipartite if its vertices can be
 * divided into two disjoint and independent sets U and V such that every edge
 * connects a vertex in U to one in V.
 *
 * The algorithm implemented in this file determines whether the given graph
 * is bipartite or not.
 *
 * <pre>
 *  Example - Here is a graph g1 with 5 vertices and is bipartite
 *
 *     1   4
 *    / \ / \
 *   2   3   5
 *
 * Example - Here is a graph G2 with 3 vertices and is not bipartite
 *
 *   1 --- 2
 *    \   /
 *      3
 *
 * </pre>
 *
 * @author [Akshat Vaya](https://github.com/AkVaya)
 *
 */
#include <iostream>
#include <queue>
#include <vector>

/**
 * @namespace graph
 * @brief Graph algorithms
 */
namespace graph {
/**
 * @namespace is_graph_bipartite
 * @brief Functions for checking whether a graph is bipartite or not
 */
namespace is_graph_bipartite {
/**
 * @brief Class for representing graph as an adjacency list.
 */
class Graph {
 private:
    int n;  ///< size of the graph

    std::vector<std::vector<int> >
        adj;  ///< adj stores the graph as an adjacency list

    std::vector<int> side;  ///< stores the side of the vertex

 public:
    /**
     * @brief Constructor that initializes the graph on creation
     * @param size number of vertices of the graph
     */
    explicit Graph(int size) {
        n = size;
        adj.resize(n);
        side.resize(n, -1);
    }

    void addEdge(int u, int v);  /// function to add edges to our graph

    bool
    is_bipartite();  /// function to check whether the graph is bipartite or not
};

/**
 * @brief Function that add an edge between two nodes or vertices of graph
 *
 * @param u is a node or vertex of graph
 * @param v is a node or vertex of graph
 */
void Graph::addEdge(int u, int v) {
    adj[u - 1].push_back(v - 1);
    adj[v - 1].push_back(u - 1);
}

/**
 * @brief function that checks whether the graph is bipartite or not
 * the function returns true if the graph is a bipartite graph
 * the function returns false if the graph is not a bipartite graph
 *
 * @details
 * Here, side refers to the two disjoint subsets of the bipartite graph.
 * Initially, the values of side are set to -1 which is an unassigned state. A
 * for loop is run for every vertex of the graph. If the current edge has no
 * side assigned to it, then a Breadth First Search operation is performed. If
 * two neighbours have the same side then the graph will not be bipartite and
 * the value of check becomes false. If and only if each pair of neighbours have
 * different sides, the value of check will be true and hence the graph
 * bipartite.
 *
 * @returns `true` if th graph is bipartite
 * @returns `false` otherwise
 */
bool Graph::is_bipartite() {
    bool check = true;
    std::queue<int> q;
    for (int current_edge = 0; current_edge < n; ++current_edge) {
        if (side[current_edge] == -1) {
            q.push(current_edge);
            side[current_edge] = 0;
            while (q.size()) {
                int current = q.front();
                q.pop();
                for (auto neighbour : adj[current]) {
                    if (side[neighbour] == -1) {
                        side[neighbour] = (1 ^ side[current]);
                        q.push(neighbour);
                    } else {
                        check &= (side[neighbour] != side[current]);
                    }
                }
            }
        }
    }
    return check;
}
}  // namespace is_graph_bipartite
}  // namespace graph

/**
 * Function to test the above algorithm
 * @returns none
 */
static void test() {
    graph::is_graph_bipartite::Graph G1(
        5);  /// creating graph G1 with 5 vertices
    /// adding edges to the graphs as per the illustrated example
    G1.addEdge(1, 2);
    G1.addEdge(1, 3);
    G1.addEdge(3, 4);
    G1.addEdge(4, 5);

    graph::is_graph_bipartite::Graph G2(
        3);  /// creating graph G2 with 3 vertices
    /// adding edges to the graphs as per the illustrated example
    G2.addEdge(1, 2);
    G2.addEdge(1, 3);
    G2.addEdge(2, 3);

    /// checking whether the graphs are bipartite or not
    if (G1.is_bipartite()) {
        std::cout << "The given graph G1 is a bipartite graph\n";
    } else {
        std::cout << "The given graph G1 is not a bipartite graph\n";
    }
    if (G2.is_bipartite()) {
        std::cout << "The given graph G2 is a bipartite graph\n";
    } else {
        std::cout << "The given graph G2 is not a bipartite graph\n";
    }
}

/**
 * Main function
 */
int main() {
    test();  /// Testing
    return 0;
}
