/******************************************************************************
 * @file
 * @brief Implementation of the [Dial's
 *Algorithm](https://www.codingninjas.com/studio/library/dials-algorithm)
 * @details
 * Dial's algorithm is a variation of Dijkstra's algorithm designed to optimize
 * the process of finding the shortest paths in a graph. It achieves this
 * optimization by grouping nodes into buckets based on their current shortest
 * path estimates. This strategy reduces the number of nodes processed in each
 * iteration, particularly beneficial when dealing with graphs where the range
 * of edge weights is small.
 *
 * ## Implementation
 *
 * ### Step 1 (Initialization)
 * Initialize a set of buckets, where each bucket i Begin with the source node s
 * and set its shortest path estimate to 0.
 *
 * ### Step 2 (Bucket Assignment)
 * For each node v adjacent to s, add it to the bucket corresponding to its
 * distance from s.
 *
 * While there are non-empty buckets:
 *   Find the non-empty bucket with the smallest index i.
 *   Remove the node u with the smallest shortest path estimate from the bucket.
 *   For each node v adjacent to u:
 *     If the shortest path estimate for v is greater than the new estimate via
 *     u, update v's estimate and move it to the corresponding bucket.
 *
 * ### Step 3 (Result Retrieval)
 * Return the shortest path estimates for all nodes.
 *
 * The time complexity of the above implementation is O(vertices*W). Here
 *vertices is the number of vertices in the graph and W is the maximum weight of
 *the edge.
 *
 * ## Benefits of Dial's Algorithm
 * Efficiency Improvement: By processing only nodes with the smallest path
 * estimates in each iteration, Dial's algorithm reduces the computational
 *overhead associated with scanning all nodes.
 *
 * Speed Enhancement: Particularly advantageous when dealing with graphs where
 * the range of edge weights is small, as it minimizes unnecessary processing.
 *
 * ## Implementation Considerations
 * Data Structures: Efficient implementation requires appropriate data
 *structures for managing buckets and shortest path estimates.
 *
 * Bucket Indexing: Efficiently locating the bucket with the smallest index is
 * crucial for algorithm performance.
 *
 * ## Example Use Cases
 * Network Routing: Optimizing route calculation in computer networks.
 * Transportation Networks: Finding the shortest path in transportation networks
 * for navigation or logistics optimization.
 *
 * ## References
 * Dial, R. B. (1970). The Implementation of Dijkstra's Algorithm. Journal of
 * the ACM (JACM), 17(1), 193-197.
 *
 * ## Further Reading
 * Dijkstra, E. W. (1959). A note on two problems in connexion with graphs.
 * Numerische mathematik, 1(1), 269-271.
 *
 * Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009).
 * Introduction to Algorithms (3rd ed.). MIT Press.
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 *
 *******************************************************************************/

#include <iostream>  /// for IO operations
#include <list>      /// for std::lists
#include <vector>    /// for std::vector

// Define infinity as the maximum value a 32-bit signed integer can hold
constexpr int64_t INF = 0x3f3f3f3f;

namespace greedy_algorithms {

namespace dijkstra {

namespace dials_algorithm {

// This class represents a directed graph using
// adjacency list representation
class Graph {
    int64_t vertices;  // No. of vertices
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    std::list<std::pair<int64_t, int64_t>> *adj;  // Adjacency list

 public:
    // Constructor to initialize the graph with vertices
    explicit Graph(int64_t vertices)
        : vertices(vertices),
          adj(new std::list<std::pair<int64_t, int64_t>>[vertices]) {}

    // function to add an edge to graph
    void addEdge(int64_t u, int64_t v, int64_t weight);

