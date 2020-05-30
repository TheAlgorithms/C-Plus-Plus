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
    int residual_capacity[MAXN][MAXN];
    int capacity[MAXN][MAXN];  //  used while checking the flow of edge
    int total_nodes;
    int total_edges, source, sink;
    int parent[MAXN];
    std::vector<std::tuple<int, int, int> > edge_participated;
    std::bitset<MAXN> visited;
    int max_flow = 0;
    bool bfs(int source, int sink) {  //  to find the augmented - path
        memset(parent, -1, sizeof(parent));
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
    Graph() { memset(residual_capacity, 0, sizeof(residual_capacity)); }
    void set_graph(void) {
        std::cin >> total_nodes >> total_edges >> source >> sink;
        for (int start, destination, capacity_, i = 0; i < total_edges; ++i) {
            std::cin >> start >> destination >> capacity_;
            residual_capacity[start][destination] = capacity_;
            capacity[start][destination] = capacity_;
        }
    }
    void ford_fulkerson(void) {
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
    void print_flow_info(void) {
        for (int i = 0; i < total_nodes; ++i) {
            for (int j = 0; j < total_nodes; ++j) {
                if (capacity[i][j] &&
                    residual_capacity[i][j] < capacity[i][j]) {
                    edge_participated.push_back(std::make_tuple(
                        i, j, capacity[i][j] - residual_capacity[i][j]));
                }
            }
        }
        std::cout << "\nNodes : " << total_nodes << "\nMax flow: " << max_flow
                  << "\nEdge present in flow: " << edge_participated.size()
                  << '\n';
        std::cout << "\nSource\tDestination\tCapacity\total_nodes";
        for (auto& edge_data : edge_participated) {
            int source, destination, capacity_;
            std::tie(source, destination, capacity_) = edge_data;
            std::cout << source << "\t" << destination << "\t\t" << capacity_
                      << '\t';
        }
    }
};
int main(void) {
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
