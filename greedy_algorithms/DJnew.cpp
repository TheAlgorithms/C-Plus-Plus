/**
 * @file
 * @brief Implementation of Djikstra's Algorithm
 * @details
 * Dijkstra's algorithm is an algorithm for finding the shortest paths between nodes in a graph using its neighbors
 * description containing links, references,
 * math equations, etc.
 * @author [Aryan Talekar](https://github.com/aryantalekar20)
 */

#include <iostream>
#include <vector>
#include <set>

/**
 * @namespace greedy_algorithms
 */
namespace greedy_algorithms {

    struct Edge {
        int src, dest, weight;

        Edge(int _src, int _dest, int _weight) {
            src = _src;
            dest = _dest;
            weight = _weight;
        }
    };

/**
 * @brief Graph Implementation
 */
    class Graph {
    public:
        int numVertices;
        std::vector<std::vector<std::pair<int, int>>> adjList;
        // e.g. 0: {1, 12}, {2, 4} -> the weight from vertex 0 to 1 is 12
        //                        and the weight from vertex 0 to 2 is 4

        Graph(const std::vector<Edge> &edges, int vertices) {
            numVertices = vertices;

            adjList.resize(vertices);

            for (auto &edge : edges) {
                adjList[edge.src].push_back(std::make_pair(edge.dest, edge.weight));
            }
        }
    };

/**
 * @brief Function Documentation
 * Q is a set of not visited nodes
 * Uses Q to find the list of nodes
 *
 */
    std::vector<int> dijkstra(const Graph &graph, int src) {
        std::set<int> Q; // not yet visited vertices
        std::vector<int> distance;
        distance.resize(graph.numVertices);
        std::vector<int> prev;
        prev.resize(graph.numVertices);

        for (int v = 0; v < distance.size(); v++) {
            distance[v] = 99999;
            prev[v] = -1;
            Q.insert(v);
        }
        distance[src] = 0;

        while (!Q.empty()) {
            int u = *Q.begin();
            for (int i : Q) {
                //check if distance is greater than...
                if (distance[i] < distance[u]) { // checks the distance instead of vertex
                    u = i;
                }
            }
            Q.erase(u);

            std::vector<std::pair<int, int>> neighbors = graph.adjList[u];
            for (std::pair<int, int> n : neighbors) {
                //check if it is in Q
                if (Q.find(n.first) != Q.end()) {
                    if (distance[u] + n.second < distance[n.first]) {
                        distance[n.first] = distance[u] + n.second;
                        prev[n.first] = u;
                    }
                }
            }
        }

        return distance;
    }

/**
 * @brief Self-test implementations
 * @returns void
 */

    static void test() {
        std::vector<Edge> edges1 =
                {
                    {0,0, 1}, {0,1, 2}, {1,2, 0}, {1,2, 1}, {2,3, 2}, {3,4, 5}, {3,5, 4}
                };
        Graph obj1(edges1 , 6);
        std::vector<int> test1Key{ 0,2,2,4,9,8};
        bool result = std::equal(dijkstra(obj1,0).begin(), dijkstra(obj1,0).end(), test1Key.begin());
        if (result)
            std::cout << "passed";
        //0 2 2 4 9 8

        std::cout<<std::endl;
        std::vector<Edge> edges2 =
                {
                        {0,1, 3}, {1,2, 5}, {2,3, 3}, {2,3, 6}, {3,4, 2}, {4,3, 4}, {4,5, 3}
                };
        Graph obj2(edges2, 6);
        //0 3 8 11 13 16
        std::vector<int> test2Key{0,3,8,11,13,16};
        bool result2 = std::equal(dijkstra(obj2,0).begin(), dijkstra(obj2,0).end(), test2Key.begin());
        if (result2)
            std::cout << "passed";
        std::cout<<std::endl;
        //test 3
        std::vector<Edge> edges3 =
                {
                        {0,1, 4}, {1,2, 6}, {2,3, 3}, {2,5, 6}, {3,4, 2}, {4,2, 2}, {4,4, 4}
                };
        Graph obj3(edges3 , 6);
        std::vector<int> test3Key{ 0, 4, 10, 13, 15, 16};
        //0 4 10 13 15 16
        bool result3 = std::equal(dijkstra(obj3,0).begin(), dijkstra(obj3,0).end(), test3Key.begin());
        if (result3)
            std::cout << "passed" ;

    }
}
/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main() {
    greedy_algorithms::test();  // run self-test implementations
    // code here
    return 0;
}