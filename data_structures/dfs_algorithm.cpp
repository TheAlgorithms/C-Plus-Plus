#include <cassert>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/**
 * @brief This class represents a simple undirected graph and provides a
 * Depth-First Search (DFS) algorithm.
 *
 * The problem involves traversing an undirected graph using the Depth-First
 * Search algorithm. Given a graph with a certain number of vertices and edges,
 * the DFS algorithm explores the vertices in a way that prioritizes visiting
 * unexplored neighbors, backtracking only when necessary.
 *
 * @details The Depth-First Search (DFS) algorithm is a recursive or iterative
 * algorithm used to explore a graph's vertices and edges. Starting from a
 * specific vertex, the algorithm visits the vertex and then recursively
 * explores its unvisited neighbors, backtracking only when no further
 * unexplored neighbors are present. This process ensures that all vertices
 * connected to the starting vertex are visited.
 */
class Graph {
 public:
    int vertices;
    vector<vector<int>> adjList;

    /**
     * @brief Construct a new Graph object with the given number of vertices.
     *
     * @param v Number of vertices in the graph.
     */
    Graph(int v) : vertices(v), adjList(v) {}

    /**
     * @brief Add an edge between two vertices in the graph.
     *
     * @param v The first vertex.
     * @param w The second vertex.
     */
    void addEdge(int v, int w) { adjList[v].push_back(w); }

    /**
     * @brief Perform Depth-First Search (DFS) starting from the given vertex.
     *
     * @param start The starting vertex for DFS.
     *
     * @details The DFS algorithm starts from the specified vertex, explores
     * each connected vertex, and recursively traverses the unvisited neighbors.
     * The algorithm maintains a stack to keep track of the vertices to visit,
     * ensuring a systematic exploration of the graph.
     */
    void DFS(int start) {
        // Check the validity of the starting vertex
        if (start < 0 || start >= vertices) {
            cerr << "Invalid starting vertex" << endl;
            return;
        }

        vector<bool> visited(vertices, false);
        stack<int> s;

        s.push(start);

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited[current]) {
                cout << current << " ";
                visited[current] = true;
            }

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
};

void testDFS() {
    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 4);

    cout << "Test Case 1: Depth-First Traversal starting from vertex 0:\n";
    g1.DFS(0);
    Graph g2(3);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);

    cout << "\nTest Case 2: Invalid starting vertex (expect error message):\n";
    g2.DFS(5);
    Graph g3(0);

    cout << "\nTest Case 3: Depth-First Traversal on an empty graph (expect no "
            "output):\n";
    g3.DFS(0);

    Graph g4(1);

    cout << "\nTest Case 4: Depth-First Traversal on a graph with a single "
            "vertex:\n";
    g4.DFS(0);

    Graph g5(7);
    g5.addEdge(0, 1);
    g5.addEdge(0, 2);
    g5.addEdge(1, 3);
    g5.addEdge(2, 4);
    g5.addEdge(5, 6);

    cout << "\nTest Case 5: Depth-First Traversal on a graph with disconnected "
            "components starting from vertex 0:\n";
    g5.DFS(0);
}

int main() {
    testDFS();

    return 0;
}
