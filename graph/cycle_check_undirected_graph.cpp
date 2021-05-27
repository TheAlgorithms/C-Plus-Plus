//union find algorithm for undirected graph
//disjoint set

#include<bits/stdc++.h>
using namespace std;

int parent[1000001];

int find(int u){//find operation is use to find the parent
    if(parent[u]==-1){
        return u;
    }
    return find(parent[u]);
}

void union1(int u,int v){//adding node v and u to the same set
    u=find(u);
    v=find(v);
    parent[u]=v;// make parent of u -> v
}

bool hasCycle(int u,int v){//checking wheter cycle is present or not
    if(find(u)==find(v)){
        return true;//if both are having same parent return true
    }
    union1(u,v);
    return false;// else return false there is no cycle
}


int main(){
    memset(parent,-1,sizeof(parent));// make parent of each node -> -1
    vector<vector<int>>edge;
    int e;// total number of edges
    cin>>e;
    bool res=false;
    for(int i=0;i<e;++i){
        int u,v;
        cin>>u>>v;
        res=hasCycle(u,v);
    }
    cout<<res<<endl;// print true if there is cylce in the graph else false if there is no cycle.
}

//  test case:
//     input
//     4
//     1 2
//     1 3
//     2 3
//     output
//     true
    
