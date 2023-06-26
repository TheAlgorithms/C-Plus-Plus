#include <limits.h>
#include <iostream>

using namespace std;

// Wrapper class for storing a graph
class Graph {
 public:
    int vertexNum;
    int **edges;

    /**
     * @brief Constructs a graph
     * @param V number of vertices of the graph
     */
    Graph(const int V) {
        // Initialize the array edges.
        this->edges = new int *[V];
        for (int i = 0; i < V; i++) {
            edges[i] = new int[V];
        }

        // Fills the array with zeros.
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
    void addEdge(int src, int dst, int weight) {
        this->edges[src][dst] = weight;
    }
};

/**
 * @brief Finds the vertex with the minimum distance in mdist[].
 * 
 * @param mdist Array of distances to each vertex.
 * @param vset Array indicating inclusion in the shortest path tree.
 * @param V Number of vertices in the graph.
 * @return Index of the vertex with the minimum distance.
 */
int minDistance(int mdist[], bool vset[], int V) {
    int minVal = INT_MAX, minInd = 0;
    for (int i = 0; i < V; i++) {
        if (!vset[i] && (mdist[i] < minVal)) {
            minVal = mdist[i];
            minInd = i;
        }
    }

    return minInd;
}

// Utility function to print distances
void print(int dist[], int V) {
    cout << "\nVertex  Distance" << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] < INT_MAX)
            cout << i << "\t" << dist[i] << endl;
        else
            cout << i << "\tINF" << endl;
    }
}


// Finds the shortest path from the given source to all other vertices using Dijkstra's Algorithm.
// Note: It doesn't work with negative weights.
void Dijkstra(Graph graph, int src) {
    int V = graph.vertexNum;
    int mdist[V];  // Stores updated distances to vertex
    bool vset[V];  // vset[i] is true if the vertex i is included in the shortest path tree 

    // Initialise mdist and vset. Set distance of source as zero
    for (int i = 0; i < V; i++) {
        mdist[i] = INT_MAX;
        vset[i] = false;
    }

    mdist[src] = 0;

    // iterate to find shortest path
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(mdist, vset, V);

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

// Driver Function
int main() {
    int V, E, gsrc;
    int src, dst, weight;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    // Create a graph object
    Graph G(V);

    // Input edges and weights
    for (int i = 0; i < E; i++) {
        cout << "\nEdge " << i + 1 << "\nEnter source: ";
        cin >> src;
        cout << "Enter destination: ";
        cin >> dst;
        cout << "Enter weight: ";
        cin >> weight;

        // Check if source and destination are within bounds
        if (src >= 0 && src < V && dst >= 0 && dst < V) {
            G.addEdge(src, dst, weight);
        } else {
            cout << "source and/or destination out of bounds" << endl;
            i--;
            continue;
        }
    }
    cout << "\nEnter source:";
    cin >> gsrc;
    Dijkstra(G, gsrc);

    return 0;
}
