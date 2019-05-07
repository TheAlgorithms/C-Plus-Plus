#include"bits/stdc++.h"
using namespace std;

vector<int> visited;
vector<vector <int>> adjlist;
vector<int> indegree;
queue<int> q;
int not_printed_verticesinted_vertices; 

void func(){
  while(!q.empty()){
    for(int &x: adjlist[q.front()]){
      indegree[x]--;
      if(indegree[x]==0) q.push(x);
    }
    cout<<q.front()<<" ";
    q.pop();
    not_printed_verticesinted_vertices--;
  }

  if(not_printed_verticesinted_vertices!=0) cout<<"\nCycle exists, so cannot do further topological sort";
}

int main(){
  int v,e,m,n;
  cin>>v>>e; //number of vertices and edges
  adjlist.resize(v+1);
  visited.resize(v+1);
  indegree.resize(v+1);

  for(int i=0;i<e;i++){
    cin>>m>>n;
    adjlist[m].push_back(n);
    indegree[n]++;
  }

  for(int i=1;i<=v;i++){
    if(indegree[i]==0) q.push(i);
  }

  not_printed_verticesinted_vertices=v;
  func();
}