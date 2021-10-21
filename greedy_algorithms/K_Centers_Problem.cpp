/*Given n cities and distances between every pair of cities, 
select k cities to place warehouses
such that the maximum distance of a city to a warehouse is minimized. 
*/


#include <bits/stdc++.h>
using namespace std;

int maxindex(int* dist, int n)
{
	int mi = 0;
	for (int i = 0; i < n; i++) {
		if (dist[i] > dist[mi])
			mi = i;
	}
	return mi;
}

void selectKcities(int n, int weights[4][4], int k)
{
	int* dist = new int[n];
	vector<int> centers;
	for (int i = 0; i < n; i++) {
		dist[i] = INT_MAX;
	}


	int max = 0;
	for (int i = 0; i < k; i++) {
		centers.push_back(max);
		for (int j = 0; j < n; j++) {

	
			dist[j] = min(dist[j], weights[max][j]);
		}


		max = maxindex(dist, n);
	}


	cout << endl << dist[max] << endl;


	for (int i = 0; i < centers.size(); i++) {
		cout << centers[i] << " ";
	}
	cout << endl;
}


int main()
{
	int n = 4;
	int weights[4][4] = { { 0, 4, 8, 5 },
						{ 4, 0, 10, 7 },
						{ 8, 10, 0, 9 },
						{ 5, 7, 9, 0 } };
	int k = 2;

	// Function Call
	selectKcities(n, weights, k);
}

