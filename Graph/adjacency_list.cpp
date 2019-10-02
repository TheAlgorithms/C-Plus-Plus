#include<bits/stdc++.h>
using namespace std;

int main()
{
vector<int> adj[10];
int x,y,nodes,edges; 
cin>>nodes; 
cin>>edges;
cout<<"\nEnter the common edges i.e. connect the nodes\n";

for(int i=0;i<edges;i++)
{
    cin>>x>>y;
    adj[x].push_back(y);
}

for(int i=1;i<=nodes;i++)
{   cout<<endl;
    cout<<"Adjacency list of node "<<i<<":";
    for(int j=0;j<adj[i].size();++j)
        if(j==adj[i].size()-1)
            cout<<adj[i][j];
        else
            cout<<adj[i][j]<<" -> ";
            cout<<endl;
} 

return(0);

}
