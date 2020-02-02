// Copyright 2020 George Tsomlektsis
#include <limits>
#include <iostream>
#include <algorithm>
#include <vector>
#define numberOfVertices 6

// Returns the index of the minimum cost in the vector.
// Note that it also checks if it's not included in the mst.
int find_minimum_cost_index(std::vector<int> cheapest_costs,
                            std::vector<bool> is_included) {
    int min = std::numeric_limits<int>::max();
    int min_index;
    for (int v = 0; v < numberOfVertices; v++) {
        if (!(is_included[v]) && cheapest_costs[v] < min) {
            min = cheapest_costs[v];
            min_index = v;
        }
    }
    return min_index;
}

// Calculates the prim algorithm on the given graph and prints out the result.
void calculatePrim(int G[numberOfVertices][numberOfVertices]) {
    // Store the result and store the cheapest costs to the root..
    // At first every cost is infinite.
    std::vector<int> result(numberOfVertices, -1),
                     cheapest_costs(numberOfVertices,
                                    std::numeric_limits<int>::max());

    // Indicates which vertices are included in the MST tree.
    std::vector<bool> is_included(numberOfVertices, false);

    cheapest_costs[0] = 0;

    for (int i = 0; i < numberOfVertices - 1; i++) {
        // Retrieve the cheapest cost vertex from
        // the vertices not included in final MST
        int minimum_cost_index = find_minimum_cost_index(cheapest_costs,
                                                        is_included);
        is_included[minimum_cost_index] = true;

        // Update the cheapest cost when
        // there is a better one and it isn't included
        // in the MST
        for (int v = 0; v < numberOfVertices; v++) {
            if (G[minimum_cost_index][v] &&
                G[minimum_cost_index][v] < cheapest_costs[v] &&
                !is_included[v]) {
                result[v] = minimum_cost_index;
                cheapest_costs[v] = G[minimum_cost_index][v];
            }
        }
    }

    // Print out the result
    std::cout << "MST Result : " << std::endl;
    std::cout << "Edges\t\tWeight" << std::endl;
    std::cout << "----------------------" << std::endl;
    for (int i = 1; i < numberOfVertices; i++) {
        int from = result[i];
        int to = i;
        int weight = G[i][from];
        std::cout << from << " -> " << to << "\t\t" << weight << std::endl;
    }
}

int main() {
    // Adjacency Matrix
    int G[numberOfVertices][numberOfVertices] =
        {{0, 4, 4, 0, 0, 0},   // 0
         {4, 0, 2, 0, 0, 0},   // 1
         {4, 2, 0, 3, 4, 2},   // 2
         {0, 0, 3, 0, 3, 0},   // 3
         {0, 0, 4, 3, 0, 3},   // 4
         {0, 0, 2, 0, 3, 0}};  // 5
    calculatePrim(G);
    return 0;
}
