/**
 *
 * \file
 * \brief [Breadth First Search Algorithm
 * (Breadth First Search)](https://en.wikipedia.org/wiki/Breadth-first_search)
 *
 * \author [Ayaan Khan](http://github.com/ayaankhan98)
 *
 * \details
 * Breadth First Search also quoted as BFS is a Graph Traversal Algorithm.
 * Time Complexity O(|V| + |E|) where V are the number of vertices and E
 * are the number of edges in the graph.
 *
 * Applications of Breadth First Search are
 *
 * 1. Finding shortest path between two vertices say u and v, with path
 *    length measured by number of edges (an advantage over depth first
 *    search algorithm)
 * 2. Ford-Fulkerson Method for computing the maximum flow in a flow network.
 * 3. Testing bipartiteness of a graph.
 * 4. Cheney's Algorithm, Copying garbage collection.
 *
 * And there are many more...
 *
 * <h4>working</h4>
 * In the implementation below we first created a graph using the adjacency
 * list representation of graph.
 * Breadth First Search Works as follows
 * it requires a vertex as a start vertex, Start vertex is that vertex
 * from where you want to start traversing the graph.
 * we maintain a bool array or a vector to keep track of the vertices
 * which we have visited so that we do not traverse the visited vertices
 * again and again and eventually fall into an infinite loop. Along with this
 * boolen array we use a Queue.
 *
 * 1. First we mark the start vertex as visited.
 * 2. Push this visited vertex in the Queue.
 * 3. while the queue is not empty we repeat the following steps
 *
 *      1. Take out an element from the front of queue
 *      2. start exploring the adjacency list of this vertex
 *         if element in the adjacency list is not visited then we
 *         push that element into the queue and mark this as visited
 *
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

/**
 * \namespace graph
 * \brief Graph algorithms
 */
namespace graph {
/**
 * \brief
 * Adds and edge between two vertices of graph say u and v in this
 * case.
 *
 * @param adj Adjacency list representation of graph
 * @param u first vertex
 * @param v second vertex
 *
 */
void addEdge(std::vector<std::vector<int>> *adj, int u, int v) {
    /**
     * Here we are considering directed graph that's the
     * reason we are adding v to the adjacency list representation of u
     * but not adding u to the adjacency list representation of v
     *
     * in case of a un-directed graph you can un comment the statement below.
     */
    (*adj)[u - 1].push_back(v - 1);
    // adj[v - 1].push_back(u -1);
}

/**
 * \brief
 * Function performs the breadth first search algorithm over the graph
 *
 * @param adj Adjacency list representation of graph
 * @param start vertex from where traversing starts
 *
 */
std::vector<int> beadth_first_search(const std::vector<std::vector<int>> &adj,
                                     int start) {
    size_t vertices = adj.size();

    std::vector<int> result;

    /// vector to keep track of visited vertices
    std::vector<bool> visited(vertices, 0);

    std::queue<int> tracker;
    /// marking the start vertex as visited
    visited[start] = true;
    tracker.push(start);
    while (!tracker.empty()) {
        size_t vertex = tracker.front();
        tracker.pop();
        result.push_back(vertex + 1);
        for (auto x : adj[vertex]) {
            /// if the vertex is not visited then mark this as visited
            /// and push it to the queue
            if (!visited[x]) {
                visited[x] = true;
                tracker.push(x);
            }
        }
    }
    return result;
}
}  // namespace graph

void tests() {
    std::cout << "Initiating Tests" << std::endl;

    /// Test 1 Begin
    std::vector<std::vector<int>> graphData(4, std::vector<int>());
    graph::addEdge(&graphData, 1, 2);
    graph::addEdge(&graphData, 1, 3);
    graph::addEdge(&graphData, 2, 3);
    graph::addEdge(&graphData, 3, 1);
    graph::addEdge(&graphData, 3, 4);
    graph::addEdge(&graphData, 4, 4);

    std::vector<int> returnedResult = graph::beadth_first_search(graphData, 2);
    std::vector<int> correctResult = {3, 1, 4, 2};

    assert(std::equal(correctResult.begin(), correctResult.end(),
                      returnedResult.begin()));
    std::cout << "Test 1 Passed..." << std::endl;

    /// Test 2 Begin
    /// clear data from previous test
    returnedResult.clear();
    correctResult.clear();

    returnedResult = graph::beadth_first_search(graphData, 0);
    correctResult = {1, 2, 3, 4};

    assert(std::equal(correctResult.begin(), correctResult.end(),
                      returnedResult.begin()));
    std::cout << "Test 2 Passed..." << std::endl;

    /// Test 3 Begins
    /// clear data from previous test
    graphData.clear();
    returnedResult.clear();
    correctResult.clear();

    graphData.resize(6);
    graph::addEdge(&graphData, 1, 2);
    graph::addEdge(&graphData, 1, 3);
    graph::addEdge(&graphData, 2, 4);
    graph::addEdge(&graphData, 3, 4);
    graph::addEdge(&graphData, 2, 5);
    graph::addEdge(&graphData, 4, 6);

    returnedResult = graph::beadth_first_search(graphData, 0);
    correctResult = {1, 2, 3, 4, 5, 6};

    assert(std::equal(correctResult.begin(), correctResult.end(),
                      returnedResult.begin()));
    std::cout << "Test 3 Passed..." << std::endl;
}

/** Main function */
int main() {
    /// running predefined test cases
    tests();

    size_t vertices, edges;
    std::cout << "Enter the number of vertices : ";
    std::cin >> vertices;
    std::cout << "Enter the number of edges : ";
    std::cin >> edges;

    /// creating a graph
    std::vector<std::vector<int>> adj(vertices, std::vector<int>());

    /// taking input for edges
    std::cout << "Enter vertices in pair which have edges between them : "
              << std::endl;
    while (edges--) {
        int u, v;
        std::cin >> u >> v;
        graph::addEdge(&adj, u, v);
    }

    /// running Breadth First Search Algorithm on the graph
    graph::beadth_first_search(adj, 0);
    return 0;
}
