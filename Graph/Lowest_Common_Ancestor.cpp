//http://www.spoj.com/problems/LCA/
/*

A tree is an undirected graph in which any two vertices are connected by exactly one simple path. In other words, 
any connected graph without cycles is a tree. - Wikipedia 
The lowest common ancestor (LCA) is a concept in graph theory and computer science. Let T be a rooted tree with N nodes. 
The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants 
(where we allow a node to be a descendant of itself). - Wikipedia
Your task in this problem is to find the LCA of any two given nodes v and w in a given tree T.

Input

The first line of input will be the number of test cases. Each test case will start with a number N the number of nodes in the tree,
 1 <= N <= 1,000. Nodes are numbered from 1 to N. The next N lines each one will start with a number M the number of child nodes of 
 the Nth node, 0 <= M <= 999 followed by M numbers the child nodes of the Nth node. The next line will be a number Q the number of
  queries you have to answer for the given tree T, 1 <= Q <= 1000. The next Q lines each one will have two number v and w in which 
  you have to find the LCA of v and w in T, 1 <= v, w <= 1,000.

Input will guarantee that there is only one root and no cycles.

*/


#include <iostream>
#include <cmath>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
#define MAXN 1234
#define fast_io ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

int P[MAXN]={0},T[MAXN]={0},L[MAXN]={0},V[MAXN]={0};
int nr,n,x,y,z;
vector< vector<int> > adj(MAXN);
void dfs(int level,int s){
    L[s] = level + 1;
    for(auto i : adj[s]){
        dfs(level+1,i);
    }
}

void func(int s,int level){
    L[s] = level+1;
    if(L[s]<nr) P[s]=1;
    else{
        if(L[s]%nr==0){
            P[s] = T[s];
        }
        else{
            P[s]=  P[T[s]];
        }
    }
    for(auto i: adj[s]){
        func(i,level+1);
    }
}

void func1(int s){
    L[s] = 0;
    queue <int> myQueue;
    myQueue.push(s);
    while (!myQueue.empty()) {
        int u = myQueue.front();
        myQueue.pop ();
        for(auto i : adj[u]){   
            L[i] = L[u] + 1;
            myQueue.push(i);
            if(L[i]<nr) P[i]=1;
            else{
                if(L[i]%nr==0){
                    P[i] = T[i];
                }
                else{
                    P[i]=  P[T[i]];
                }
            }

        }
    }
}

int query(int x,int y){
    while(P[x]!=P[y]){
        if(L[x]>L[y]){
            x = P[x];
        }
        else{
            y = P[y];
        }
    }
    while(x!=y){
        if(L[x]>L[y]){
            x = T[x];
        }
        else{
            y = T[y];
        }
    }
    return x;
}

int main(){
    fast_io;
    int t;cin >> t;
    for(int i =1;i<=t;i++){
        memset(P,0,sizeof P);
        memset(T,0,sizeof T);
        memset(L,0,sizeof L);
        for(int i=0;i<MAXN;i++) adj[i].clear();
        cin >> n;
        nr = sqrt(n);
        for(int i=0;i<n;i++){
            cin >> x;
            while(x--){
                cin >> y;
                adj[i+1].push_back(y);
                T[y] = i+1;
            }
        }
        int k;
        for(k=1;k<=n;k++) if(T[k]==0) break;
        func(k,-1);
        int q;
        cin >> q;
        cout << "Case " << i << ":"<<endl;
        while(q--){
            cin >> x>> y;
            cout << query(x,y) << endl;
        }
    }
}