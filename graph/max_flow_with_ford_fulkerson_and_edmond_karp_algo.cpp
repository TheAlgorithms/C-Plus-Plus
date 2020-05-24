/*
 * Author: Amit Kumar
 * Created: May 24, 2020
 * Copyright: 2020, Open-Source
 * 
 * As cpplint checker doesn't allow me to use more then 80 columns 
 * so i used some naming convention , which can be expended as: 
 *
 * r_capacity   -> residual_capacity 
 * capacity     -> original edge capacity 
 * vis          -> visited node 
 * c_n          -> current_node
 * n            -> total number of nodes
 * m            -> total number of edges
 * s            -> source 
 * t            -> sink 
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
//  standard utility used
using std::min;
using std::max;
using std::tie;
using std::make_tuple;
using std::make_pair;
// standard containers used
using std::vector;
using std::queue;
using std::bitset;
using std::tuple;
// standard streams used
using std::cout;
using std::cin;
// max capacity of node in graph
const int MAXN = 505;
class Graph {
    int r_capacity[MAXN][MAXN];
    int capacity[MAXN][MAXN];  //  used while checking the flow of edge
    int n;
    int m, s, t;
    int parent[MAXN];
    vector <tuple <int, int, int> >edge_participated;  //  print edges present
    bitset <MAXN> vis;
    int max_flow = 0;
    bool bfs(int s, int t) {  //  to find the augmented - path
        memset(parent, -1, sizeof(parent));
        vis.reset();
        queue<int>q;
        q.push(s);
        bool is_path_found = false;
        while (q.empty() == false && is_path_found == false) {
            int c_n = q.front();
            vis.set(c_n);
            q.pop();
            for (int i = 0; i < n; ++i) {
                if (r_capacity[c_n][i] > 0 && !vis[i]) {
                    vis.set(i);
                    parent[i] = c_n;
                    if (i == t) {
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
        memset(r_capacity, 0, sizeof(r_capacity));
    }
    void set_graph(void) {
        cin >> n >> m >> s >> t;
        for (int u, v, c, i = 0; i < m; ++i) {
            cin >> u >> v >> c;
            r_capacity[u][v] = c;
            capacity[u][v] = c;
        }
    }
    void ford_fulkerson(void) {
        while (bfs(s, t)) {
            int v = t;
            int flow = std::numeric_limits<int>::max();
            while (v != s) {
                int u = parent[v];
                flow = min(flow, r_capacity[u][v]);
                v = u;
            }
            v = t;
            max_flow += flow;
            while ( v != s ) {
                int u = parent[v];
                r_capacity[u][v] -= flow;
                r_capacity[v][u] += flow;
                v = u;
            }
        }
    }
    void print_flow_info(void) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (capacity[i][j] && r_capacity[i][j] < capacity[i][j]) {
                    edge_participated.push_back(
                            make_tuple(i, j, capacity[i][j]-r_capacity[i][j]));
                }
            }
        }
        cout << "\nNodes : " << n
            << "\nMax flow: " << max_flow
            << "\nEdge present in flow: " << edge_participated.size()
            << '\n';
        cout<< "\nSource\tDestination\tCapacity\n";
        for (auto&itr : edge_participated) {
            int a, b, c;
            tie(a, b, c) = itr;
            cout << a << "\t" << b << "\t\t" << c <<'\n';
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
    Graph g1;
    g1.set_graph();
    g1.ford_fulkerson();
    g1.print_flow_info();
    return 0;
}

