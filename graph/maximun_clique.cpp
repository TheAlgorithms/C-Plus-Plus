/**
 *
 * @file
 * @brief [Clique problem](https://en.wikipedia.org/wiki/Clique_problem)
 *
 * @author [Jxtopher](https://github.com/jxtopher)
 *
 * @details The maximum clique problem is find the group of vertices in the
 * graph where everyone is connected to everyone else, and this group is the
 * biggest such group you can find in the entire graph.
 *
 * This implementation for maximum clique algorithm is based on [A fast
 * algorithm for the maximum clique
 * problem](https://doi.org/10.1016/S0166-218X(01)00290-6)
 */

#include <algorithm>  /// header for set_intersection, min_element
#include <cassert>    /// header for preprocessor macro assert()
#include <iostream>   /// for IO operations
#include <iterator>   /// header for std::inserter
#include <limits>     /// header for limits of integral types
#include <list>       /// herder for list
#include <set>        /// herder for std:set
#include <vector>     /// header for std::vector

/**
 * @namespace graph
 * @brief Graph algorithms
 */
namespace graph {
/**
 * @namespace maximun_clique
 * @brief Functions for [Maximun
 * clique](https://en.wikipedia.org/wiki/Clique_problem) algorithm
 */
namespace maximun_clique {
/**
 * @brief
 * Adds and edge between two vertices of graph say u and v in this
 * case.
 *
 * @param adj Adjacency list representation of graph
 * @param u first vertex
 * @param v second vertex
 *
 */
void addEdge(std::vector<std::set<size_t>> *adj, size_t u, size_t v) {
    /*
     *
     * Here we are considering undirected graph that's the
     * reason we are adding v to the adjacency list representation of u
     * and also adding u to the adjacency list representation of v
     *
     */
    (*adj)[u].insert(v);
}

void addEdge(std::vector<std::set<size_t>> *adj, size_t u,
             const std::list<size_t> &vertices) {
    for (const size_t vertex : vertices) {
        (*adj)[u].insert(vertex);
    }
}

/**
 * Global context of the recursive function.
 */
struct Context {
    bool found = false;     // True if clique is found otherwise False
    size_t max = 0;         // degrees maximum of separation
    std::vector<size_t> c;  // enable the new pruning strategy
    std::vector<std::set<size_t>> graph;  // Problem instance data
};

/**
 * @brief
 */
void clique(size_t size, Context &ctx, std::set<size_t> U,
            std::set<size_t> &result) {
    // Criterion for terminating the recursive function.
    if (U.empty()) {
        if (size > ctx.max) {
            ctx.max = size;
            ctx.found = true;
        }
        return;
    }

    // While that there are adjacent vertices to consider
    while (!U.empty()) {
        if (size + U.size() <= ctx.max) {
            return;
        }

        size_t v_i = *std::min_element(
            U.cbegin(), U.cend(), [&ctx](size_t v1, size_t v2) {
                return ctx.graph[v1].size() < ctx.graph[v2].size();
            });

        // pruning strategy
        if (size + ctx.c[v_i] < ctx.max) {
            return;
        }

        // Remove the vertex visited
        U.erase(v_i);
        result.insert(v_i);

        // Intersection between U and the list of adjacent of v_i
        std::set<size_t> inter;
        std::set_intersection(U.cbegin(), U.cend(), ctx.graph[v_i].cbegin(),
                              ctx.graph[v_i].cend(),
                              std::inserter(inter, inter.begin()));

        clique(size + 1, ctx, inter, result);

        if (ctx.found) {
            return;
        }
    }
}

std::set<size_t> run(const std::vector<std::set<size_t>> &graph) {
    Context ctx;
    ctx.max = 0;
    ctx.c = std::vector<size_t>(graph.size(), 0);
    ctx.graph = graph;
    std::set<size_t> max_clique;

    size_t i = graph.size();
    while (i-- > 0) {
        std::set<size_t> U;
        for (size_t j = i; j < graph.size(); j++) {
            U.insert(j);
        }

        std::set<size_t> inter;
        std::set_intersection(U.cbegin(), U.cend(), ctx.graph[i].cbegin(),
                              ctx.graph[i].cend(),
                              std::inserter(inter, inter.begin()));

        ctx.found = false;
        std::set<size_t> result;
        result.insert(i);
        graph::maximun_clique::clique(1, ctx, inter, result);
        ctx.c[i] = ctx.max;
        if (result.size() > max_clique.size()) {
            max_clique = result;
        }
    }

    return max_clique;
}
}  // namespace maximun_clique
}  // namespace graph

