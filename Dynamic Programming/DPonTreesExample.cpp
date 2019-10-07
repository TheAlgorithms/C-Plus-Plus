//
// Created by sark2 on 06-10-2019.
/*
Given a tree T of N nodes, where each node i has
Ci coins attached to it. You have to choose a
subset of nodes such that no two adjacent nodes
 (i.e. nodes connected directly by an edge)
are chosen and sum of coins attached with nodes
in chosen subset is maximum.
*/
//

#include "bits/stdc++.h"

using namespace std;
#define IOS cin.sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define cases int t;cin>>t;while(t--)
typedef long double ld;
typedef long long ll;
ll mod = 1e9 + 7;

const int N = 100010;

vector<int>adj[N];

int dp1[N], dp2[N];

int C[N];

void dfs(int V, int parent){
    int sum1 = 0, sum2 = 0;

    for(auto v : adj[V]){
        if(v == parent) continue;
        dfs(v,V);
        sum1 += dp2[v];
        sum2 += max(dp1[v], dp2[v]);
    }

    dp1[V] = C[V] + sum1;
    dp2[V] = sum2;

}

int main() {
    IOS

    int n;
    cin>>n;
    for(int i = 1; i < n; i++){
        int u, v;
        cin>>u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1,0);
    int ans = max(dp1[1], dp2[1]);
    cout<<ans<<endl;


}
