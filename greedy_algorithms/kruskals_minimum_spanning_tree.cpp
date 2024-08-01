/**
 * @file
 * @brief [Kruskal's Minimum Spanning Tree](https://www.simplilearn.com/tutorials/data-structure-tutorial/kruskal-algorithm)
 * implementation
 *
 * @details
 * Kruskal’s algorithm is used to find the Minimum Spanning Tree (MST) for a connected weighted graph. 
 * This algorithm sorts all edges by their weight and adds the smallest edge to the MST while avoiding cycles.
 *
 * @author [MeetMendapara09](https://github.com/Meetmendapara09)
 */

#include <iostream>   // for IO operations
#include <vector>     // for std::vector
#include <algorithm>  // for std::sort
#include <array>      // for std::array

using namespace std;

/**
 * @namespace
 * @brief Greedy Algorithms
 */
namespace greedy_algorithms {

/**
 * @struct Edge
 * @brief Represents an edge in the graph
 */
struct Edge {
    int src, dest, weight;
};

/**
 * @class DisjointSet
 * @brief Union-Find data structure with path compression and union by rank
 */
class DisjointSet {
public:
    /**
     * @brief Constructs a DisjointSet with n elements
     * @param n Number of elements
     */
    DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    /**
     * @brief Finds the root of the set containing u with path compression
     * @param u Element to find
     * @returns Root of the set containing u
     */
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    /**
     * @brief Unites the sets containing u and v
     * @param u First element
     * @param v Second element
     */
    void unionSet(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                ++rank[rootU];
            }
        }
    }

private:
    vector<int> parent; // Stores the parent of each element
    vector<int> rank;   // Stores the rank of each set
};

/**
 * @brief Finds and prints the Minimum Spanning Tree (MST) using Kruskal's algorithm
 * @param graph Adjacency matrix representing the graph
 */
void kruskalMST(const array<array<int, 6>, 6> &graph) {
    vector<Edge> edges;

    // Convert adjacency matrix to edge list
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = i + 1; j < graph.size(); ++j) {
            if (graph[i][j] != 99999) {
                edges.push_back({i, j, graph[i][j]});
            }
        }
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.weight < b.weight;
    });

    DisjointSet ds(graph.size());
    vector<Edge> result;

    // Process each edge
    for (const auto &edge : edges) {
        int rootU = ds.find(edge.src);
        int rootV = ds.find(edge.dest);

        if (rootU != rootV) {
            result.push_back(edge);
            ds.unionSet(rootU, rootV);
        }
    }

    // Output the MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto &edge : result) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << "\n";
    }
}

}  // namespace greedy_algorithms

/**
 * @brief Main function to demonstrate Kruskal's MST algorithm
 * @returns 0 on exit
 */
int main() {
    constexpr int INF = 99999;
    int choice;

    cout << "Select input method:\n";
    cout << "1. Static Input\n";
    cout << "2. Dynamic Input\n";
    cout << "Enter your choice (1/2): ";
    cin >> choice;

    array<array<int, 6>, 6> graph;

    if (choice == 1) {
        // Static input
        graph = {{
            {0,        4,        1,        4,        INF,      INF},
            {4,        0,        3,        8,        3,        INF},
            {1,        3,        0,        INF,      1,        INF},
            {4,        8,        INF,      0,        5,        7},
            {INF,      3,        1,        5,        0,        INF},
            {INF,      INF,      INF,      7,        INF,      0}
        }};
    } else if (choice == 2) {
        // Dynamic input
        cout << "Enter the number of vertices (max 6): ";
        int vertices;
        cin >> vertices;

        if (vertices > 6) {
            cerr << "Number of vertices exceeds the maximum allowed (6).\n";
            return 1;
        }

        cout << "Enter the adjacency matrix (use " << INF << " for no connection):\n";
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                cin >> graph[i][j];
            }
        }
    } else {
        cerr << "Invalid choice. Exiting...\n";
        return 1;
    }

    greedy_algorithms::kruskalMST(graph);
    return 0;
}
