/**
 * @file
 *
 * @brief The [Euler Tour](https://en.wikipedia.org/wiki/Euler_tour_technique)
 * technique allows for efficient, parallel computation of solutions to common
 * problems in algorithmic graph theory
 *
 * @details
 * Euler tour is defined as a way of traversing tree such that each vertex is
 * added to the tour when we visit it (either moving down from parent vertex or
 * returning from child vertex). We start from root and reach back to root after
 * visiting all vertices. It requires exactly 2*n-1 vertices to store Euler
 * tour.
 *
 * Time Complexity : O(N)
 * Auxillary Space Complexity : O(N)
 *
 * @author [Kritika Shrinivasan](https://github.com/KritikaShrinivasan)
 */
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

/**
 *
 * \namespace EulerTour
 *
 */
namespace EulerTour {
std::vector<size_t> eulerTour(1005);
void addEdge(std::vector<std::vector<size_t>> *adj, size_t u, size_t v) {
    (*adj)[u - 1].push_back(v - 1);
    (*adj)[v - 1].push_back(u - 1);
}

void eulerTree(const std::vector<std::vector<size_t>> &adj, size_t u,
               std::vector<bool> *vis, size_t &id) {
    (*vis)[u] = 1;
    eulerTour[id++] = u;
    for (auto it : adj[u]) {
        if (!(*vis)[it]) {
            eulerTree(adj, it, vis, id);
            eulerTour[id++] = u;
        }
    }
}

std::string solve(const std::vector<std::vector<size_t>> adj, size_t root) {
    size_t id = 0, n = adj.size();
    std::vector<bool> vis(n, false);
    eulerTree(adj, root - 1, &vis, id);
    std::string ans = "";
    for (int i = 0; i < (2 * n - 1); i++) {
        // std::cout<<eulerTour[i]<<" ";
        ans += std::to_string(eulerTour[i] + 1) + " ";
    }

    return ans;
}
}  // namespace EulerTour

/** Function to test the Algorithm */
void tests() {
    std::cout << "Initiatinig Predefined Tests..." << std::endl;
    std::cout << "Initiating Test 1..." << std::endl;
    std::vector<std::vector<size_t>> adj1(4);
    EulerTour::addEdge(&adj1, 1, 2);
    EulerTour::addEdge(&adj1, 2, 3);
    EulerTour::addEdge(&adj1, 2, 4);
    assert(EulerTour::solve(adj1, 1) == "1 2 3 2 4 2 1 ");
    std::cout << "Test 1 Passed..." << std::endl;

    std::vector<std::vector<size_t>> adj2(5);
    EulerTour::addEdge(&adj2, 1, 5);
    EulerTour::addEdge(&adj2, 4, 5);
    EulerTour::addEdge(&adj2, 4, 2);
    EulerTour::addEdge(&adj2, 4, 3);
    std::cout << "Initiating Test 2..." << std::endl;
    assert(EulerTour::solve(adj2, 1) == "1 5 4 2 4 3 4 5 1 ");
    std::cout << "Test 2 Passed..." << std::endl;

    std::cout << "All Test Passed..." << std::endl << std::endl;
}

/** Main function */
int main() {
    // running predefined tests
    tests();

    size_t vertices = 0, edges = 0;
    std::cout << "Enter the Vertices : ";
    std::cin >> vertices;
    std::cout << "Enter the Edges : ";
    std::cin >> edges;

    /// creating graph
    std::vector<std::vector<size_t>> adj(vertices, std::vector<size_t>());

    /// taking input for edges
    std::cout << "Enter the vertices which have edges between them : "
              << std::endl;
    while (edges--) {
        size_t u = 0, v = 0;
        std::cin >> u >> v;
        EulerTour::addEdge(&adj, u, v);
    }

    std::string ans = EulerTour::solve(adj, 1);

    std::cout << ans;
    return 0;
}
