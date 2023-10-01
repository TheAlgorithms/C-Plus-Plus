#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX; // Represents infinity for unreachable vertices

// Function to find the Minimum Bottleneck Spanning Tree (MBST) using Floyd-Warshall
vector<vector<int>> findMBST(vector<vector<int>>& graph, int n) {
    // Initialize the MBST matrix with infinity
    vector<vector<int>> mbst(n, vector<int>(n, INF));

    // Initialize the diagonal of the MBST matrix with zeros
    for (int i = 0; i < n; i++) {
        mbst[i][i] = 0;
    }

    // Compute all-pairs shortest paths using Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][j] > min(graph[i][k], graph[k][j])) {
                    graph[i][j] = min(graph[i][k], graph[k][j]);
                    mbst[i][j] = k; // Update the MBST matrix
                }
            }
        }
    }

    return mbst;
}

int main() {
    int n, m; // Number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;

    // Initialize the graph adjacency matrix with maximum possible distances
    vector<vector<int>> graph(n, vector<int>(n, INF));

    for (int i = 0; i < m; i++) {
        int src, dest, weight;
        cout << "Enter the source for edge " << i + 1 << ": ";
        cin >> src;
        cout << "Enter the destination for edge " << i + 1 << ": ";
        cin >> dest;
        cout << "Enter the weight for edge " << i + 1 << ": ";
        cin >> weight;
        // Set the edge weight in the graph adjacency matrix
        graph[src][dest] = weight;
        graph[dest][src] = weight; // Assuming an undirected graph
    }

    // Find the Minimum Bottleneck Spanning Tree (MBST)
    vector<vector<int>> mbst = findMBST(graph, n);

    // Display the MBST matrix
    cout << "Minimum Bottleneck Spanning Tree (MBST) Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mbst[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << mbst[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
