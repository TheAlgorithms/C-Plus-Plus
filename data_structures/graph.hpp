/**
 * \file
 * \brief Graph Data Structure
 *
 * \author [Filip Hlasek](http://github.com/fhlasek)
 *
 * \details
 * This file contains an implementation of the graph data structure
 * reprsented by an Adjacency List
 * (https://en.wikipedia.org/wiki/Adjacency_list). That representation is most
 * commonly used by the graph algorithm as it allows easily to iterate over
 * neighbors of every vertex with a complexity linear with the number of
 * neighbors (unlike the adjacency matrix representation for which the operation
 * is linear in the total number of vertices in the graph even if there are no
 * neighbors of the vertex at all).
 */

#ifndef DATA_STRUCTURES_GRAPH_H_
#define DATA_STRUCTURES_GRAPH_H_

#include <cassert>
#include <list>
#include <utility>
#include <vector>

/** \namespace data_structures
 * \brief Data-structure algorithms
 */
namespace data_structures {

/**
 * @brief Data structure storing a directed graph as an adjacency list.
 */
class directed_graph {
 public:
    /** @brief For every vertex a list of its neigbors is stored.  */
    std::vector<std::list<int> > neighbors;

    /**
     * @brief This constructor builds the structure from a list of edges.
     * It assumes that the vertices of the graph are indexed from 0.
     *
     * @param number_of_vertices the number of vertices in the graph
     * @param edges ordered pairs of vertices representing directed edges
     */
    directed_graph(int number_of_vertices,
                   const std::vector<std::pair<int, int> >& edges)
        : neighbors(std::vector<std::list<int> >(number_of_vertices)) {
        for (const auto& edge : edges) {
            add_edge(edge.first, edge.second);
        }
    }

    /**
     * @returns the number of vertices in the graph
     */
    int vertices() const { return neighbors.size(); }

    /**
     * @brief Adds a new directed edge in the graph.
     * @param a starting vertex of the newly added the directed edge
     * @param b an ending vertex of the newly added directed edge
     */
    void add_directed_edge(int a, int b) {
        assert(0 <= a && a < vertices());
        assert(0 <= b && b < vertices());
        neighbors[a].push_back(b);
    }

    /**
     * @brief a shortcut for add_directed_edge (see above).
     * @param a starting vertex of the newly added the directed edge
     * @param b an ending vertex of the newly added directed edge
     */
    void add_edge(int a, int b) { add_directed_edge(a, b); }
};

/**
 * @brief undirected graph is represented as a directed graph in which every
 * edge is added in both directions.
 */
class undirected_graph : public directed_graph {
 public:
    /**
     * @brief This constructor builds the structure from a list of edges.
     * It assumes that the vertices of the graph are indexed from 0.
     *
     * @param number_of_vertices the number of vertices in the graph
     * @param edges pairs of vertices representing the undirected edges
     */
    undirected_graph(int number_of_vertices,
                     const std::vector<std::pair<int, int> >& edges)
        : directed_graph(number_of_vertices, edges) {
        for (const auto& edge : edges) {
            // Don't add an opposite directed edge for self-loops
            if (edge.first != edge.second) {
                // Add every edge in the opposite direction
                // to make the graph undirected.
                add_directed_edge(edge.second, edge.first);
            }
        }
    }

    /**
     * @brief overrides the method of the parent directed_graph to provide
     * a more intuitive adding of new undirected edges.
     *
     * @param a an index of one endpoint vertex of the newly added edge
     * @param b an index of the other eendpoint vertex of the newly added edge
     */
    void add_edge(int a, int b) {
        add_directed_edge(a, b);
        add_directed_edge(b, a);
    }
};

}  // namespace data_structures

#endif  // DATA_STRUCTURES_GRAPH_H_
