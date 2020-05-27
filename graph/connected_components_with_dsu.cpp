#include <iostream>
#include <vector>
#include <set>

int N;  // denotes number of nodes;
std::vector<int> parent;
std::vector<int> siz;
void make_set() {  // function the initialize every node as it's own parent
    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        siz[i] = 1;
    }
}
// To find the component where following node belongs to
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {  // To join 2 components to belong to one
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (siz[a] < siz[b])
            std::swap(a, b);
        parent[b] = a;
        siz[a] += siz[b];
    }
}

int no_of_connected_components() {  // To find total no of connected components
    std::set<int> temp;  // temp set to count number of connected components
    for (int i = 1; i <= N; i++)
        temp.insert(find_set(i));
    return temp.size();
}

// All critical/corner cases have been taken care of.
// Input your required values: (not hardcoded)
int main() {
    std::cin >> N;
    parent.resize(N + 1);
    siz.resize(N + 1);
    make_set();
    int edges;
    std::cin >> edges;  // no of edges in the graph
    while (edges--) {
        int node_a, node_b;
        std::cin >> node_a >> node_b;
        union_sets(node_a, node_b);
    }
    std::cout << no_of_connected_components() << std::endl;
    return 0;
}
