/**
 * @file
 * @brief Simple implementation of the [A* search
 * algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm)
 *
 * @details A* is an informed search algorithm, which leverages a heuristic
 * function to estimate the cost from the current node to the goal. This
 * enables the algorithm to prioritise traversing edges that move you closer to
 * the goal. This can significantly reduce the time spent searching but, unlike
 * Dijkstra, doesn't compute all possible routes.
 *
 * @author [Jordan Hembrow](http://github.com/JordanHembrow5)
 *
 */
#include <cassert>   /// For assert
#include <cmath>     /// For std::hypot, std::abs
#include <iostream>  /// For IO operations
#include <queue>     /// For std::priority_queue
#include <vector>    /// For std::vector

/**
 * @namespace graph
 * @brief Graph Algorithms
 */
namespace graph {

class Node {
 private:
    size_t _idx;               // A unique identifier for a given graph
    std::pair<int, int> _pos;  // Coordinates denoting the location of the node
    std::vector<size_t> _connections;  // A list of indexes of connected nodes

 public:
    Node(size_t idx, std::pair<int, int> pos, std::vector<size_t> conn = {}) {
        this->_idx = idx;
        this->_pos = pos;
        if (!conn.empty()) {
            for (size_t c : conn) {
                this->_connections.push_back(c);
            }
        }
    }

    void add_connection(size_t conn) { this->_connections.push_back(conn); }
    size_t get_idx() { return this->_idx; }
    std::vector<size_t> get_connections() { return this->_connections; }
    std::pair<int, int> get_pos() { return this->_pos; }
};

/**
 * @brief Calculates the euclidean distance between the current node and the
 * goal
 * @param curr_pos a pair containing the coordinates (x,y) of the current node
 * @param end_pos a pair containing the coordinates (x,y) of the goal node
 * @returns the euclidean distance between the current node and the goal
 */
double heuristic_cost(std::pair<int, int> curr_pos,
                      std::pair<int, int> end_pos) {
    return std::hypot(curr_pos.first - end_pos.first,
                      curr_pos.second - end_pos.second);
}

/**
 * @brief Calculates the euclidean distance between the current node and the
 * next node
 * @param curr_pos a pair containing the coordinates (x,y) of the current node
 * @param end_pos a pair containing the coordinates (x,y) of the next node
 * @returns the euclidean distance between the current node and the next node
 */
double traverse_cost(std::pair<int, int> curr_pos,
                     std::pair<int, int> next_pos) {
    return std::hypot(curr_pos.first - next_pos.first,
                      curr_pos.second - next_pos.second);
}

/**
 * @brief Calculates the best route from a given start and end point through a
 * weighted graph.
 * @param graph a graph of nodes with weighted connections
 * @param start_idx the index of the node to start the search from
 * @param end_idx the index of the goal node
 * @returns the distance, traversing through the graph, between the start and
 * end nodes. If the end node is not reachable, will return -1.
 */
double a_star(std::vector<Node> graph, size_t start_idx, size_t finish_idx) {
    if (start_idx == finish_idx) {
        return 0.0;
    }

    // stores all the info required for our priority queue
    typedef struct {
        double heur_cost = 0.0;
        double curr_weight = 0.0;
        size_t node_idx = 0;
    } queue_info;

    // Ensures our priority queue is sorted with the smallest cost at the top
    typedef struct {
        bool operator()(const queue_info l, const queue_info r) const {
            return (l.heur_cost + l.curr_weight) >
                   (r.heur_cost + r.curr_weight);
        }
    } custom_less;

    std::priority_queue<queue_info, std::vector<queue_info>, custom_less> pq;

    // Start at the start point, with a total weight of zero
    queue_info q_info;
    q_info.node_idx = start_idx;
    pq.push(q_info);
    std::pair<int, int> end_pos = graph[finish_idx].get_pos();

    while (!pq.empty()) {
        double curr_weight = pq.top().curr_weight;
        Node curr_node = graph[pq.top().node_idx];
        pq.pop();  // remove current node now we are exploring it
        for (const size_t &N_idx : curr_node.get_connections()) {
            double cost = curr_weight + traverse_cost(curr_node.get_pos(),
                                                      graph[N_idx].get_pos());

            if (N_idx == finish_idx) {  // We found the finish
                return cost;
            }

            queue_info q = {heuristic_cost(graph[N_idx].get_pos(), end_pos),
                            cost, N_idx};
            pq.push(q);
        }
    }
    std::cout << "End point is not reachable from start point!" << std::endl;
    return -1;
}

}  // namespace graph

/**
 * @brief Constructs an 8-node graph and tests different start and end points to
 * verify the algorithm works as expected
 * @returns void
 */
void test() {
    std::vector<graph::Node> graph;
    graph::Node n0(0, {0, 0}, {1, 6}), n1(1, {5, 0}, {2}), n2(2, {5, 5}, {3}),
        n3(3, {10, 5}, {4}), n4(4, {10, 10}, {5}), n5(5, {11, 11}),
        n6(6, {0, 11}, {7}), n7(7, {16, 11}, {5});

    graph.push_back(n0);
    graph.push_back(n1);
    graph.push_back(n2);
    graph.push_back(n3);
    graph.push_back(n4);
    graph.push_back(n5);
    graph.push_back(n6);
    graph.push_back(n7);

    double shortest_dist = graph::a_star(graph, 0, 5);
    constexpr double EPS = 1e-4;  // Accepable difference when compaing doubles
    std::cout << "Test 1:\n"
              << "  Shortest distance: " << shortest_dist << std::endl;
    assert(std::abs(shortest_dist - 21.4142) < EPS);

    shortest_dist = graph::a_star(graph, 1, 1);
    std::cout << "Test 2:\n"
              << "  Shortest distance: " << shortest_dist << std::endl;
    assert(shortest_dist == 0.0);
    std::cout << "\nTest is working correctly\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
