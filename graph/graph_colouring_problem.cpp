#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
    int V;
    list<int> *adj;

public:
    Graph(int V);
    void addEdge(int v, int w);
    void greedyColoring();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::greedyColoring() {
    vector<int> result(V, -1);  // Initialize all vertices as uncolored

    // Assign the first color to the first vertex
    result[0] = 0;

    // A temporary array to store the available colors.
    vector<bool> available(V, false);

    // Process the remaining V-1 vertices
    for (int u = 1; u < V; u++) {
        // Initialize the available colors
        fill(available.begin(), available.end(), false);

        // Find the colors of adjacent vertices and mark them as unavailable
        for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
            if (result[*i] != -1) {
                available[result[*i]] = true;
            }
        }

        // Find the first available color
        int cr;
        for (cr = 0; cr < V; cr++) {
            if (available[cr] == false) {
                break;
            }
        }

        result[u] = cr;  // Assign the found color
    }

    // Print the result
    for (int u = 0; u < V; u++) {
        cout << "Vertex " << u << " ---> Color " << result[u] << endl;
    }
}

int main() {
    int V, E;  // V is the number of vertices, E is the number of edges
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    Graph g(V);

    for (int i = 0; i < E; i++) {
        int v, w;
        cout << "Enter edge " << i + 1 << " (format: v w): ";
        cin >> v >> w;
        g.addEdge(v, w);
    }

    cout << "Coloring of the graph:\n";
    g.greedyColoring();

    return 0;
}
