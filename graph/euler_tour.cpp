//program to print the euler tour of a graph (as an array)

// including the required header files
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long int ll;

ll vis[100005];
vector<ll> matrix[100005];
vector<ll> euler_path;

// Function to perform Depth-First-Search on the graph
void dfs(ll a)
{
	// cout << a << " ";
	euler_path.push_back(a);
	vis[a] = 1;
	for (ll i = 0; i < matrix[a].size(); i++)
	{
		ll u = matrix[a][i];
		if (vis[u] == 1)
		{
			continue;
		}
		dfs(u);
		// cout << a << " ";
		euler_path.push_back(a);
	}
}

int main()
{
	ll n, m;
	cout << "\nEnter no of vertices: ";
	cin >> n;
	cout << "\nEnter no of edges: ";
	cin >> m;

	// loop for inputing the graph and storing it in matrix
	cout << "Enter the adjacent vertices: for eg if vertex 1 and 2 are adjacent and vertex 2 and 3 are adjacent\n";
	cout << "You enter - \n 1 2\n 2 3\n and so on\n Enter now:\n";
	for (ll i = 0; i < m; ++i)
	{
		ll a, b;
		cin >> a >> b;
		matrix[a].push_back(b);
		matrix[b].push_back(a);
	}

	dfs(1);
	cout << "\nThe euler path is:  ";
	for (ll i = 0; i < euler_path.size(); i++)
	{
		cout << euler_path[i] << " ";
	}
	cout << endl;
	return 0;
}