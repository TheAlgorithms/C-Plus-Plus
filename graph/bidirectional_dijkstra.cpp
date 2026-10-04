/**
 * @file
 * @brief [Bidirectional Dijkstra Shortest Path Algorithm]
 * (https://www.coursera.org/learn/algorithms-on-graphs/lecture/7ml18/bidirectional-dijkstra)
 *
 * @author [Marinovksy](http://github.com/Marinovsky)
 *
 * @details
 * This is basically the same Dijkstra Algorithm but faster because it goes from
 * the source to the target and from target to the source and stops when
 * finding a vertex settled by both the direct and reverse searches.
 * Here some simulations of it:
 * https://www.youtube.com/watch?v=DINCL5cd_w0&t=24s
 */

#include <algorithm>  /// for min
#include <array>      /// for test edges
#include <cassert>    /// for assert
#include <cstdint>
#include <iostream>  /// for io operations
#include <limits>    /// for variable INF
#include <queue>     /// for the priority_queue of distances
#include <random>    /// for reproducible differential tests
#include <utility>   /// for make_pair function
#include <vector>    /// for store the graph, the distances, and the path

constexpr uint64_t INF = std::numeric_limits<int64_t>::max();

/**
 * @namespace graph
 * @brief Graph Algorithms
 */
namespace graph {
/**
 * @namespace bidirectional_dijkstra
 * @brief Functions for [Bidirectional Dijkstra Shortest Path]
 * (https://www.coursera.org/learn/algorithms-on-graphs/lecture/7ml18/bidirectional-dijkstra)
 * algorithm
 */
namespace bidirectional_dijkstra {
/**
 * @brief Function that add edge between two nodes or vertices of graph
 *
 * @param adj1 adjacency list for the direct search
 * @param adj2 adjacency list for the reverse search
 * @param u any node or vertex of graph
 * @param v any node or vertex of graph
 */
void addEdge(std::vector<std::vector<std::pair<uint64_t, uint64_t>>> *adj1,
             std::vector<std::vector<std::pair<uint64_t, uint64_t>>> *adj2,
             uint64_t u, uint64_t v, uint64_t w) {
    (*adj1)[u - 1].emplace_back(v - 1, w);
    (*adj2)[v - 1].emplace_back(u - 1, w);
    // (*adj)[v - 1].push_back(std::make_pair(u - 1, w));
}
/**
 * @brief This function returns the shortest distance from the source
 * to the target if there is path between vertices 's' and 't'.
 *
 * @param workset_ vertices visited in the search
 * @param distance_ vector of distances from the source to the target and
 * from the target to the source
 *
 */
uint64_t Shortest_Path_Distance(
    const std::vector<uint64_t> &workset_,
    const std::vector<std::vector<uint64_t>> &distance_) {
    uint64_t distance = INF;
    for (uint64_t i : workset_) {
        // Check the bound before adding, including unreachable distances.
        if (distance_[0][i] < distance &&
            distance_[1][i] < distance - distance_[0][i]) {
            distance = distance_[0][i] + distance_[1][i];
        }
    }
    return distance;
}

/**
 * @brief Function runs the dijkstra algorithm for some source vertex and
 * target vertex in the graph and returns the shortest distance of target
 * from the source.
 *
 * @param adj1 input graph
 * @param adj2 input graph reversed
 * @param s source vertex
 * @param t target vertex
 *
 * @return shortest distance in [0, INT64_MAX), or -1 if no path has a
 * representable distance. INT64_MAX is reserved for infinity.
 */
int64_t Bidijkstra(
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> *adj1,
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> *adj2, uint64_t s,
    uint64_t t) {
    /// n denotes the number of vertices in graph
    uint64_t n = adj1->size();

    /// setting all the distances initially to INF
    std::vector<std::vector<uint64_t>> dist(2, std::vector<uint64_t>(n, INF));

    /// creating a a vector of min heap using priority queue
    /// pq[0] contains the min heap for the direct search
    /// pq[1] contains the min heap for the reverse search

    /// first element of pair contains the distance
    /// second element of pair contains the vertex
    std::vector<
        std::priority_queue<std::pair<uint64_t, uint64_t>,
                            std::vector<std::pair<uint64_t, uint64_t>>,
                            std::greater<std::pair<uint64_t, uint64_t>>>>
        pq(2);
    /// vector for store the nodes or vertices in the shortest path
    std::vector<uint64_t> workset;
    /// Each search records its own settled vertices.
    std::vector<std::vector<bool>> visited(2, std::vector<bool>(n));

    /// pushing the source vertex 's' with 0 distance in pq[0] min heap
    pq[0].emplace(0, s);

    /// marking the distance of source as 0
    dist[0][s] = 0;

    /// pushing the target vertex 't' with 0 distance in pq[1] min heap
    pq[1].emplace(0, t);

    /// marking the distance of target as 0
    dist[1][t] = 0;

    while (true) {
        /// direct search

        // If pq[0].size() is equal to zero then the node/ vertex is not
        // reachable from s
        if (pq[0].size() == 0) {
            break;
        }
        /// second element of pair denotes the node / vertex
        uint64_t currentNode = pq[0].top().second;

        /// first element of pair denotes the distance
        uint64_t currentDist = pq[0].top().first;

        pq[0].pop();

        // An older queue entry is not a meeting with the reverse search.
        if (currentDist != dist[0][currentNode]) {
            continue;
        }

        /// for all the reachable vertex from the currently exploring vertex
        /// we will try to minimize the distance
        for (const auto &edge : (*adj1)[currentNode]) {
            /// minimizing distances
            if (edge.second < INF - currentDist &&
                currentDist + edge.second < dist[0][edge.first]) {
                dist[0][edge.first] = currentDist + edge.second;
                pq[0].emplace(dist[0][edge.first], edge.first);
            }
        }
        // store the processed node/ vertex
        workset.push_back(currentNode);

        /// Only a vertex settled in the opposite direction is a meeting.
        if (visited[1][currentNode]) {
            uint64_t distance = Shortest_Path_Distance(workset, dist);
            return distance == INF ? -1 : static_cast<int64_t>(distance);
        }
        visited[0][currentNode] = true;
        /// reversed search

        // If pq[1].size() is equal to zero then the node/ vertex is not
        // reachable from t
        if (pq[1].size() == 0) {
            break;
        }
        /// second element of pair denotes the node / vertex
        currentNode = pq[1].top().second;

        /// first element of pair denotes the distance
        currentDist = pq[1].top().first;

        pq[1].pop();

        if (currentDist != dist[1][currentNode]) {
            continue;
        }

        /// for all the reachable vertex from the currently exploring vertex
        /// we will try to minimize the distance
        for (const auto &edge : (*adj2)[currentNode]) {
            /// minimizing distances
            if (edge.second < INF - currentDist &&
                currentDist + edge.second < dist[1][edge.first]) {
                dist[1][edge.first] = currentDist + edge.second;
                pq[1].emplace(dist[1][edge.first], edge.first);
            }
        }
        // store the processed node/ vertex
        workset.push_back(currentNode);

        /// Only a vertex settled in the opposite direction is a meeting.
        if (visited[0][currentNode]) {
            uint64_t distance = Shortest_Path_Distance(workset, dist);
            return distance == INF ? -1 : static_cast<int64_t>(distance);
        }
        visited[1][currentNode] = true;
    }
    return -1;
}
}  // namespace bidirectional_dijkstra
}  // namespace graph

