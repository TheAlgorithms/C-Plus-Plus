/**
 *
 * \file
 * \brief [Connected Components
 * (Connected Components)](https://en.wikipedia.org/wiki/Component_(graph_theory))
 *
 * \author [Ayaan Khan](http://github.com/ayaankhan98)
 *
 * \details
 * A graph is a collection of nodes also called vertices and these vertices
 * are connected by edges. A connected component in a graph refers to a set of
 * vertices which are reachable form one another.
 *
 * <pre>
 * Example - Here is graph with 3 connected components
 *
 *      3   9           6               8
 *     / \ /           / \             / \
 *    2---4           2   7           3   7
 *
 *    first          second           third
 *    component      component        component
 * </pre>
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

/**
 * Class for representing graph as a adjacency list.
 */
class graph {
 private:
   /** \brief adj stores adjacency list representation of graph */
    vector<vector<int>> adj;

    /** \brief keep track of connected components */
    int connected_components;

    /** \brief Utility function to perform depth first search on graph */
    void depth_first_search();

    /** \brief Utility function that explores given vertex in graph */
    void explore(int, vector<bool> &);

 public:
    /** 
     * \brief Constructor that intiliazes the graph on creation and set
     * the connected components to 0
     */
    explicit graph(int n) : adj(n, vector<int>()) { connected_components = 0; }
    
    /** \brief Function to add a edge between two nodes or vertices of graph */
    void addEdge(int, int);

    /** 
     * \brief Function the calculates the connected compoents in the graph
     * by performing the depth first search on graph
     *
     * @return connected_components total connected components in graph
     */
    int getConnectedComponents() {
        depth_first_search();
        return connected_components;
    }
};

/**
 * \brief Function that add edge between two nodes or vertices of graph
 *
 * @param u any node or vertex of graph
 * @param v any node or vertex of graph
 */
void graph::addEdge(int u, int v) {
    adj[u - 1].push_back(v - 1);
    adj[v - 1].push_back(u - 1);
}

/**
 * \brief Function that perfoms depth first search algorithm on graph
 */
void graph::depth_first_search() {
    int n = adj.size();
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            explore(i, visited);
            connected_components++;
        }
    }
}
/**
 * \brief Utility function for depth first seach algorithm
 * this function explores the vertex which is passed into.
 *
 * @param u vertex or node to be explored
 * @param visited already visited vertex
 */
void graph::explore(int u, vector<bool> &visited) {
    visited[u] = true;
    for (auto v : adj[u]) {
        if (!visited[v]) {
            explore(v, visited);
        }
    }
}

/** Main function */
int main() {
  /// creating a graph with 4 vertex 
    graph g(4);

  /// Adding edges between vertices
    g.addEdge(1, 2);
    g.addEdge(3, 2);

  /// printing the connected components
    std::cout << g.getConnectedComponents();
    return 0;
}
