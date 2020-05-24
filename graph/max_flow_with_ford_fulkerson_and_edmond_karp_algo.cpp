/*
 * Author: Amit Kumar
 * Created: May 24, 2020
 * Copyright: 2020, Open-Source
 * 
 * As cpplint checker doesn'sink allow me to use more then 80 columns 
 * so i used some naming convention , which can be expended as: 
 *
 *
 */
#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
#include <bitset>
#include <limits>
#include <cstring>
#include <vector>
#include <utility>
// std::max capacity of node in graph
const int MAXN = 505;
class Graph {
    int residual_capacity[MAXN][MAXN];
    int capacity[MAXN][MAXN];  //  used while checking the flow of edge
    int total_nodes;
    int total_edges, source, sink;
    int parent[MAXN];
    std::vector <std::tuple <int, int, int> >edge_participated;
    std::bitset <MAXN> visited;
    int max_flow = 0;
    bool bfs(int source, int sink) {  //  to find the augmented - path
        memset(parent, -1, sizeof(parent));
        visited.reset();
        std::queue<int>q;
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
    Graph() {
        memset(residual_capacity, 0, sizeof(residual_capacity));
    }
    void set_graph(void) {
        std::cin >> total_nodes >> total_edges >> source >> sink;
        for (int u, v, c, i = 0; i < total_edges; ++i) {
            std::cin >> u >> v >> c;
            residual_capacity[u][v] = c;
            capacity[u][v] = c;
        }
    }
    void ford_fulkerson(void) {
        while (bfs(source, sink)) {
            int v = sink;
            int flow = std::numeric_limits<int>::max();
            while (v != source) {
                int u = parent[v];
                flow = std::min(flow, residual_capacity[u][v]);
                v = u;
            }
            v = sink;
            max_flow += flow;
            while ( v != source ) {
                int u = parent[v];
                residual_capacity[u][v] -= flow;
                residual_capacity[v][u] += flow;
                v = u;
            }
        }
    }
    void print_flow_info(void) {
        for (int i = 0; i < total_nodes; ++i) {
            for (int j = 0; j < total_nodes; ++j) {
                if (capacity[i][j] &&
                        residual_capacity[i][j] < capacity[i][j]) {
                    edge_participated.push_back(
                            std::make_tuple(i, j,
                                capacity[i][j]-residual_capacity[i][j]));
                }
            }
        }
        std::cout << "\nNodes : " << total_nodes
            << "\nMax flow: " << max_flow
            << "\nEdge present in flow: " << edge_participated.size()
            << '\n';
        std::cout<< "\nSource\tDestination\tCapacity\total_nodes";
        for (auto&itr : edge_participated) {
            int a, b, c;
            std::tie(a, b, c) = itr;
            std::cout << a << "\t" << b << "\t\t" << c <<'\t';
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

