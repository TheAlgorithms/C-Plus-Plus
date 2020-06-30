/**
 * @file
 * \brief Implementation of Dijkstra's Algorithm
 * \details
 * Dijkstra's Algorithm is a greedy solution for the single-source shortest path problem in a graph whose edges have integer weights.
 * This solution takes in input to build the graph and outputs distances to nodes from a selected source node.
 * @author arpanjain97
 * @author christianbender
 * @author ali-mir
*/

#include <climits>
#include <iostream>

/**
* Class for representing a graph.
*/
class Graph {
 public:
    int vertexNum; ///< number of vertices in the graph
    int **edges; ///< matrix of edge connection weights. `edge[i][j]` represents the weight of edge

    /**
     * \brief Constructor that initiliazes the graph by creating the edges array.
     * @param V number of vertices in the graph
     */
    explicit Graph(const int V) {
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

    /** Class destructor to deallocate memory on class destruction */
    ~Graph() {
        for (int i = 0; i < this->vertexNum; i++) {
            delete[] edges[i];
        }
        delete[] edges;
    }

    // Adds the given edge to the graph
    void addEdge(int src, int dst, int weight) {
        this->edges[src][dst] = weight;
    }
};
/**
 * Function to find minimum distance vertex in mdist.
 * @param mdist array of minimum distances to vertices
 * @param vset array of vertices, where vset[i] is a boolean value that indicates
 * whether the vertex i is included in the shortest path tree
 * @param V number of vertices
 * @return minimum distance vertex
 */
int minDistance(const int *mdist, const bool *vset, int V) {
    int minVal = std::numeric_limits<int>::infinity(), minInd = 0;
    for (int i = 0; i < V; i++) {
        if (!vset[i] && (mdist[i] < minVal)) {
            minVal = mdist[i];
            minInd = i;
        }
    }

    return minInd;
}

/**
 * Function to print minimum distances to vertices.
 * @param dist array of distances to vertices
 * @param V number of vertices
 */
void print(const int *dist, int V) {
    std::cout << "\nVertex  Distance" << std::endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] < INT_MAX)
            std::cout << i << "\t" << dist[i] << std::endl;
        else
            std::cout << i << "\tINF" << std::endl;
    }
}

/**
 * The main function that finds the shortest path from given source
 * to all other vertices using Dijkstra's Algorithm. It doesn't work on negative
 * weights.
 * @param graph the Graph on which we are performing our shortest path algorithm
 * @param src node from which we calculate minimum distances to all other vertices in the graph
*/
void Dijkstra(const Graph &graph, int src) {
    int V = graph.vertexNum;
    int mdist[V];  // Stores updated distances to vertex
    bool vset[V];  // vset[i] is true if the vertex i included
    // in the shortest path tree

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

/** Main function */
int main() {
    int V, E, gsrc;
    int src, dst, weight;
    std::cout << "Enter number of vertices: ";
    std::cin >> V;
    std::cout << "Enter number of edges: ";
    std::cin >> E;
    Graph G(V);
    for (int i = 0; i < E; i++) {
        std::cout << "\nEdge " << i + 1 << "\nEnter source: ";
        std::cin >> src;
        std::cout << "Enter destination: ";
        std::cin >> dst;
        std::cout << "Enter weight: ";
        std::cin >> weight;

        // makes sure source and destination are in the proper bounds.
        if (src >= 0 && src < V && dst >= 0 && dst < V) {
            G.addEdge(src, dst, weight);
        } else {
            std::cout << "source and/or destination out of bounds" << std::endl;
            i--;
            continue;
        }
    }
    std::cout << "\nEnter source:";
    std::cin >> gsrc;
    Dijkstra(G, gsrc);
    return 0;
}
