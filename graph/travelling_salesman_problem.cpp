// Travelling salesman problem states that:
// Given a list of cities and the distances between each pair of cities, what is
// the shortest possible route that visits each city exactly once and returns to
// the origin city?
// This is the naive approach to solve this problem.

// References:
// https://en.wikipedia.org/wiki/Travelling_salesman_problem

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int TravellingSalesmanProblem(vector<vector<int>> cities, int src, int V) {
    vector<int> vtx;
    for (int i = 0; i < V; i++) {
        if (i != src) {
            vtx.push_back(i);
        }
    }

    // store minimum weight Hamiltonian Cycle.
    int min_path = INT_MAX;
    do {
        // store current Path weight(cost)
        int curr_weight = 0;

        // compute current path weight
        int k = src;
        for (int i = 0; i < vtx.size(); i++) {
            curr_weight += cities[k][vtx[i]];
            k = vtx[i];
        }
        curr_weight += cities[k][src];

        // update minimum
        min_path = min(min_path, curr_weight);

    } while (next_permutation(vtx.begin(), vtx.end()));

    return min_path;
}

int main() {
    vector<vector<int>> cities = {
        {0, 20, 42, 35}, {20, 0, 30, 34}, {42, 30, 0, 12}, {35, 34, 12, 0}};
    int V = cities.size();
    cout << TravellingSalesmanProblem(cities, 0, V);
}