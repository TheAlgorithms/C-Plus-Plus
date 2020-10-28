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
 */
#include <iostream> /// for io operations
#include <set>    /// for std::set
#include <vector> /// for std::vector

int number_of_nodes;  // denotes number of nodes;
std::vector<int> parent; // parent of each node
std::vector<int> connected_set_size; // size of each set
/**
 * @brief function the initialize every node as it's own parent
 * @returns void
 */
void make_set() {
    for (int i = 1; i <= number_of_nodes; i++) {
        parent[i] = i;
        connected_set_size[i] = 1;
    }
}
/**
 * @brief To find the component where following node belongs to
 * @param val parent of val should be found
 * @return parent of val
 */
int find_set(int val) {
    while (parent[val] != val) {
        parent[val] = parent[parent[val]];
        val = parent[val];
    }
    return val;
}
/**
 * @brief To join 2 components to belong to one
 * @param a 1st component
 * @param b 2nd component
 * @returns void
 */
void union_sets(int a, int b) {
    a = find_set(a); // find the parent of a
    b = find_set(b); // find the parent of b

    // If parents of both nodes are not same, combine them
    if (a != b) {
        if (connected_set_size[a] < connected_set_size[b]) {
            std::swap(a, b); // swap both components
        }
        parent[b] = a; // make a node as parent of b node.
        connected_set_size[a] += connected_set_size[b]; // sum the size of both as they combined
    }
}
/**
 * @brief To find total no of connected components
 * @return Number of connected components
 */
int no_of_connected_components() {
    std::set<int> temp;  // temp set to count number of connected components
    for (int i = 1; i <= number_of_nodes; i++)
        temp.insert(find_set(i));
    return temp.size(); // return the size of temp set
}

/**
 * @brief Test Implementations
 * @returns void
 */
static void test() {
    std::cin >> number_of_nodes;
    parent.resize(number_of_nodes + 1);
    connected_set_size.resize(number_of_nodes + 1);
    make_set();
    int edges = 0;
    std::cin >> edges;  // no of edges in the graph
    while (edges--) {
        int node_a = 0, node_b = 0;
        std::cin >> node_a >> node_b;
        union_sets(node_a, node_b);
    }
    std::cout << no_of_connected_components() << std::endl;
}

int main() {
    test(); // Execute the tests
    return 0;
}
