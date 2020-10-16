/**
 *
 * \file
 *
 * \brief Data structure for finding the lowest common ancestor
 * of two vertices in a rooted tree using binary lifting.
 *
 * \details
 * Algorithm: https://cp-algorithms.com/graph/lca_binary_lifting.html
 *
 * Complexity:
 *   - Precomputation: \f$O(N \log N)\f$ where \f$N\f$ is the number of vertices
 * in the tree
 *   - Query: \f$O(\log N)\f$
 *   - Space: \f$O(N \log N)\f$
 *
 * Example:
 * <br/>  Tree:
 * <pre>
 *             _  3  _
 *          /     |     \
 *        1       6       4
 *      / |     /   \       \
 *    7   5   2       8       0
 *            |
 *            9
 * </pre>
 *
 * <br/>  lowest_common_ancestor(7, 4) = 3
 * <br/>  lowest_common_ancestor(9, 6) = 6
 * <br/>  lowest_common_ancestor(0, 0) = 0
 * <br/>  lowest_common_ancestor(8, 2) = 6
 *
 *   The query is symmetrical, therefore
 *     lowest_common_ancestor(x, y) = lowest_common_ancestor(y, x)
 */

#include <cassert>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

/**
 * \namespace graph
 * \brief Graph algorithms
 */
namespace graph {
/**
 * Class for representing a graph as an adjacency list.
 * Its vertices are indexed 0, 1, ..., N - 1.
 */
class Graph {
 public:
    /**
     * \brief Populate the adjacency list for each vertex in the graph.
     * Assumes that evey edge is a pair of valid vertex indices.
     *
     * @param N number of vertices in the graph
     * @param undirected_edges list of graph's undirected edges
     */
    Graph(size_t N, const std::vector<std::pair<int, int> > &undirected_edges) {
        neighbors.resize(N);
        for (auto &edge : undirected_edges) {
            neighbors[edge.first].push_back(edge.second);
            neighbors[edge.second].push_back(edge.first);
        }
    }

    /**
     * Function to get the number of vertices in the graph
     * @return the number of vertices in the graph.
     */
    int number_of_vertices() const { return neighbors.size(); }

    /** \brief for each vertex it stores a list indicies of its neighbors */
    std::vector<std::vector<int> > neighbors;
};

/**
 * Representation of a rooted tree. For every vertex its parent is
 * precalculated.
 */
class RootedTree : public Graph {
 public:
    /**
     * \brief Constructs the tree by calculating parent for every vertex.
     * Assumes a valid description of a tree is provided.
     *
     * @param undirected_edges list of graph's undirected edges
     * @param root_ index of the root vertex
     */
    RootedTree(const std::vector<std::pair<int, int> > &undirected_edges,
               int root_)
        : Graph(undirected_edges.size() + 1, undirected_edges), root(root_) {
        populate_parents();
    }

    /**
     * \brief Stores parent of every vertex and for root its own index.
     * The root is technically not its own parent, but it's very practical
     * for the lowest common ancestor algorithm.
     */
    std::vector<int> parent;
    /** \brief Stores the distance from the root. */
    std::vector<int> level;
    /** \brief Index of the root vertex. */
    int root;

 protected:
    /**
     * \brief Calculate the parents for all the vertices in the tree.
     * Implements the breadth first search algorithm starting from the root
     * vertex searching the entire tree and labeling parents for all vertices.
     * @returns none
     */
    void populate_parents() {
        // Initialize the vector with -1 which indicates the vertex
        // wasn't yet visited.
        parent = std::vector<int>(number_of_vertices(), -1);
        level = std::vector<int>(number_of_vertices());
        parent[root] = root;
        level[root] = 0;
        std::queue<int> queue_of_vertices;
        queue_of_vertices.push(root);
        while (!queue_of_vertices.empty()) {
            int vertex = queue_of_vertices.front();
            queue_of_vertices.pop();
            for (int neighbor : neighbors[vertex]) {
                // As long as the vertex was not yet visited.
                if (parent[neighbor] == -1) {
                    parent[neighbor] = vertex;
                    level[neighbor] = level[vertex] + 1;
                    queue_of_vertices.push(neighbor);
                }
            }
        }
    }
};

/**
 * A structure that holds a rooted tree and allow for effecient
 * queries of the lowest common ancestor of two given vertices in the tree.
 */
class LowestCommonAncestor {
 public:
    /**
     * \brief Stores the tree and precomputs "up lifts".
     * @param tree_ rooted tree.
     */
    explicit LowestCommonAncestor(const RootedTree &tree_) : tree(tree_) {
        populate_up();
    }

