#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <list>
using namespace std;
// Class Graph for modelling a graph
class Graph {
public:
        list<uint32_t>* adj;
        const size_t vrtx;
        int32_t *colors;
        int32_t chromatic;
        Graph(const uint32_t);
        ~Graph();
        Graph& addEdge(const uint32_t, const uint32_t);
        enum  Color
        {
                BLANK = -1
        };
};
Graph::Graph(const uint32_t vrtx) :
        adj(new list<uint32_t>[vrtx]),
        vrtx(vrtx),
        colors(new int32_t[vrtx]),
        chromatic(0) {
        memset(colors, BLANK, sizeof(int32_t) * vrtx);
}
Graph::~Graph() {
        delete[] this->adj;
        delete[] this->colors;
}
Graph& Graph::addEdge(const uint32_t v0, const uint32_t v1) {
        this->adj[v0].push_back(v1);
        this->adj[v1].push_back(v0);
        return *this;
}
// Worst Time Complexity O(V^2 + E)
/* Graph Coloring Algorihm
 * This Algoritm makes a "good" coloring on the given graph,
 * which mean every vertex will be coloring.
 * A vertex of graph should be a different color from their
 * adjacments.This algoritm uses Welsh–Powell technic, what
 * gives optimalization for this algorithm.It means the
 * coloring of the vertexes is ordered by degree.It is
 * because the algorihm makes a better chromotic number.
 * chromotic number = the lowest color what enought to make
 * a "good" color on the graph.
*/
void graph_coloring(Graph &graph) {
bool *ava_clrs;
auto srt = [](list<uint32_t> &ls0, list<uint32_t> &ls1) -> bool {
        return ls0.size() < ls1.size();
};
auto chr = [](int32_t &max, int32_t &clr_i) -> int32_t {
        return clr_i > max ? clr_i : max;
};
sort(graph.adj, graph.adj + graph.vrtx, srt);
ava_clrs = new bool[graph.adj->size() + 1];
for (uint32_t off(0); off < graph.vrtx; ++off) {
  memset(ava_clrs, true, sizeof(ava_clrs) - 1);
  for (auto itr = graph.adj[off].begin(); itr != graph.adj[off].end(); ++itr) {
           if (graph.colors[*itr] != graph.BLANK) {
                  ava_clrs[graph.colors[*itr]] = false;
           }
        }
   for (uint32_t color_idx(0); color_idx < sizeof(ava_clrs) - 1; ++color_idx) {
             if (ava_clrs[color_idx]) {
                     graph.colors[off] = color_idx;
                      break;
             }
       }
}
graph.chromatic = accumulate(graph.colors, graph.colors + graph.vrtx, 0, chr);
for (uint32_t idx(0); idx < graph.vrtx; ++idx) {
        cout << "Node index:" << idx << " " << graph.colors[idx] << endl;
}
cout << "Coloring chromotic number (estimation) ~ " << graph.chromatic << endl;
}
int main() {
Graph g1(7);
g1.addEdge(0, 1);
g1.addEdge(1, 2);
g1.addEdge(1, 3);
g1.addEdge(1, 6);
g1.addEdge(2, 3);
g1.addEdge(3, 4);
g1.addEdge(3, 6);
g1.addEdge(4, 5);
g1.addEdge(5, 6);
graph_coloring(g1);
return 0;
}