    // Function to find the shortest paths from a source vertex
    std::vector<int64_t> shortestPath(int64_t s, int64_t Weight);
};

/**
 * @brief Function to add an edge between vertices u and v with weight w
 *
 * @param u if the source (starting point) of the weighted graph.
 * @param v is the maximum weight of an edge
 * @param weight is the weight of the newly added edge between points u and v
 * @returns a vector with all the shortest paths from source
 */
void Graph::addEdge(int64_t u, int64_t v, int64_t weight) {
    // Add v to the list of adjacent vertices of u with weight w
    adj[u].emplace_back(std::make_pair(v, weight));

    // Add u to the list of adjacent vertices of v with weight w
    adj[v].emplace_back(std::make_pair(u, weight));
}

/**
 * @brief Utility function that calculates
 * the shortest paths from source to all the vertices.
 *
 * @param source if the source (starting point) of the weighted graph.
 * @param Weight is the maximum weight of an edge
 * @returns a vector with all the shortest paths from source
 */
std::vector<int64_t> Graph::shortestPath(int64_t source, int64_t Weight) {
    /* With each distance, iterator to that vertex in
    its bucket is stored so that vertex can be deleted
    in O(1) at time of updation. So
    dist[i].first = distance of ith vertex from source vertex
    dist[i].second = iterator to vertex i in bucket number */
    std::vector<std::pair<int64_t, std::list<int64_t>::iterator>> dist(
        vertices);

    // Initialize all distances as infinite (INF)
    for (int64_t iterator = 0; iterator < vertices; iterator++) {
        dist[iterator].first = INF;
    }

    // Create buckets Vector B.
    // each representing a range of distances
    std::vector<std::list<int64_t>> Buckets(Weight * vertices + 1);

    // Add the source vertex to the bucket representing distance 0
    Buckets[0].emplace_back(source);
    // Set the distance of the source vertex to 0
    dist[source].first = 0;

    // Loop until all buckets are empty
    int64_t idx = 0;
    while (true) {
        // Go sequentially through buckets till one non-empty
        // bucket is found
        while (Buckets[idx].size() == 0 && idx < Weight * vertices) {
            idx++;
        }

        // If all buckets are empty, exit the loop.
        if (idx == Weight * vertices) {
            break;
        }

        // Extract the top vertex from the non-empty bucket
        int64_t u = Buckets[idx].front();
        Buckets[idx].pop_front();

        // Process all adjacents of extracted vertex 'u' and
        // update their distanced if required.
        for (auto iterator = adj[u].begin(); iterator != adj[u].end();
             ++iterator) {
            int64_t adj_vertex = (*iterator).first;  // Adjacent vertex
            int64_t temp_weight =
                (*iterator).second;  // Weight of the edge (u, v)

            int64_t distance_u =
                dist[u].first;  // Distance of vertex u from source
            int64_t distance_v =
                dist[adj_vertex].first;  // Distance of vertex v from source

            // If there is shorted path to v through u.
            if (distance_v > distance_u + temp_weight) {
                // If dv is not INF then it must be in B[dv]
                // bucket, so erase its entry using iterator
                // in O(1)
                if (distance_v != INF) {
                    Buckets[distance_v].erase(dist[adj_vertex].second);
                }

                // Update the distance of vertex v
                dist[adj_vertex].first = distance_u + temp_weight;
                distance_v = dist[adj_vertex].first;

                // Add vertex v to the bucket representing its updated distance
                Buckets[distance_v].push_front(adj_vertex);

                // Update the iterator of vertex v in its bucket
                dist[adj_vertex].second = Buckets[distance_v].begin();
            }
        }
    }

    // Store the shortest distances in a vector and return it
    std::vector<int64_t> result;
    for (int64_t iterator = 0; iterator < vertices; ++iterator) {
        result.emplace_back(dist[iterator].first);
    }
    return result;
}
        }  // namespace dials_algorithm
    }  // namespace dijkstra
}  // namespace greedy_algorithms

/**
 * @brief Self-test implementations for the function to Store the shortest
 * distances in a vector and return it.
 * @returns void
 */
static void test_basic_case() {
    int64_t vertices = 5;
    greedy_algorithms::dijkstra::dials_algorithm::Graph g(vertices);

    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 8);
    g.addEdge(3, 4, 7);

    std::vector<int64_t> expected_result = {0, 8, 5, 9, 16};
    std::vector<int64_t> derived_result = g.shortestPath(0, 10);

    std::cout << "Basic Case Test: ";
    if (std::equal(expected_result.begin(), expected_result.end(),
                   derived_result.begin())) {
        std::cout << "Passed!" << std::endl;
    } else {
        std::cout << "Failed!" << std::endl;
    }
}

/**
 * @brief Self-test implementations for the function to test the algorithm with
 * a disconnected graph.
 * @returns void
 */
static void test_disconnected_graph() {
    int64_t vertices = 6;
    greedy_algorithms::dijkstra::dials_algorithm::Graph g(vertices);

    g.addEdge(0, 1, 5);
    g.addEdge(1, 2, 3);
    g.addEdge(3, 4, 6);
    g.addEdge(4, 5, 2);

    std::vector<int64_t> expected_result = {0, 5, 8, INF, INF, INF};
    std::vector<int64_t> derived_result = g.shortestPath(0, 10);

    std::cout << "Disconnected Graph Test: ";
    if (std::equal(expected_result.begin(), expected_result.end(),
                   derived_result.begin())) {
        std::cout << "Passed!" << std::endl;
    } else {
        std::cout << "Failed!" << std::endl;
    }
}

/**
 * @brief Self-test implementations for the function to test the algorithm with
 * negative weight edges.
 * @returns void
 */
static void test_negative_weight_edges() {
    int64_t vertices = 4;
    greedy_algorithms::dijkstra::dials_algorithm::Graph g(vertices);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, -3);
    g.addEdge(2, 3, 2);
    g.addEdge(1, 3, 6);

    std::vector<int64_t> expected_result = {0, 4, 1, 10};
    std::vector<int64_t> derived_result = g.shortestPath(0, 10);

    std::cout << "Negative Weight Edges Test: ";
    if (std::equal(expected_result.begin(), expected_result.end(),
                   derived_result.begin())) {
        std::cout << "Passed!" << std::endl;
    } else {
        std::cout << "Failed!" << std::endl;
    }
}

/**
 * @brief Self-test implementations for the function to test the algorithm with
 * single vertex graph
 * @returns void
 */
static void test_single_vertex_graph() {
    int64_t vertices = 1;
    greedy_algorithms::dijkstra::dials_algorithm::Graph g(vertices);

    std::vector<int64_t> expected_result = {0};
    std::vector<int64_t> derived_result = g.shortestPath(0, 10);

    std::cout << "Single verticesertex Graph Test: ";
    if (std::equal(expected_result.begin(), expected_result.end(),
                   derived_result.begin())) {
        std::cout << "Passed!" << std::endl;
    } else {
        std::cout << "Failed!" << std::endl;
    }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test_basic_case();
    test_disconnected_graph();
    test_negative_weight_edges();
    test_single_vertex_graph();
    return 0;
}