/**
 * Self-test implementations
 * @returns none
 */
static void tests() {
    /// Test 1
    std::cout << "- Test 1" << std::endl;
    std::vector<std::set<size_t>> g1(5, std::set<size_t>());
    graph::maximun_clique::addEdge(&g1, 0, {1, 4});
    graph::maximun_clique::addEdge(&g1, 1, {0, 2, 3, 4});
    graph::maximun_clique::addEdge(&g1, 2, {1, 3, 4});
    graph::maximun_clique::addEdge(&g1, 3, {1, 2, 4});
    graph::maximun_clique::addEdge(&g1, 4, {0, 1, 2, 3});

    std::set<size_t> max_clique_for_g1 = graph::maximun_clique::run(g1);
    std::cout << "Clique: ";
    for (size_t vertex : max_clique_for_g1) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    /// Test 2
    /// Graph defined in Ostergard et al. 2002
    std::cout << "- Test 2" << std::endl;
    std::vector<std::set<size_t>> g2(8, std::set<size_t>());
    graph::maximun_clique::addEdge(&g2, 0, {7, 5, 4, 2});
    graph::maximun_clique::addEdge(&g2, 1, {6, 5, 4});
    graph::maximun_clique::addEdge(&g2, 2, {0, 7, 6, 5});
    graph::maximun_clique::addEdge(&g2, 3, {7, 6, 5});
    graph::maximun_clique::addEdge(&g2, 4, {1, 0, 7, 6});
    graph::maximun_clique::addEdge(&g2, 5, {2, 3, 1, 0});
    graph::maximun_clique::addEdge(&g2, 6, {1, 2, 3, 4});
    graph::maximun_clique::addEdge(&g2, 7, {0, 2, 3, 4});

    std::set<size_t> max_clique_for_g2 = graph::maximun_clique::run(g2);
    std::cout << "Clique: ";
    for (size_t vertex : max_clique_for_g2) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    /// Test 3
    /// Graph defined in Carraghan et al. 1990
    std::cout << "- Test 3" << std::endl;
    std::vector<std::set<size_t>> g3(8, std::set<size_t>());
    graph::maximun_clique::addEdge(&g3, 0, {1, 3, 4});
    graph::maximun_clique::addEdge(&g3, 1, {0, 6, 5, 3, 2});
    graph::maximun_clique::addEdge(&g3, 2, {1, 7, 6, 3});
    graph::maximun_clique::addEdge(&g3, 3, {2, 1, 0, 7, 6, 5, 4});
    graph::maximun_clique::addEdge(&g3, 4, {3, 0, 5});
    graph::maximun_clique::addEdge(&g3, 5, {4, 3, 1, 7, 6});
    graph::maximun_clique::addEdge(&g3, 6, {1, 2, 3, 5});
    graph::maximun_clique::addEdge(&g3, 7, {2, 3, 5});

    std::set<size_t> max_clique_for_g3 = graph::maximun_clique::run(g3);
    std::cout << "Clique: ";
    for (size_t vertex : max_clique_for_g3) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    /// Test 4
    /// Complete graph
    std::cout << "- Test 4" << std::endl;
    std::vector<std::set<size_t>> g4(5, std::set<size_t>());
    graph::maximun_clique::addEdge(&g4, 0, {1, 2, 3, 4});
    graph::maximun_clique::addEdge(&g4, 1, {0, 2, 3, 4});
    graph::maximun_clique::addEdge(&g4, 2, {1, 0, 4, 3});
    graph::maximun_clique::addEdge(&g4, 3, {2, 1, 0, 4});
    graph::maximun_clique::addEdge(&g4, 4, {3, 2, 1, 0});

    std::set<size_t> max_clique_for_g4 = graph::maximun_clique::run(g4);
    std::cout << "Clique: ";
    for (size_t vertex : max_clique_for_g4) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    /// Test 5
    std::cout << "- Test 5" << std::endl;
    std::vector<std::set<size_t>> g5(5, std::set<size_t>());
    graph::maximun_clique::addEdge(&g5, 0, {});
    graph::maximun_clique::addEdge(&g5, 1, {});
    graph::maximun_clique::addEdge(&g5, 2, {});
    graph::maximun_clique::addEdge(&g5, 3, {});
    graph::maximun_clique::addEdge(&g5, 4, {});

    std::set<size_t> max_clique_for_g5 = graph::maximun_clique::run(g5);
    std::cout << "Clique: ";
    for (size_t vertex : max_clique_for_g5) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // execute the tests
    return 0;
}
