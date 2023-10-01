#include <algorithm>
#include <iostream>
#include <vector>

/*
 *
 * @aurthor - Prabhat-Kumar-42
 * @github - https://github.com/Prabhat-Kumar-42
 *
 * Problem :
 *
 * Given an adjacency list of a graph with vertices = v, having
 * 0 based indexing. Find all Articulation Points and Articulation
 * Bridge Present in Graph
 *
 * Articulation Point : vertex whcih when removed increases the number of
 * connected component in graph.
 *
 * Articulation Bridge : edge which when removed increases the number of
 * connected component in graph.
 *
 * eg : Given graph with vertices = 5 and
 *     adj list is :  vertex -> neighbours (Assuming all edges are
 * bidirectional) 0 -> 1, 2 1 -> 2 2 -> 3 3 -> 4
 *
 *      Graph is :
 *
 *                0-------1
 *                |      /
 *                |     /
 *                |    /
 *                |   /
 *                |  /       4
 *                | /        |
 *                |/         |
 *                2----------3
 *
 *     current connected component = 1
 *
 *  -> Articulation Points : 2 , 3
 *     Explanation :
 *
 *             -> When removing 2, graph changes to below and connected
 * components increases from 1 to 2.
 *
 *                0-------1
 *                |      /
 *                |     /
 *                |    /
 *                |   /
 *                |  /       4
 *                | /        |
 *                |/         |
 *                           3
 *
 *
 *              -> When removing 3, graph changes to below and connected
 * components increases from 1 to 2.
 *
 *                0-------1
 *                |      /
 *                |     /
 *                |    /
 *                |   /
 *                |  /       4
 *                | /
 *                |/
 *                2
 *
 *
 *  -> Articulation Bridges: edge : 2-3, edge: 3-4
 *     Explanation :
 *
 *             -> When removing edge : 2-3, graph changes to below and connected
 * components increases from 1 to 2.
 *
 *                0-------1
 *                |      /
 *                |     /
 *                |    /
 *                |   /
 *                |  /       4
 *                | /        |
 *                |/         |
 *                2          3
 *
 *
 *              -> When removing edge : 3-4, graph changes to below and
 * connected components increases from 1 to 2.
 *
 *                0-------1
 *                |      /
 *                |     /
 *                |    /
 *                |   /
 *                |  /       4
 *                | /
 *                |/
 *                2----------3
 *
 */
class ArticulationPointsAndBridges {
 public:
    // Edge used to store bridges
    struct Edge {
        int u, v;
        Edge(int u, int v) : u(u), v(v) {}
    };

 private:
    int V;                              // Number of vertices
    std::vector<std::vector<int>> adj;  // Adjacency list

    int time = 0;
    std::vector<bool> visited;  // To track visited vertices during traversal
    std::vector<int> disc;      // Discovery time of vertices
    std::vector<int> low;  // Lowest discovery time reachable from the vertex
    std::vector<int>
        parent;  // Parent vertex in DFS traversal, initialized to -1
    std::vector<bool> articulationPoints;  // To store articulation points

    std::vector<Edge> bridges;  // Vector to store bridges

 public:
    /**
     * Constructor
     *
     * @param v number of vertex in graph
     */
    ArticulationPointsAndBridges(int v) : V(v) {
        adj.resize(v);
        visited.assign(v, false);
        disc.resize(v);
        low.resize(v);
        parent.assign(v, -1);
        articulationPoints.assign(v, false);
    }

    /**
     * function addEdge - Add an edge between vertices u and v
     * @param u - source vertex of graph that needs to be conneted to v
     * @param v - end vertex f graph that needs to be connected to u
     */
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Find articulation points and bridges in the graph
    void findArticulationPointsAndBridges() {
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                findArticulationPointsAndBridges(i);
            }
        }
    }

    /*
     * Helper function to perform DFS and find articulation points and bridges
     *
     * @param u source vertex
     */
    void findArticulationPointsAndBridges(int u) {
        int children = 0;
        visited[u] = true;
        disc[u] = low[u] = ++time;

        for (int v : adj[u]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                findArticulationPointsAndBridges(v);
                low[u] = std::min(low[u], low[v]);

                if (parent[u] == -1 && children > 1) {
                    articulationPoints[u] = true;
                }
                if (parent[u] != -1 && low[v] >= disc[u]) {
                    articulationPoints[u] = true;
                }

                if (low[v] > disc[u]) {
                    bridges.emplace_back(u, v);
                }
            } else if (v != parent[u]) {
                low[u] = std::min(low[u], disc[v]);
            }
        }
    }

    /* Check if a vertex is an articulation point
     *
     * @param u source vertex
     */
    bool isArticulationPoint(int u) { return articulationPoints[u]; }

    // Get an ArrayList of bridges in the graph
    std::vector<Edge> getBridges() { return bridges; }
    // Get an ArrayList of articulation points in the graph
    std::vector<int> getArticulationPoints() {
        std::vector<int> articulationPointsList;
        for (int i = 0; i < V; i++) {
            if (articulationPoints[i]) {
                articulationPointsList.push_back(i);
            }
        }
        return articulationPointsList;
    }
};

// main for test check
int main() {
    int V = 5;
    ArticulationPointsAndBridges graph(V);

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.findArticulationPointsAndBridges();

    std::cout << "Articulation Points:" << std::endl;
    std::vector<int> articulationPoints = graph.getArticulationPoints();
    for (int point : articulationPoints) {
        std::cout << point << " ";
    }
    std::cout << std::endl;

    std::cout << "\nBridges:" << std::endl;
    std::vector<ArticulationPointsAndBridges::Edge> bridges =
        graph.getBridges();
    for (const auto &bridge : bridges) {
        std::cout << "Bridge: " << bridge.u << " - " << bridge.v << std::endl;
    }

    return 0;
}
