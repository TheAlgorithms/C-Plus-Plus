#include <bits/stdc++.h>
using namespace std;

#define ll  long long int
#define vi  vector<int>
#define vll vector<long long int>

#define INF 1e12
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int> iii;

int main(){
    #ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    std::ios::sync_with_stdio(false);
    
    int n,m;

    cin >> n >> m;

    vector<vii> AL(n+1, vii());
    int u, v, w;
    
    for (int i = 0; i < m; ++i)
    {   
        cin >> u >> v >> w;
        // The graph here is undirected:
        AL[u].emplace_back(v, w);
        AL[v].emplace_back(u, w);
    }

    vll dist(n+1, INF);
    dist[1] = 0;
    
    vi pred(n+1, -1);
    pred[1] = 1;

    priority_queue<ii, vector<ii>, greater<ii>> pq; 
    pq.push({0, 1});

    // sort the pairs by non-decreasing distance from s
    while (!pq.empty()) {                          // main loop
        auto [d, u] = pq.top(); pq.pop();          // shortest unvisited u

        if (d > dist[u]) continue;                 // a very important check

        for (auto &[v, w] : AL[u]) {               // all edges from u
            if (dist[u]+w >= dist[v]) continue;    // not improving, skip
        
            dist[v] = dist[u]+w;                   // relax operation
            pred[v] = u;
            pq.push({dist[v], v});                 // enqueue better pair
        
        }
    }
    if(dist[n] == INF)
        cout << "-1";
    else{
        vi path;
        int current = n;
        while(current != 1){
            path.push_back(current);
            current = pred[current];
        } 
        path.push_back(current);
        reverse(path.begin(),path.end());
        for(auto x : path){
            cout << x << " "; 
        }
    }

 return 0;   

}