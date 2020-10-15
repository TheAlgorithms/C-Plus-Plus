#include<bits/stdc++.h>
using namespace std;


class Graph {
	int V;
	vector<int> *adjList;
	int INF = 1e9;
public:

	Graph(int v) {
		V = v;
		adjList = new vector<int>[V];
	}

	void addEdge(int u, int v, bool bidir = true) {
		adjList[u].push_back(v);
		if (bidir) adjList[v].push_back(u);
	}

	void printList() {
		for (int i = 0; i < V; i++) {
			cout << i << "-> ";
			for (int node : adjList[i]) {
				cout << node << ", " ;
			}
			cout << endl;
		}
	}

	void dfsT(int at, int prev, vector<int>& low, vector<int>& disc, vector<bool>& visited, vector<pair<int, int>>& bridges) {
		static int t = 0;
		low[at] = disc[at] = t++;
		visited[at] = true;

		for (int to : adjList[at]) {
			if (to == prev) continue;
			if (!visited[to]) {
				dfsT(to, at, low, disc, visited, bridges);
				low[at] = min(low[at], low[to]);
				if (disc[at] < low[to]) {
					bridges.push_back(make_pair(at, to));
				}
			} else {
				low[at] = min(low[at], disc[to]);
			}
		}
	}

	void tarjans() {
		vector<int> disc (V);
		vector<int> low (V, 0);
		vector<bool> visited (V, 0);
		vector<pair<int, int>> bridges;

		for (int i = 0; i < V; i++) {
			if (!visited[i]) {
				dfsT(i, -1, low, disc, visited, bridges);
			}
		}

		for (auto b : bridges) {
			cout << b.first << " " << b.second << endl;
		}
	}

	void dfsArtPoints(int at, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<bool>& ap) {
		static int time = 0;
		disc[at] = low[at] = time++;
		int children = 0;

		for (int to : adjList[at]) {
			if (disc[to] == -1) {
				children++;
				parent[to] = at;
				dfsArtPoints(to, disc, low, parent, ap);
				low[at] = min(low[at], low[to]);

				if (parent[at] == -1 && children > 1) {
					ap[at] = true;
				}

				if (parent[at] != -1 && disc[at] <= low[to]) {
					ap[at] = true;
				}
			} else {
				low[at] = min(low[at], disc[to]);
			}
		}
	}

	void findArtPoints() {
		vector<int> disc(V, -1);
		vector<int> low(V, -1);
		vector<bool> ap(V, 0);
		vector<int> parent(V, -1);

		for (int i = 0; i < V; i++) {
			if (disc[i] == -1) {
				dfsArtPoints(i, disc, low, parent, ap);
			}
		}

		for (int i = 0; i < V; i++) {
			if (ap[i]) {
				cout << i << endl;
			}
		}
	}


	void dfsSCC(int at, vector<int>& disc, vector<int>& low, stack<int>& stk, vector<bool>& inStack) {
		static int t = 0;
		low[at] = disc[at] = t++;
		stk.push(at);
		inStack[at] = true;

		for (int to : adjList[at]) {
			if (disc[to] == -1) {
				dfsSCC(to, disc, low, stk, inStack);
				low[at] = min(low[at], low[to]);
			} else if (inStack[to]) {
				low[at] = min(low[at], disc[to]);
			}
		}

		if (low[at] == disc[at]) {
			cout << "SCC: " << endl;
			while (stk.top() != at) {
				cout << stk.top() << " ";
				inStack[stk.top()] = false;
				stk.pop();
			}
			cout << stk.top() << " ";
			inStack[stk.top()] = false;
			stk.pop();
			cout << endl;
		}
	}

	void tarjansSCC() {
		vector<int> disc(V, -1);
		vector<int> low(V, -1);
		vector<bool> inStack(V, 0);
		stack<int> stk;

		for (int i = 0; i < V; i++) {
			if (disc[i] == -1) {
				dfsSCC(i, disc, low, stk, inStack);
			}
		}

	}

};


int main() {
	pair<int, int> edges[] = {{0, 1}, {0, 2}, {1, 2}, {2, 3}, {3, 4}, {2, 5}, {5, 6}, {6, 7}, {7, 8}, {5, 8}};
	pair<int, int> SCCedges[] = {{0, 1}, {1, 2}, {1, 3}, {3, 4}, {4, 0}, {4, 5}, {4, 6}, {5, 6}, {5, 2}, {6, 5}, };
	Graph g(7);
	// for (auto e : edges) {
	// 	int u, v;
	// 	tie(u, v) = e;
	// 	g.addEdge(u, v);
	// }
	for (auto edge : SCCedges) {
		int u, v;
		tie(u, v) = edge;
		g.addEdge(u, v, false);
	}

	// g.printList();
	// g.tarjans();
	// g.findArtPoints();
	g.tarjansSCC();

}
