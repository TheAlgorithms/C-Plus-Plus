/**
 * \file
 * \brief Graph Data Structure
 *
 * \author [Filip Hlasek](http://github.com/fhlasek)
 *
 * \details
 * This file contains an implementation of the graph datastructure
 * reprsented by an Adjacency List
 * (https://en.wikipedia.org/wiki/Adjacency_list). That representation is most
 * commonly used by the graph algorithm as it allows easily to iterate over
 * neighbors of every vertex with a complexity linear with the number of
 * neighbors (unlike the adjacency matrix representation for which the operation
 * is linear in the total number of vertices in the graph even if there are no
 * neighbors of the vertex at all).
 */

#include <cassert>
#include <list>
#include <utility>
#include <vector>

namespace graph {

class directed_graph {
 public:
    /**
     *
     */
    std::vector<std::list<int> > neighbors;

    directed_graph(int number_of_vertices,
                   const std::vector<std::pair<int, int> >& edges) {
        neighbors.resize(number_of_vertices);
        for (auto& edge : edges) {
            addEdge(edge.first, edge.second);
        }
    }

    int vertices() const { return neighbors.size(); }

    void addEdge(int a, int b) {
        assert(0 <= a && a < vertices());
        assert(0 <= b && b < vertices());
        neighbors[a].push_back(b);
    }
};

}  // namespace graph
