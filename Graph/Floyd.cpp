#include <iostream>
using namespace std;
void Floyd(int **dist,int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				if (dist[i][j] > (dist[i][k] + dist[k][j]))
					dist[i][j] = dist[i][k] + dist[k][j];
			}
}
int main()
{
	int n, m;
	// n--> number of nodes, m--> number of edges
	cin >> n >> m; 
	int **dist = new int*[n];
	//initialize dist
	for (int i = 0; i < n; i++)
	{
		dist[i] = new int[n];
		for (int j = 0; j < n; j++)
			if (i == j)
				dist[i][j] = 0;
			else
				dist[i][j] = 1000000000;
	}
	//input edges
	for (int i = 0; i < m; i++)
	{
		int input_n, input_m, input_cost;
		cin >> input_n >> input_m >> input_cost;

		if (dist[input_n - 1][input_m - 1] > input_cost)
			dist[input_n - 1][input_m - 1] = input_cost;
	}
	Floyd(dist, n);

	//result print (0 is disconnected)
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (dist[i][j] == 1000000000)
				cout << 0 << " ";
			else
				cout << dist[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
