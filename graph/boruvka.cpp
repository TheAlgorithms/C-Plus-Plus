/**
 * @file boruvkas_algorithm.cpp
 * @brief Implementation of Boruvka's Algorithm to find out the minimum spanning
 * tree of a graph.
 * @author FranciscoThiesen
 * @details For more details, see
 * https://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm
 */

#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

/**
 * @brief Union-Find data structure (with union by rank and path compression).
 */
struct union_find {
    std::vector<int> parent, component_size;

    /**
     * @brief Initializes the union_find data structure.
     * @param n Number of elements.
     */
    union_find(int n) {
        parent.resize(n);
        component_size.assign(n, 1);
        std::iota(parent.begin(), parent.end(), 0);
    }

    /**
     * @brief Finds the representative of the set containing x.
     * @param x An element of the set.
     * @return The representative of the set containing x.
     */
    int find(int x) {
        return (parent[x] == x) ? x : parent[x] = find(parent[x]);
    }

    /**
     * @brief Unites two sets containing x and y.
     * @param x An element of the first set.
     * @param y An element of the second set.
     */
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x != y) {
            if (component_size[x] < component_size[y]) {
                std::swap(x, y);
            }
            parent[y] = x;
            component_size[x] += component_size[y];
        }
    }
};

/**
 * @brief Boruvka's algorithm to compute the minimum spanning tree cost.
 * @param num_nodes Number of nodes in the graph.
 * @param num_edges Number of edges in the graph.
 * @param edges Edges of the graph.
 * @return Minimum spanning tree cost.
 */
long long boruvka(
    int num_nodes, int num_edges,
    const std::vector<std::pair<int, std::pair<int, int>>>& edges) {
    union_find UF(num_nodes);

    // In the beginning, each vertex represents an individual component
    int total_components = num_nodes;

    std::vector<int> cheapest_edge_from(num_nodes, -1);
    long long total_cost = 0;

    // This implementation assumes a connected graph as input. Algorithm can be
    // adapted to find the minimum spanning forest by stopping whenever we
    // iterate over all the edges and cannot find a new candidate edge to unite
    // two components.
    while (total_components > 1) {
        // resetting the values because the components
        fill(cheapest_edge_from.begin(), cheapest_edge_from.end(), -1);

        // We now want to go over all edges and find the cheapest edge that
        // leaves each one of the remaining components.
        for (int e = 0; e < num_edges && total_components > 1; ++e) {
            int from = edges[e].second.first;
            int to = edges[e].second.second;
            int weight = edges[e].first;

            int from_component = UF.find(from);
            int to_component = UF.find(to);

            if (from_component == to_component) {
                continue;
            }

            if (cheapest_edge_from[from_component] == -1 ||
                edges[cheapest_edge_from[from_component]].first > weight) {
                cheapest_edge_from[from_component] = e;
            }

            if (cheapest_edge_from[to_component] == -1 ||
                edges[cheapest_edge_from[to_component]].first > weight) {
                cheapest_edge_from[to_component] = e;
            }

            for (int i = 0; i < num_nodes; ++i) {
                if (cheapest_edge_from[i] != -1) {
                    int from = edges[cheapest_edge_from[i]].second.first;
                    int to = edges[cheapest_edge_from[i]].second.second;
                    int weight = edges[cheapest_edge_from[i]].first;

                    if (UF.find(from) != UF.find(to)) {
                        UF.unite(from, to);
                        total_cost += weight;
                        --total_components;
                    }
                }
            }
        }
    }

    return total_cost;
}

/**
 * @brief Test function for Boruvka's algorithm.
 */
void tests() {
    std::vector<std::pair<int, std::pair<int, int>>> edges;
    edges.push_back({1, {0, 1}});
    edges.push_back({2, {0, 2}});
    edges.push_back({3, {1, 2}});
    edges.push_back({4, {1, 3}});
    edges.push_back({5, {2, 3}});
    edges.push_back({6, {2, 4}});
    edges.push_back({7, {3, 4}});
    assert(boruvka(5, 7, edges) == 13);
}

int main() {
    tests();

    /**
     * @mainpage Interactive Execution Mode
     *
     * @section overview Overview
     * Uncomment the following block if you want to run the Boruvka algorithm
     * for finding the minimum spanning tree interactively.
     *
     * @section usage Usage
     * 1. The program prompts you for the number of vertices and edges.
     * 2. For each edge, you will specify the start vertex, end vertex, and
     * weight.
     * 3. The program calculates and displays the minimum spanning tree cost
     * using the Boruvka algorithm.
     */

    /*
    while (true) {
        // Getting the input graph
        int num_nodes, num_edges;



        //! Prompt user for graph details
        std::cout << "Enter the number of vertices and edges of your graph"
                  << std::endl;
        std::cin >> num_nodes >> num_edges;
        
        std::vector<std::pair<int, std::pair<int, int>>> edges;

        //! Prompt user for edge details
        std::cout << "Enter the edges of your graph in the format: "
                  << "from to weight" << std::endl;

        for (int i = 0; i < num_edges; ++i) {
            int from, to, weight;
            std::cin >> from >> to >> weight;

            //! Store edge information
            edges.emplace_back(
                std::make_pair(weight, std::make_pair(from, to)));
        }

        //! Display minimum spanning tree cost
        std::cout << "Total minimum spanning tree cost = "
                  << boruvka(num_nodes, num_edges, edges) << std::endl;
    }
    */

    return 0;
}
