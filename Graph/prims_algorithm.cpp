// Spanning Tree: Given an undirected and connected graph, a spanning tree of that graph is a tree such that all nodes 
// in that tree are connected.

// A Minimum Spanning Tree is a spanning tree such that sum of weights of all edges is minimum and it is possible to reach each and every node 
// from a given node.


// Create a multiset of pairs in which the first value of the pair is weight and second value is the ndoe, i.e. multiset<pair<weight, node> > s

// We are using a multiset because multiset acts as a minimum priority queue. Values in this multiset will be sorted in increasing order of weights and
// nodes. So each time we pop node from the multiset, it will be the node with minimum distance from the previous selected node.

// Steps:
// 1-> Create a variable to store MinCost, and initialize this variable with 0
// 2-> Create a multiset and insert the root node with weight equal to 0, i.e. , s.insert(make_pair(0, root))
// 3-> Till all nodes are not visited, repeteadly pop nodes from the multiset (each of these nodes will be the node with minimum distance)
// 4-> After popping a node, add its weight to the the MinCost and mark this visited
// 5-> Loop through all its child nodes and insert all these nodes. which are not visited to the multiset



#include<iostream>
#include<set>
#include<utility>
#include<vector>

using namespace std;

int n, m;
vector< pair<int, int > > v[10000]; //vector pair used to store weight and nodes
int visited[100000];  //global visited array takes default value 0 for all positions. So all nodes are initially not visited.

int prims(int root)
{

	// multiset< pair<weight, node > > s
	multiset < pair <int, int > > s;  // multiset acts as a minimum priority queue

	s.insert(make_pair(0, root)); 

	int minCost = 0;

	//Every time node with minimum weight will be selected till the multiset is not empty
	while(!s.empty())
	{
		pair<int, int > p = *s.begin();
		s.erase(s.begin());
		int x = p.second; // node
		int w = p.first; //weight

		if(visited[x] == 1)
		{
			continue;
		}
		else
		{
			minCost += w;
			visited[x] = 1;
			for(int i=0; i<v[x].size(); i++)
			{
				int y = v[x][i].second;
				int weight = v[x][i].first;
				if(!visited[y]) // If the node is not visited, add this node to the multiset
				{
					s.insert(make_pair(weight, y));
				}
			}
		}
	}
	return minCost;
}

int main()
{
    int nodes, edges;
    cin>>nodes>>edges;

    for(int i=0; i<edges; i++)
    {
    	int x, y, w; //node1, node2, weight of edge
    	cin>>x>>y>>w;
    	v[x].push_back(make_pair(w, y));
    	v[y].push_back(make_pair(w, x));
    }

    int minCost = prims(1);
    cout<<minCost<<endl;

	return 0;
}
