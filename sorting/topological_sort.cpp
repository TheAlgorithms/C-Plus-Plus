#include <algorithm>
#include <iostream>
#define MAX 10
int n, adj[MAX][MAX];
int front = -1, rear = -1, Queue[MAX];
void create_graph() {
	int i, max_edge, origin, dest;
	std::cout<<"Enter number of Vertex\n";
	std::cin>>n;
	max_edge = n*(n-1);
	for(int i = 0; i <= max_edge;i ++) {
		std::cout<<"Enter Edge Source and Destination 0 to exit\n";
		std::cin>>origin>>dest;
		if(origin == 0 && dest == 0) {
			break;
		}
		
		if(origin > n || dest > n || origin < 0 || dest < 0) {
		std::cout<<"Invalid Edge";
		i--;	
		}
		
		else {
			adj[origin][dest] = 1;
		}
	}
}
int find_in_degree(int node) {
	int indegree = 0;
	for(int i=0;i<n;i++) {
		if(adj[i][node] == 1) {
			indegree++;
		}
	}
	return indegree;
}
void en_queue(int node) {
	if(rear == MAX-1) {
		std::cout<<"OVERFLOW";
	}
	else {
		if(front == -1) {
			front++;
			Queue[++rear] = node;
		}
	}
}
int de_queue() {
	int delnode;
	if(front == -1 || front>rear) {
		std::cout<<"UNDERFLOW\n";
		return -1;
	}
	else delnode = Queue[front++];
	return delnode;
}
int main()
{
	int node, topsort[MAX], indeg[MAX], delnode, j=0;
	create_graph();
	for(node=1; node<=n; node++) {
		indeg[node] = find_in_degree(node);
		if(indeg[node] == 0) {
			en_queue(node);
		}
	}
	while(front <= rear) {
		delnode = de_queue();
		topsort[j] = delnode;
		j++;
		
		for(node=1; node<=n; node++) {
			if(adj[delnode][node] == 1) {
				adj[delnode][node] = 0;
				indeg[node]--;
				
				if(indeg[node] == 0) {
					en_queue(node); 
				}
			}
		}
	}
	std::cout<<"Topologocal Sort of Graph is";
	for(node=1; node<=n; node++){
		std::cout<<topsort[node];
	}
	return 0;
}
