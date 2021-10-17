/*
 * Author: Amit Kumar
 * Created: May 24, 2020
 * Copyright: 2020, Open-Source
 * Last Modified: May 25, 2020
 */
#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>
// std::max capacity of node in graph
const int MAXN = 505;
class Graph {
    std::vector<std::vector<int> > residual_capacity, capacity;
    int total_nodes = 0;
    int total_edges = 0, source = 0, sink = 0;
    std::vector<int> parent;
    std::vector<std::tuple<int, int, int> > edge_participated;
    std::bitset<MAXN> visited;
    int max_flow = 0;
    bool bfs(int source, int sink) {  //  to find the augmented - path
        visited.reset();
        std::queue<int> q;
        q.push(source);
        bool is_path_found = false;
        while (q.empty() == false && is_path_found == false) {
            int current_node = q.front();
            visited.set(current_node);
            q.pop();
            for (int i = 0; i < total_nodes; ++i) {
                if (residual_capacity[current_node][i] > 0 && !visited[i]) {
                    visited.set(i);
                    parent[i] = current_node;
                    if (i == sink) {
                        return true;
                    }
                    q.push(i);
                }
            }
        }
        return false;
    }

 public:
    void set_graph() {
        std::cin >> total_nodes >> total_edges >> source >> sink;
        parent = std::vector<int>(total_nodes, -1);
        capacity = residual_capacity = std::vector<std::vector<int> >(
            total_nodes, std::vector<int>(total_nodes));
        for (int start = 0, destination = 0, capacity_ = 0, i = 0;
             i < total_edges; ++i) {
            std::cin >> start >> destination >> capacity_;
            residual_capacity[start][destination] = capacity_;
            capacity[start][destination] = capacity_;
        }
    }
    void ford_fulkerson() {
        while (bfs(source, sink)) {
            int current_node = sink;
            int flow = std::numeric_limits<int>::max();
            while (current_node != source) {
                int parent_ = parent[current_node];
                flow = std::min(flow, residual_capacity[parent_][current_node]);
                current_node = parent_;
            }
            current_node = sink;
            max_flow += flow;
            while (current_node != source) {
                int parent_ = parent[current_node];
                residual_capacity[parent_][current_node] -= flow;
                residual_capacity[current_node][parent_] += flow;
                current_node = parent_;
            }
        }
    }
    void print_flow_info() {
        for (int i = 0; i < total_nodes; ++i) {
            for (int j = 0; j < total_nodes; ++j) {
                if (capacity[i][j] &&
                    residual_capacity[i][j] < capacity[i][j]) {
                    edge_participated.emplace_back(std::make_tuple(
                        i, j, capacity[i][j] - residual_capacity[i][j]));
                }
            }
        }
        std::cout << "\nNodes : " << total_nodes << "\nMax flow: " << max_flow
                  << "\nEdge present in flow: " << edge_participated.size()
                  << '\n';
        std::cout << "\nSource\tDestination\tCapacity\total_nodes";
        for (auto& edge_data : edge_participated) {
            int source = 0, destination = 0, capacity_ = 0;
            std::tie(source, destination, capacity_) = edge_data;
            std::cout << source << "\t" << destination << "\t\t" << capacity_
                      << '\t';
        }
    }
};
int main() {
    /*
       Input Graph: (for testing )
        4 5 0 3
        0 1 10
        1 2 1
        1 3 1
        0 2 1
        2 3 10
     */
    Graph graph;
    graph.set_graph();
    graph.ford_fulkerson();
    graph.print_flow_info();
    return 0;
}
