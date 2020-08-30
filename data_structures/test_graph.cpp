#include <cassert>
#include <set>

#include "./graph.hpp"

/** Test function */
static void test() {
    // Empty graph with no vertices and no edges.
    data_structures::directed_graph graph0(0, {});
    assert(graph0.neighbors.empty());

    // A trivial directed graph with two vertices and a single edge.
    data_structures::directed_graph graph1(2, {{0, 1}});
    std::set<int> ans10(graph1.neighbors[0].begin(), graph1.neighbors[0].end());
    assert(ans10 == std::set<int>({1}));
    std::set<int> ans11(graph1.neighbors[1].begin(), graph1.neighbors[1].end());
    assert(ans11 == std::set<int>({}));

    // A trivial undirected graph with two vertices and a single edge.
    data_structures::undirected_graph graph2(2, {{0, 1}});
    std::set<int> ans20(graph2.neighbors[0].begin(), graph2.neighbors[0].end());
    assert(ans20 == std::set<int>({1}));
    std::set<int> ans21(graph2.neighbors[1].begin(), graph2.neighbors[1].end());
    assert(ans21 == std::set<int>({0}));

    // A bit more sophisticated undirected graph with 4 vertices and a self-loop
    //
    //     0---
    //     |   \
    //     |     3---2
    //     |   /
    //     1---
    //    / \
    //   |   |
    //    \_/
    //
    data_structures::undirected_graph graph3(
        4, {{3, 2}, {1, 1}, {1, 3}, {3, 0}, {1, 0}});
    std::set<int> ans30(graph3.neighbors[0].begin(), graph3.neighbors[0].end());
    assert(ans30 == std::set<int>({1, 3}));
    std::set<int> ans31(graph3.neighbors[1].begin(), graph3.neighbors[1].end());
    assert(ans31 == std::set<int>({0, 1, 3}));
    std::set<int> ans32(graph3.neighbors[2].begin(), graph3.neighbors[2].end());
    assert(ans32 == std::set<int>({3}));
    std::set<int> ans33(graph3.neighbors[3].begin(), graph3.neighbors[3].end());
    assert(ans33 == std::set<int>({0, 1, 2}));
}

/** Main function */
int main() {
    test();
    return 0;
}
