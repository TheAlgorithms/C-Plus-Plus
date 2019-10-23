#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int tim = 0;

struct node{
    int d;
    int f;
    int color;
    int parent;
};


void addedge(vector<int> adj[],int u,int v){
    adj[u].push_back(v);
    // adj[v-1].push_back(u);
}

void DFS_visit(vector<int> adj[], struct node arr[], int u, vector<int>& mystack,int toggle,int* count){
    if(!toggle)*count = *count +1;
    tim = tim + 1;
    arr[u].d = tim;
    arr[u].color = 1;
    for(auto x: adj[u]){
        if(arr[x].color == 0){
            arr[x].parent = u;
            DFS_visit(adj, arr, x, mystack, toggle,count);
        }
    }
    tim = tim+1;
    arr[u].f = tim;
    if(toggle)mystack.push_back(u);  
    arr[u].color = 2;
    
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);    
	int V,E,u,v, cc=0,count, maxcount = -1,t;
	cin>>t;
	while(t--){
	    maxcount =-1;
    	cin>>V;
    	cin>>E;
    	vector<int> adj[V], adj_t[V], mystack;
    	struct node arr[V], arr_t[V];
    	
    	//making adjacency list
    	for(int i=0;i<E;i++){
    	    cin>>u>>v;
    	    addedge(adj,u,v);
    	    addedge(adj_t,v,u);
    	}
    	//initialising arrays
        for(int i=0;i<V;i++){
            arr[i].color = 0;
            arr[i].parent = -1;
            arr_t[i].color = 0;
            arr_t[i].parent = -1;
        }
        //first DFS to get order of finishing time in mystack vector
        for(int i=0;i<V;i++){
            if(arr[i].color == 0)DFS_visit(adj,arr,i ,mystack, 1,&count);
        }
        tim = 0;
        //popping elements of stack and checking for maximum length of SCC 
        while(mystack.size() != 0){
            u = mystack.back();
            if(arr_t[u].color == 0){
                count = 0;
                cc = cc +1;
                DFS_visit(adj_t, arr_t, u, mystack,0,&count);
                if(count >maxcount)maxcount = count;
            }
            mystack.pop_back();
        }
        
        //printing maxcount
        cout<<maxcount<<endl;

	}
	return 0;
}
