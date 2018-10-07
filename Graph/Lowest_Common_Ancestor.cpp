/*
Lowest Common Ancestor
In graph theory and computer science, 
the lowest common ancestor (LCA) of two nodes v and w in a tree or 
directed acyclic graph (DAG) T is the lowest (i.e. deepest) node 
that has both v and w as descendants, where we define each node to 
be a descendant of itself (so if v has a direct connection from w, 
w is the lowest common ancestor).
*/

#include<iostream>
#include<vector>
using namespace std;

const int MAXN = 1e5;
const int logN = 22;
vector<int> adjacencyList[MAXN];
vector<int> nodeDepth(MAXN, 0);
int parentArr[MAXN][logN];
int nodeCount, queryCount;

/*
void depthFirstSearch(int, int)
A Depth first search to find the depth of
each nodes
*/

void depthFirstSearch(int node, int parent)
{
	for(int i : adjacencyList[node])
	{
		if(i == parent)
		{
			continue;
		}
		nodeDepth[i] = nodeDepth[node] + 1;
		parentArr[i][0] = node;
		depthFirstSearch(i, node);
	}
}

/*
void preProcess()
Storing Parent's information for finding LCA
*/

void preProcess()
{
	for(int j = 1; j < logN; j++)
	{
		for(int i = 1; i < nodeCount; i++)
		{
			parentArr[i][j] = parentArr[parentArr[i][j-1]][j-1];
		}
	}
}

/*
int lowestCommonAncestor(int, int)
A function which takes in 2 nodes and finds it LCA
*/

int lowestCommonAncestor(int firstNode, int secondNode)
{
	// We always keep first node with larger depth
	if(nodeDepth[firstNode] < nodeDepth[secondNode])
	{
		swap(firstNode, secondNode);
	}
	// LogN jumping till possible
	for(int j = logN - 1; j >= 0; j--)
	{
		int currentValue = 1 << j;
		if(nodeDepth[firstNode] - currentValue >= nodeDepth[secondNode])
		{
			firstNode = parentArr[firstNode][j];
		}
	}
	if(firstNode == secondNode)
	{
		return firstNode;
	}
	for(int j = logN - 1; j >= 0; j--)
	{
		if(parentArr[firstNode][j] == 0 
			|| parentArr[secondNode][j] == 0 
			|| parentArr[firstNode][j] == parentArr[secondNode][j])
		{
			continue;
		}
		firstNode = parentArr[firstNode][j];
		secondNode = parentArr[secondNode][j];
	}
	return parentArr[firstNode][0];
}

int main()
{
	//Uncomment below part for manual input
	/*
	//Input / Output
	//	4
	//	1 2
	//	1 3
	//	3 4
	//	3
	//	1 2
	//	O/P: 1
	//	2 3
	//	O/P: 1
	//	3 4
	//	O/P: 3
	nodeCount = 4;
	adjacencyList[1].push_back(2);
	adjacencyList[1].push_back(3);
	adjacencyList[3].push_back(4);
	adjacencyList[2].push_back(1);
	adjacencyList[3].push_back(1);
	adjacencyList[4].push_back(3);
	depthFirstSearch(1, 1);
	preProcess();
	queryCount = 3;
	cout << lowestCommonAncestor(1, 2) << '\n';
	cout << lowestCommonAncestor(2, 3) << '\n';
	cout << lowestCommonAncestor(3, 4) << '\n';
	*/
	cin >> nodeCount;
	for(int i = 0; i < nodeCount - 1; i++)
	{
		int fromNode, toNode;
		cin >> fromNode >> toNode;
		adjacencyList[fromNode].push_back(toNode);
		adjacencyList[toNode].push_back(fromNode);
	}
	depthFirstSearch(1, 1);
	preProcess();
	cin >> queryCount;
	while(queryCount--)
	{
		int firstNode, secondNode;
		cin >> firstNode >> secondNode;
		cout << lowestCommonAncestor(firstNode, secondNode) << '\n';
	}
	return 0;
}