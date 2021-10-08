#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
//#include <boost/multiprecision/cpp_int.hpp>
// using namespace boost::multiprecision;
const int mx = 1e6 + 5;
using ll = int64_t;

std::array<ll, mx> parent;
std::array<ll,mx> sz;
ll node, edge;
std::vector<std::pair<ll, std::pair<ll, ll>>> edges;
void initial() {
    for (int i = 0; i < node + edge; ++i) {
        parent[i] = i;
        sz[i] = 1;
    }
}

int root(int i) {//path compresseion added
    if(parent[i] == i)
        return parent[i];
    return parent[i] = root(parent[i]);
}

void join(int x, int y) {//union by rank added
    int root_x = root(x);  
    int root_y = root(y);
    if(sz[root_x]>sz[root_y]){
        std::swap(root_x,root_y);
    }
    parent[root_x] = root_y;
    sz[root_y]+=sz[root_x];
}

ll kruskal() {
    ll mincost = 0;
    for (int i = 0; i < edge; ++i) {
        ll x = edges[i].second.first;
        ll y = edges[i].second.second;
        if (root(x) != root(y)) {
            mincost += edges[i].first;
            join(x, y);
        }
    }
    return mincost;
}

int main() {
    while (true) {
        int from = 0, to = 0, cost = 0, totalcost = 0;
        std::cin >> node >> edge;  // Enter the nodes and edges
        if (node == 0 && edge == 0) {
            break;  // Enter 0 0 to break out
        }
        initial();  // Initialise the parent array
        for (int i = 0; i < edge; ++i) {
            std::cin >> from >> to >> cost;
            edges.emplace_back(make_pair(cost, std::make_pair(from, to)));
            totalcost += cost;
        }
        sort(edges.begin(), edges.end());
        std::cout << kruskal() << std::endl;
        edges.clear();
    }
    return 0;
}