/**
 * @brief Verify distance range, stale entries, and directed reachability.
 */
static void test_distance_regressions() {
    using adjacency_list =
        std::vector<std::vector<std::pair<uint64_t, uint64_t>>>;
    const auto check = [](uint64_t vertices,
                          const std::vector<std::array<uint64_t, 3>> &edges,
                          uint64_t source, uint64_t target, int64_t expected) {
        adjacency_list forward(vertices), reverse(vertices);
        for (const auto &edge : edges) {
            graph::bidirectional_dijkstra::addEdge(&forward, &reverse, edge[0],
                                                   edge[1], edge[2]);
        }
        assert(graph::bidirectional_dijkstra::Bidijkstra(
                   &forward, &reverse, source - 1, target - 1) == expected);
        assert(graph::bidirectional_dijkstra::Bidijkstra(
                   &reverse, &forward, target - 1, source - 1) == expected);
    };

    check(1, {}, 1, 1, 0);
    check(2, {}, 1, 2, -1);
    check(2, {{1, 2, 0}}, 1, 2, 0);
    check(2, {{1, 2, 7}}, 2, 1, -1);
    check(2, {{1, 2, uint64_t{1} << 31}}, 1, 2, int64_t{1} << 31);
    check(2, {{1, 2, (uint64_t{1} << 32) + 5}}, 1, 2, (int64_t{1} << 32) + 5);
    check(3, {{1, 2, 1500000000}, {2, 3, 1500000000}}, 1, 3, 3000000000);
    check(2, {{1, 2, INF - 1}}, 1, 2, static_cast<int64_t>(INF - 1));
    check(3, {{1, 2, INF - 2}, {2, 3, 1}}, 1, 3, static_cast<int64_t>(INF - 1));
    check(3, {{1, 2, INF - 2}, {2, 3, 2}}, 1, 3, -1);
    check(2, {{1, 2, std::numeric_limits<uint64_t>::max()}, {1, 2, 11}}, 1, 2,
          11);
    check(4, {{1, 2, 0}, {2, 1, 0}, {2, 3, 9}, {1, 3, 20}, {3, 4, 0}}, 1, 4, 9);

    // The obsolete distance 10 must not terminate the forward search.
    check(7,
          {{1, 2, 10},
           {1, 3, 1},
           {3, 2, 1},
           {2, 4, 100},
           {4, 5, 100},
           {5, 6, 100},
           {6, 7, 100}},
          1, 7, 402);
    // Multiple routes and parallel edges must retain the shortest candidate.
    check(4, {{1, 2, 15}, {1, 2, 3}, {2, 4, 8}, {1, 3, 4}, {3, 4, 5}}, 1, 4, 9);
    std::cout << "Distance regressions passed (14 cases in both directions)\n";
}