    /**
     * \brief Query the structure to find the lowest common ancestor.
     * Assumes that the provided numbers are valid indices of vertices.
     * Iterativelly modifies ("lifts") u an v until it finnds their lowest
     * common ancestor.
     * @param u index of one of the queried vertex
     * @param v index of the other queried vertex
     * @return index of the vertex which is the lowet common ancestor of u and v
     */
    int lowest_common_ancestor(int u, int v) const {
        // Ensure u is the deeper (higher level) of the two vertices
        if (tree.level[v] > tree.level[u]) {
            std::swap(u, v);
        }

        // "Lift" u to the same level as v.
        int level_diff = tree.level[u] - tree.level[v];
        for (int i = 0; (1 << i) <= level_diff; ++i) {
            if (level_diff & (1 << i)) {
                u = up[u][i];
            }
        }
        assert(tree.level[u] == tree.level[v]);

        if (u == v) {
            return u;
        }

        // "Lift" u and v to their 2^i th ancestor if they are different
        for (int i = static_cast<int>(up[u].size()) - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }

        // As we regressed u an v such that they cannot further be lifted so
        // that their ancestor would be different, the only logical
        // consequence is that their parent is the sought answer.
        assert(up[u][0] == up[v][0]);
        return up[u][0];
    }

    /* \brief reference to the rooted tree this structure allows to query */
    const RootedTree &tree;
    /**
     * \brief for every vertex stores a list of its ancestors by powers of two
     * For each vertex, the first element of the corresponding list contains
     * the index of its parent. The i-th element of the list is an index of
     * the (2^i)-th ancestor of the vertex.
     */
    std::vector<std::vector<int> > up;

 protected:
    /**
     * Populate the "up" structure. See above.
     */
    void populate_up() {
        up.resize(tree.number_of_vertices());
        for (int vertex = 0; vertex < tree.number_of_vertices(); ++vertex) {
            up[vertex].push_back(tree.parent[vertex]);
        }
        for (int level = 0; (1 << level) < tree.number_of_vertices(); ++level) {
            for (int vertex = 0; vertex < tree.number_of_vertices(); ++vertex) {
                // up[vertex][level + 1] = 2^(level + 1) th ancestor of vertex =
                // = 2^level th ancestor of 2^level th ancestor of vertex =
                // = 2^level th ancestor of up[vertex][level]
                up[vertex].push_back(up[up[vertex][level]][level]);
            }
        }
    }
};

}  // namespace graph

/**
 * Unit tests
 * @returns none
 */
static void tests() {
    /**
     *             _  3  _
     *          /     |     \
     *        1       6       4
     *      / |     /   \       \
     *    7   5   2       8       0
     *            |
     *            9
     */
    std::vector<std::pair<int, int> > edges = {
        {7, 1}, {1, 5}, {1, 3}, {3, 6}, {6, 2}, {2, 9}, {6, 8}, {4, 3}, {0, 4}};
    graph::RootedTree t(edges, 3);
    graph::LowestCommonAncestor lca(t);
    assert(lca.lowest_common_ancestor(7, 4) == 3);
    assert(lca.lowest_common_ancestor(9, 6) == 6);
    assert(lca.lowest_common_ancestor(0, 0) == 0);
    assert(lca.lowest_common_ancestor(8, 2) == 6);
}

/** Main function */
int main() {
    tests();
    return 0;
}
