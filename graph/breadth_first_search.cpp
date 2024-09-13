/**
 *
 * \file
 * \brief [Breadth First Search Algorithm
 * (Breadth First Search)](https://en.wikipedia.org/wiki/Breadth-first_search)
 *
 * \author [Ayaan Khan](https://github.com/ayaankhan98)
 * \author [Aman Kumar Pandey](https://github.com/gpamangkp)
 *
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
 * We maintain a bool array or a vector to keep track of the vertices
 * which we have visited so that we do not traverse the visited vertices
 * again and again and eventually fall into an infinite loop. Along with this
 * boolen array we use a Queue.
 *
 * 1. First we mark the start vertex as visited.
 * 2. Push this visited vertex in the Queue.
 * 3. while the queue is not empty we repeat the following steps
 *
 *      1. Take out an element from the front of queue
 *      2. Explore the adjacency list of this vertex
 *         if element in the adjacency list is not visited then we
 *         push that element into the queue and mark this as visited
 *
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>

/**
 * \namespace graph
 * \brief Graph algorithms
 */
namespace graph {
/* Class Graph definition */
template <typename T>
class Graph {
    /**
     *  adjacency_list maps every vertex to the list of its neighbours in the
     * order in which they are added.
     */
    std::map<T, std::list<T> > adjacency_list;

 public:
    Graph() = default;
    ;
    void add_edge(T u, T v, bool bidir = true) {
        /**
         *  add_edge(u,v,bidir) is used to add an edge between node u and
         * node v by default , bidir is made true , i.e graph is
         * bidirectional . It means if edge(u,v) is added then u-->v  and
         * v-->u both edges exist.
         *
         *  to make the graph unidirectional pass the third parameter of
         * add_edge as false which will
         */
        adjacency_list[u].push_back(v);  // u-->v edge added
        if (bidir == true) {
            // if graph is bidirectional
            adjacency_list[v].push_back(u);  // v-->u edge added
        }
    }

    /**
     *  this function performs the breadth first search on graph and return a
     *  mapping which maps the nodes to a boolean value representing whether the
     *  node was traversed or not.
     */
    std::map<T, bool> breadth_first_search(T src) {
        /// mapping to keep track of all visited nodes
        std::map<T, bool> visited;
        /// initialise every possible vertex to map to false
        /// initially none of the vertices are unvisited
        for (auto const &adjlist : adjacency_list) {
            visited[adjlist.first] = false;
            for (auto const &node : adjacency_list[adjlist.first]) {
                visited[node] = false;
            }
        }

        /// queue to store the nodes which are yet to be traversed
        std::queue<T> tracker;

        /// push the source vertex to queue to begin traversing
        tracker.push(src);
        /// mark the source vertex as visited
        visited[src] = true;
        while (!tracker.empty()) {
            /// traverse the graph till no connected vertex are left
            /// extract a node from queue for further traversal
            T node = tracker.front();
            /// remove the node from the queue
            tracker.pop();
            for (T const &neighbour : adjacency_list[node]) {
                /// check every vertex connected to the node which are still
                /// unvisited
                if (!visited[neighbour]) {
                    /// if the neighbour is unvisited , push it into the queue
                    tracker.push(neighbour);
                    /// mark the neighbour as visited
                    visited[neighbour] = true;
                }
            }
        }
        return visited;
    }
};
/* Class definition ends */
}  // namespace graph

/** Test function */
static void tests() {
    /// Test 1 Begin
    graph::Graph<int> g;
    std::map<int, bool> correct_result;
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    correct_result[0] = true;
    correct_result[1] = true;
    correct_result[2] = true;
    correct_result[3] = true;

    std::map<int, bool> returned_result = g.breadth_first_search(2);

    assert(returned_result == correct_result);
    std::cout << "Test 1 Passed..." << std::endl;

    /// Test 2 Begin
    returned_result = g.breadth_first_search(0);

    assert(returned_result == correct_result);
    std::cout << "Test 2 Passed..." << std::endl;

    /// Test 3 Begins
    graph::Graph<std::string> g2;

    g2.add_edge("Gorakhpur", "Lucknow", false);
    g2.add_edge("Gorakhpur", "Kanpur", false);
    g2.add_edge("Lucknow", "Agra", false);
    g2.add_edge("Kanpur", "Agra", false);
    g2.add_edge("Lucknow", "Prayagraj", false);
    g2.add_edge("Agra", "Noida", false);

    std::map<std::string, bool> correct_res;
    std::map<std::string, bool> returned_res =
        g2.breadth_first_search("Kanpur");
    correct_res["Gorakhpur"] = false;
    correct_res["Lucknow"] = false;
    correct_res["Kanpur"] = true;
    correct_res["Agra"] = true;
    correct_res["Prayagraj"] = false;
    correct_res["Noida"] = true;
    assert(correct_res == returned_res);
    std::cout << "Test 3 Passed..." << std::endl;
}

/** Main function */
int main() {
    tests();
    size_t edges = 0;
    std::cout << "Enter the number of edges: ";
    std::cin >> edges;

    graph::Graph<int> g;

    std::cout << "Enter space-separated pairs of vertices that form edges: "
              << std::endl;
    while (edges--) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    g.breadth_first_search(0);
    return 0;
}