/**
 * @brief Independent Floyd-Warshall oracle for all representable distances.
 * @param adjacency directed graph with nonnegative edge weights
 * @return all-pairs distances, with INF for unrepresentable or absent paths
 */
static std::vector<std::vector<uint64_t>> reference_distances(
    const std::vector<std::vector<std::pair<uint64_t, uint64_t>>> &adjacency) {
    const auto vertices = adjacency.size();
    std::vector<std::vector<uint64_t>> distances(
        vertices, std::vector<uint64_t>(vertices, INF));
    for (size_t source = 0; source < vertices; ++source) {
        distances[source][source] = 0;
        for (const auto &edge : adjacency[source]) {
            distances[source][edge.first] =
                std::min(distances[source][edge.first], edge.second);
        }
    }
    for (size_t via = 0; via < vertices; ++via) {
        for (size_t source = 0; source < vertices; ++source) {
            for (size_t target = 0; target < vertices; ++target) {
                if (distances[source][via] < INF &&
                    distances[via][target] < INF - distances[source][via]) {
                    distances[source][target] = std::min(
                        distances[source][target],
                        distances[source][via] + distances[via][target]);
                }
            }
        }
    }
    return distances;
}

/**
 * @brief Compare every source/target pair on reproducible directed graphs.
 */
static void test_against_reference() {
    std::mt19937 random(2026);
    const std::array<uint64_t, 9> weights = {
        0,
        1,
        19,
        uint64_t{1} << 31,
        (uint64_t{1} << 32) + 5,
        INF / 2,
        INF - 1,
        INF,
        std::numeric_limits<uint64_t>::max()};
    for (uint64_t vertices = 1; vertices <= 7; ++vertices) {
        for (size_t sample = 0; sample < 30; ++sample) {
            std::vector<std::vector<std::pair<uint64_t, uint64_t>>> forward(
                vertices),
                reverse(vertices);
            for (uint64_t source = 0; source < vertices; ++source) {
                for (uint64_t target = 0; target < vertices; ++target) {
                    if (random() % 4 == 0) {
                        const auto weight = weights[random() % weights.size()];
                        graph::bidirectional_dijkstra::addEdge(
                            &forward, &reverse, source + 1, target + 1, weight);
                    }
                }
            }
            const auto expected = reference_distances(forward);
            for (uint64_t source = 0; source < vertices; ++source) {
                for (uint64_t target = 0; target < vertices; ++target) {
                    const auto distance = expected[source][target];
                    const int64_t result =
                        distance == INF ? -1 : static_cast<int64_t>(distance);
                    assert(graph::bidirectional_dijkstra::Bidijkstra(
                               &forward, &reverse, source, target) == result);
                }
            }
        }
    }
    std::cout
        << "Floyd-Warshall comparison passed (4200 source/target pairs)\n";
}

/**
 * @brief Function to test the
 * provided algorithm above
 * @returns void
 */
