#include <iostream>
using namespace std;

const int D = 1000; // DP - matrix dimension

int t[D][D]; // DP matrix

int Knapsack(int wt[], int val[], int W, int n) {
	// base case
	if (n == 0 || W == 0)
		return 0;

	// if already calculated
  
  
	if (t[n][W] != -1)
		return t[n][W];
  
	// else calculate
	else {
		if (wt[n - 1] <= W)
			t[n][W] = max(val[n - 1] + Knapsack(wt, val, W - wt[n - 1], n - 1),Knapsack(wt, val, W, n - 1));
		else if (wt[n - 1] > W)
			t[n][W] = Knapsack(wt, val, W, n - 1);

		return t[n][W];
	}
}

signed main() {
	int n; cin >> n; // number of items
	int val[n], wt[n]; // values and wts array
	for (int i = 0; i < n; i++)
		cin >> wt[i];
	for (int i = 0; i < n; i++)
		cin >> val[i];
	int W; cin >> W; // capacity

	// matrix initialization
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= W; j++)
			t[i][j] = -1; // initialize matrix with -1

	cout << Knapsack(wt, val, W, n) << endl;
	return 0;
}
