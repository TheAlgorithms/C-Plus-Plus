#include <algorithm>
#include <iostream>
using namespace std;

#define MAX 10
int n, adj[MAX][MAX];
int front = -1, rear = -1, Queue[MAX];

void CreateGraph() {
	int i, max_edge, origin, dest;
	cout<<"Enter number of Vertex\n";
	cin>>n;
	max_edge = n*(n-1);
	for(int i = 0; i <= max_edge;i ++) {
		cout<<"Enter Edge Source and Destination 0 to exit\n";
		cin>>origin>>dest;
		if(origin == 0 && dest == 0)
		break;
		
		if(origin > n || dest > n || origin < 0 || dest < 0) {
		cout<<"Invalid Edge";
		i--;	
		}
		
		else adj[origin][dest] = 1;
	}
}

int FindIndegree(int node) {
	int indegree = 0;
	for(int i=0;i<n;i++) {
		if(adj[i][node] == 1)
		indegree++;
	}
	return indegree;
}

void EnQueue(int node) {
	if(rear == MAX-1)
	cout<<"OVERFLOW";
	else {
		if(front == -1) front++;
		Queue[++rear] = node;
	}
}

int DeQueue() {
	int delnode;
	if(front == -1 || front>rear) {
		cout<<"UNDERFLOW\n";
		return -1;
	}
	else delnode = Queue[front++];
	return delnode;
}

int main()
{
	int node, topsort[MAX], indeg[MAX], delnode, j=0;
	CreateGraph();
	for(node=1; node<=n; node++) {
		indeg[node] = FindIndegree(node);
		if(indeg[node] == 0) {
			EnQueue(node);
		}
	}
	
	while(front <= rear) {
		delnode = DeQueue();
		topsort[j] = delnode;
		j++;
		
		for(node=1; node<=n; node++) {
			if(adj[delnode][node] == 1) {
				adj[delnode][node] = 0;
				indeg[node]--;
				
				if(indeg[node] == 0)
				EnQueue(node); 
			}
		}
	}
	
	cout<<"Topologocal Sort of Graph is";
	
	for(node=1; node<=n; node++){
		cout<<topsort[node];
	}
	return 0;
}

