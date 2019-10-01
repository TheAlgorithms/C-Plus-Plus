using namespace std;
#include <bits/stdc++.h>//to implement stacks 
void circuit(vector<vector<int> > adj)
{
    map<int,int> edge;
    for (int i = 0; i < adj.size(); i++)
    {
        edge[i]=adj[i].size();
    }

    if(adj.size()==0){
        return ;
    }
    stack<int>path;
    vector<int> circuit;

    path.push(0);
    int curr_vertex=0;
    while (!path.empty())
    {
        if (edge[curr_vertex])
        {
            path.push(curr_vertex);
            int next_vertex=adj[curr_vertex].back();
            edge[curr_vertex]=edge[curr_vertex]-1;
            adj[curr_vertex].pop_back();
            curr_vertex=next_vertex;
        }
        else
        {
            circuit.push_back(curr_vertex);
            curr_vertex=path.top();
            path.pop();
        }
    
    }
     for (int i=circuit.size()-1; i>=0; i--) 
    { 
        cout << circuit[i]; 
        if (i) 
           cout<<" -> "; 
    } 
}

int main(){
    //to check the working of the program
    vector< vector<int> >  adj1;  
    adj1.resize(7); 
    adj1[0].push_back(1); 
    adj1[0].push_back(6); 
    adj1[1].push_back(2); 
    adj1[2].push_back(0); 
    adj1[2].push_back(3); 
    adj1[3].push_back(4); 
    adj1[4].push_back(2); 
    adj1[4].push_back(5); 
    adj1[5].push_back(0); 
    adj1[6].push_back(4); 
    circuit(adj1); 
  
    return 0; 
}