/*
 *  Copyright : 2020 , MIT
 *  Author : Amit Kumar (offamitkumar)
 *  Last Modified Date: May 24, 2020
 *
 */
#include <algorithm>  //  for min & max
#include <iostream>   //  for cout
#include <vector>     //  for std::vector

class Solution {
    std::vector<std::vector<int>> graph;
    std::vector<int> in_time, out_time;
    int timer = 0;
    std::vector<std::vector<int>> bridge;
    std::vector<bool> visited;
    void dfs(int current_node, int parent) {
        visited.at(current_node) = true;
        in_time[current_node] = out_time[current_node] = timer++;
        for (auto& itr : graph[current_node]) {
            if (itr == parent) {
                continue;
            }
            if (!visited[itr]) {
                dfs(itr, current_node);
                if (out_time[itr] > in_time[current_node]) {
                    bridge.push_back({itr, current_node});
                }
            }
            out_time[current_node] =
                std::min(out_time[current_node], out_time[itr]);
        }
    }

 public:
    std::vector<std::vector<int>> search_bridges(
        int n, const std::vector<std::vector<int>>& connections) {
        timer = 0;
        graph.resize(n);
        in_time.assign(n, 0);
        visited.assign(n, false);
        out_time.assign(n, 0);
        for (auto& itr : connections) {
            graph.at(itr[0]).push_back(itr[1]);
            graph.at(itr[1]).push_back(itr[0]);
        }
        dfs(0, -1);
        return bridge;
    }
};

/**
 * Main function
 */
int main() {
    Solution s1;
    int number_of_node = 5;
    std::vector<std::vector<int>> node;
    node.push_back({0, 1});
    node.push_back({1, 3});
    node.push_back({1, 2});
    node.push_back({2, 4});
    /*
     *     0 <--> 1 <---> 2
     *            ^       ^
     *            |       |
     *            |       |
     *            \/     \/
     *            3       4
     *
     *    In this graph there are 4 bridges [0,2] , [2,4] , [3,5] , [1,2]
     *
     *    I assumed that the graph is bi-directional and connected.
     *
     */
    std::vector<std::vector<int>> bridges =
        s1.search_bridges(number_of_node, node);
    std::cout << bridges.size() << " bridges found!\n";
    for (auto& itr : bridges) {
        std::cout << itr[0] << " --> " << itr[1] << '\n';
    }
    return 0;
}
