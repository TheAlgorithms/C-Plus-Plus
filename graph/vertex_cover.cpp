/*
  @author [Rajat Garg](https://github.com/Rajat379)
  @file

  Implementation of a vertex cover in a graph.
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>

namespace {
class Graph {
    int V;
    std::list<int> *adj;  // Pointer to an array containing adjacency lists
 public:
    Graph(int V);
    void addEdge(int v, int w);  // function to add an edge to graph
    void printVertexCover();     // prints vertex cover
};

}  // namespace

Graph::Graph(int V) {
    this->V = V;
    adj = new std::list<int>[V];
}

void Graph::addEdge(int v, int w) {
    // Fill up both adj lists
    adj[v].push_back(w);
    adj[w].push_back(v);
}

// The function to print vertex cover
void Graph::printVertexCover() {
    bool visited[V];
    for (int i = 0; i < V; i++) visited[i] = false;

    std::list<int>::iterator i;

    for (int u = 0; u < V; u++) {
        // An edge is only picked when both visited[u] and visited[v]
        // are false
        if (visited[u] == false) {
            // Go through all adjacents of u and pick the first not
            // yet visited vertex (We are basically picking an edge
            // (u, v) from remaining edges.
            for (i = adj[u].begin(); i != adj[u].end(); ++i) {
                int v = *i;
                if (visited[v] == false) {
                    visited[v] = true;
                    visited[u] = true;
                    break;
                }
            }
        }
    }

    // Print the vertex cover
    for (int i = 0; i < V; i++)
        if (visited[i])
            std::cout << i << " ";
}

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);

    // Created a graph with 7 nodes
    // Established the vertices amongst them
    g.printVertexCover();

    // Final ouput - 0 1 3 4 5 6

    return 0;
}