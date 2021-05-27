//union find algorithm for undirected graph
//disjoint set

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <memory.h>
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
    int e=4;// total number of edges
    bool res=false;
    int u[3]={1,1,2};
    int v[3]={2,3,3}
    for(int i=0;i<3;++i){
        res=hasCycle(u[i],v[i]);
    }
    cout<<res<<endl;// print true if there is cylce in the graph else false if there is no cycle.
}

    
