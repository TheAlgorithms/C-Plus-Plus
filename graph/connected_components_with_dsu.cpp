/**
 * @file
 * @brief [Disjoint union](https://en.wikipedia.org/wiki/Disjoint_union)
 *
 * @details
 * The Disjoint union is the technique to find connected component in graph efficiently.
 *
 * ### Algorithm
 * In Graph, if you have to find out the number of connected components, there are 2 options
 * 1. Depth first search
 * 2. Disjoint union
 * 1st option is inefficient, Disjoint union is the most optimal way to find this.
 *
 * @author Unknown author
 * @author [Sagar Pandya](https://github.com/sagarpandyansit)
 */
#include <iostream> /// for IO operations
#include <set>    /// for std::set
#include <vector> /// for std::vector

/**
 * @namespace graph
 * @brief Graph Algorithms
 */
namespace graph {
/**
 * @namespace disjoint_union
 * @brief Functions for [Disjoint union](https://en.wikipedia.org/wiki/Disjoint_union) implementation
 */
namespace disjoint_union {
uint32_t number_of_nodes = 0;                // denotes number of nodes
std::vector<int64_t> parent{};               // parent of each node
std::vector<uint32_t> connected_set_size{};  // size of each set
/**
 * @brief function the initialize every node as it's own parent
 * @returns void
 */
void make_set() {
    for (uint32_t i = 1; i <= number_of_nodes; i++) {
        parent[i] = i;
        connected_set_size[i] = 1;
    }
}
/**
 * @brief Find the component where following node belongs to
 * @param val parent of val should be found
 * @return parent of val
 */
int64_t find_set(int64_t val) {
    while (parent[val] != val) {
        parent[val] = parent[parent[val]];
        val = parent[val];
    }
    return val;
}
/**
 * @brief Merge 2 components to become one
 * @param node1 1st component
 * @param node2 2nd component
 * @returns void
 */
void union_sets(int64_t node1, int64_t node2) {
    node1 = find_set(node1);  // find the parent of node1
    node2 = find_set(node2);  // find the parent of node2

    // If parents of both nodes are not same, combine them
    if (node1 != node2) {
        if (connected_set_size[node1] < connected_set_size[node2]) {
            std::swap(node1, node2);  // swap both components
        }
        parent[node2] = node1;  // make node1 as parent of node2.
        connected_set_size[node1] +=
            connected_set_size[node2];  // sum the size of both as they combined
    }
}
/**
 * @brief Find total no. of connected components
 * @return Number of connected components
 */
uint32_t no_of_connected_components() {
    std::set<int64_t> temp;  // temp set to count number of connected components
    for (uint32_t i = 1; i <= number_of_nodes; i++) temp.insert(find_set(i));
    return temp.size();  // return the size of temp set
}
}  // namespace disjoint_union
}  // namespace graph

/**
 * @brief Test Implementations
 * @returns void
 */
static void test() {
    namespace dsu = graph::disjoint_union;
    std::cin >> dsu::number_of_nodes;
    dsu::parent.resize(dsu::number_of_nodes + 1);
    dsu::connected_set_size.resize(dsu::number_of_nodes + 1);
    dsu::make_set();
    uint32_t edges = 0;
    std::cin >> edges;  // no of edges in the graph
    while (edges--) {
        int64_t node_a = 0, node_b = 0;
        std::cin >> node_a >> node_b;
        dsu::union_sets(node_a, node_b);
    }
    std::cout << dsu::no_of_connected_components() << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // Execute the tests
    return 0;
}
