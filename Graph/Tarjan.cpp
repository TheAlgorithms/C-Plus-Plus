#include<bits/stdc++.h>
using namespace std;

vector<int> g[100100];
int scc[100100], lowlink[100100], ind[100100], instack[100100];

stack<int> s;

int cnt = 1;
int cntscc = 0;

void tarjan(int node) {
    ind[node] = lowlink[node] = cnt++;
    instack[node] = 1;
    s.push(node);
    for(auto x : g[node]){
        if (ind[x] == 0) {
            tarjan(x);
            lowlink[node] = min(lowlink[node], lowlink[x]);
        }
        else if (instack[x]) lowlink[node] = min(lowlink[node], ind[x]);
    }
    if (ind[node] == lowlink[node]) {
        while(!s.empty()) {
            auto a = s.top(); s.pop();
            scc[a] = cntscc;
            instack[a] = 0;
            if (a == node) break;
        }
        cntscc++;
    }
}

int main(){
    int n, k, m;
    // node, query, edge
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1; i <= n; i++){
        int d;
        scanf("%d", &d);
        // edge connecting to node i
        for(int j = 0; j < d; j++){
            int u;
            scanf("%d", &u);
            g[i].push_back(u);
        }
    }

    for(int i = 1; i <= n; i++){
        if (ind[i] == 0) tarjan(i);
    }
    for(int i = 0; i < k; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        printf(scc[a]==scc[b]? "yes\n":"no\n");
        // in the same SCC or not in the same SCC
    }
    return 0;
}