#include <iostream>
using namespace std;
class graph
{
	int v;
	list<int> *adj;

public:
	graph(int v);
	void addedge(int src, int dest);
	void printgraph();
	void bfs(int s);
};
graph::graph(int v)
{
	this->v = v;
	this->adj = new list<int>[v];
}
void graph::addedge(int src, int dest)
{
	src--;
	dest--;
	adj[src].push_back(dest);
	//adj[dest].push_back(src);
}
void graph::printgraph()
{
	for (int i = 0; i < this->v; i++)
	{
		cout << "Adjacency list of vertex " << i + 1 << " is \n";
		list<int>::iterator it;
		for (it = adj[i].begin(); it != adj[i].end(); ++it)
		{
			cout << *it + 1 << " ";
		}
		cout << endl;
	}
}
void graph::bfs(int s)
{
	bool *visited = new bool[this->v + 1];
	memset(visited, false, sizeof(bool) * (this->v + 1));
	visited[s] = true;
	list<int> q;
	q.push_back(s);
	list<int>::iterator it;
	while (!q.empty())
	{
		int u = q.front();
		cout << u << " ";
		q.pop_front();
		for (it = adj[u].begin(); it != adj[u].end(); ++it)
		{
			if (visited[*it] == false)
			{
				visited[*it] = true;
				q.push_back(*it);
			}
		}
	}
}
int main()
{
	graph g(4);
	g.addedge(1, 2);
	g.addedge(2, 3);
	g.addedge(3, 4);
	g.addedge(1, 4);
	g.addedge(1, 3);
	//g.printgraph();
	g.bfs(2);
	return 0;
}