static void tests() {
    test_distance_regressions();
    test_against_reference();
    std::cout << "Initiatinig Predefined Tests..." << '\n';
    std::cout << "Initiating Test 1..." << '\n';
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj1_1(
        4, std::vector<std::pair<uint64_t, uint64_t>>());
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj1_2(
        4, std::vector<std::pair<uint64_t, uint64_t>>());
    graph::bidirectional_dijkstra::addEdge(&adj1_1, &adj1_2, 1, 2, 1);
    graph::bidirectional_dijkstra::addEdge(&adj1_1, &adj1_2, 4, 1, 2);
    graph::bidirectional_dijkstra::addEdge(&adj1_1, &adj1_2, 2, 3, 2);
    graph::bidirectional_dijkstra::addEdge(&adj1_1, &adj1_2, 1, 3, 5);

    uint64_t s = 1, t = 3;
    assert(graph::bidirectional_dijkstra::Bidijkstra(&adj1_1, &adj1_2, s - 1,
                                                     t - 1) == 3);
    std::cout << "Test 1 Passed..." << '\n';

    s = 4, t = 3;
    std::cout << "Initiating Test 2..." << '\n';
    assert(graph::bidirectional_dijkstra::Bidijkstra(&adj1_1, &adj1_2, s - 1,
                                                     t - 1) == 5);
    std::cout << "Test 2 Passed..." << '\n';

    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj2_1(
        5, std::vector<std::pair<uint64_t, uint64_t>>());
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj2_2(
        5, std::vector<std::pair<uint64_t, uint64_t>>());
    graph::bidirectional_dijkstra::addEdge(&adj2_1, &adj2_2, 1, 2, 4);
    graph::bidirectional_dijkstra::addEdge(&adj2_1, &adj2_2, 1, 3, 2);
    graph::bidirectional_dijkstra::addEdge(&adj2_1, &adj2_2, 2, 3, 2);
    graph::bidirectional_dijkstra::addEdge(&adj2_1, &adj2_2, 3, 2, 1);
    graph::bidirectional_dijkstra::addEdge(&adj2_1, &adj2_2, 2, 4, 2);
    graph::bidirectional_dijkstra::addEdge(&adj2_1, &adj2_2, 3, 5, 4);
    graph::bidirectional_dijkstra::addEdge(&adj2_1, &adj2_2, 5, 4, 1);
    graph::bidirectional_dijkstra::addEdge(&adj2_1, &adj2_2, 2, 5, 3);
    graph::bidirectional_dijkstra::addEdge(&adj2_1, &adj2_2, 3, 4, 4);

    s = 1, t = 5;
    std::cout << "Initiating Test 3..." << '\n';
    assert(graph::bidirectional_dijkstra::Bidijkstra(&adj2_1, &adj2_2, s - 1,
                                                     t - 1) == 6);
    std::cout << "Test 3 Passed..." << '\n';
    std::cout << "All Test Passed..." << '\n' << '\n';
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // running predefined tests
    uint64_t vertices = uint64_t();
    uint64_t edges = uint64_t();
    std::cout << "Enter the number of vertices : ";
    std::cin >> vertices;
    std::cout << "Enter the number of edges : ";
    std::cin >> edges;

    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj1(
        vertices, std::vector<std::pair<uint64_t, uint64_t>>());
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj2(
        vertices, std::vector<std::pair<uint64_t, uint64_t>>());

    uint64_t u = uint64_t(), v = uint64_t(), w = uint64_t();
    std::cout << "Enter the edges by three integers in this form: u v w "
              << '\n';
    std::cout << "Example: if there is and edge between node 1 and node 4 with "
                 "weight 7 enter: 1 4 7, and then press enter"
              << '\n';
    while (edges--) {
        std::cin >> u >> v >> w;
        graph::bidirectional_dijkstra::addEdge(&adj1, &adj2, u, v, w);
        if (edges != 0) {
            std::cout << "Enter the next edge" << '\n';
        }
    }

    uint64_t s = uint64_t(), t = uint64_t();
    std::cout
        << "Enter the source node and the target node separated by a space"
        << '\n';
    std::cout << "Example: If the source node is 5 and the target node is 6 "
                 "enter: 5 6 and press enter"
              << '\n';
    std::cin >> s >> t;
    int64_t dist =
        graph::bidirectional_dijkstra::Bidijkstra(&adj1, &adj2, s - 1, t - 1);
    if (dist == -1) {
        std::cout << "Target not reachable from source" << '\n';
    } else {
        std::cout << "Shortest Path Distance : " << dist << '\n';
    }

    return 0;
}
