/*
# -*- coding: utf-8 -*-
"""
@author: MetaMemeLord-
"""
*/

#include<bits/stdc++.h>

using namespace std;

#define IO ios_base::sync_with_stdio(false)
#define TIE cin.tie(0); cout.tie(0)
#define mrep(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) mrep(i,0,n)
#define rrep(i,n) for(i=n-1;i>=0;i--)
#define pb push_back
#define mp make_pair
#define all(obj) obj.begin(), obj.end()
#define rall(obj) obj.rbegin(), obj.rend()
#define print(obj,len) for(int _=0;_ <len;_++) cout<<obj[_]<<" "; cout<<endl;
#define dbg(x) cout<<#x<<" : "<<x<<endl;
#define gcd __gcd

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

void R(auto &no)
{
    no = 0;
    bool negative = 0;
    register int c;
    no = 0;
    c = getchar();
    if (c=='-')
    {
        negative = true;
        c = getchar();
    }
    for (; (c>47 && c<58); c=getchar()) no = (no<<3) + (no<<1) + c - 48;
    if (negative) no *= -1;
}

int n,t;
vi x[10010];
map < pii, int> m;
bool done[10010];
int par[10010];

bool BFS(int src, int sink){
    queue< pii > q;
    q.push(mp(-1,src));
    int l = 1;
    while(!q.empty()){
        auto k = q.front();
        q.pop();
        if(done[k.second]) continue;
        done[k.second] = 1;
        par[k.second] = k.first;
        if(k.second == sink) return true;
        for(auto j: x[k.second]){
            if(!done[j] && m[mp(k.second,j)] > 0){
                q.push(mp(k.second, j));
            }
        }
    }
    return false;
}

int main()
{
    #ifdef LOCAL
    freopen ("input.txt","r",stdin);
    int start_s=clock();
    #endif
    R(t);
    while(t--){
        int i;
        int e;
        R(n);
        m.clear();
        fill(done,done+n,0);
        rep(i,n){
            x[i].clear();
        }
        R(e);
        rep(i,e){
            int v1, v2, c;
            R(v1); R(v2); R(c);
            m[mp(v1,v2)] = c;
            x[v1].pb(v2);
            // cout << v1 << " " << v2 << " " << m[mp(v1,v2)] << '\n';
        }
        
        int src, sink;
        R(src); R(sink);
        int maxFlow = 0;
        rep(i,n) par[i] = i;
        while(BFS(src,sink)){
            int mx = INT_MAX;
            int now = sink;
            while(par[now] != -1){
                mx = min(m[mp(par[now], now)], mx);
                now = par[now];
            }
            now = sink;
            while(now != -1){
                m[mp(par[now], now)] -= mx;
                now = par[now];
            }
            fill(done,done+n, 0);
            rep(i,n) par[i] = i;
            maxFlow += mx;
        }
        dbg(maxFlow);
    }

    #ifdef LOCAL
    cout << "Total time: " << (clock()-start_s)/double(CLOCKS_PER_SEC)*1000 <<" ms"<< endl;
    #endif
}

// TEST CASES
// 4
// 4 5
// 0 1 5
// 0 2 7
// 2 1 2
// 2 3 4
// 1 3 3
// 0 3
// 6 10
// 0 1 16
// 0 2 13
// 1 2 10
// 2 1 4
// 1 3 12
// 3 2 9
// 2 4 14
// 4 3 7
// 4 5 4
// 3 5 20
// 0 5
// 5 4
// 0 1 1
// 2 1 2
// 3 1 3
// 1 4 5
// 0 4
// 4 4
// 0 1 8
// 0 2 10
// 1 3 2
// 2 3 3
// 0 3
