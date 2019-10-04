#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

int ind[MAXN], inst[MAXN], ll[MAXN];
int cnt = 1;
stack <int> s;
vector<int> g[MAXN], ArtPoint, Bridge;

void tarjan (int node, int par){
    ind[node] = ll[node] = cnt++;
    s.push(node);
    int child = 0;
    for(auto x : g[node]){
        if (!ind[x]) {
            child++;
            tarjan(x, node);
            ll[node] = min(ll[node], ll[x]);
            if ((ll[x] >= ind[node] && par != 0) || (par == 0 && child > 1)){
                // x can't reach node ( no backward edge from x to node )
                // and x can't reach any anc. of node
                // cutting node splits children of x and anc. of node
                // par != 0 to prevent case 1 -> 2 -> 3
                // par == 0 && child > 1 to prevent case 1 -> 2, 1-> 3
                ArtPoint.push_back(node);
            }
            if (ll[x] > ind[node]) {
                Bridge.push_back(node);
            }
        }
        else if (inst[x]) {
            ll[node] = min(ll[node], ind[x]);
        }
    }
}

// do tarjan (node, par) on a graph to find ArtPoint and Bridge