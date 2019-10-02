#include<iostream>
#include<vector>
#define vi vector<int>
using namespace std;
const int N=2e6;

vi adj[N];
int n,val[N],q,u,v;

// BINARY LIFYING FOR CALCULATING THE PARENT OF TWO NODES IN A TREE!
// Solution to Spoj LCA - Lowest Common Ancestor

int rt;
int p[N][25],h[N];
void dfs(int x, int pp){
    p[x][0]=pp;
    for(auto xx: adj[x]) if(xx!=pp){
        h[xx]=h[x]+1;
        dfs(xx,x);
    }
}

void build(){
    for(int i=1;i<=n;i++) if(p[i][0]==i) {
        rt=i;
        break;
    }
    h[rt]=0;
    dfs(rt,rt);
    for(int j=1;j<13;j++) 
        for(int i=1;i<=n;i++)
            p[i][j]=p[p[i][j-1]][j-1];
}

int getlca(int x, int y){
    if(h[x]<h[y]) swap(x,y);
    int del= h[x]-h[y];
    for(int i=12;i>=0;i--) if(del&(1<<i)) x=p[x][i];
    if(x==y) return x;
    for(int i=12;i>=0;i--) 
        if(p[x][i]!=p[y][i]) x=p[x][i],y=p[y][i];
    return p[x][0];
}


int main(){
    int k;
    cin>>k;
    for(int j=0;j<k;j++){
        cin>>n;
        for(int i=1;i<=n;i++) adj[i].clear(),p[i][0]=i;
        for(int i=1;i<=n;i++){
            cin>>q;
            while(q--) {
                cin>>u;
                p[u][0]=i;
                adj[u].push_back(i);
                adj[i].push_back(u);
            }
        }
        build();
        cin>>q;
        cout<<"Case "<<j+1<<":\n";
        while(q--){
            cin>>u>>v;
            cout<<getlca(u,v)<<"\n";
        }
    }
    return 0;
}
