#include <iostream>
using namespace std;

int Knapsack(int wt[], int val[], int W, int n) {
	// every recursive solution will have a base condition 
  // for base condition we need to think of the smallest valid input that we can pass 
  // array size can be atleast 0 || min weight can be 0 but not negetive; 
	if (n == 0 || W == 0)
		return 0;

	// these are the choices we are having 
	if (wt[n - 1] <= W) {
		return max(val[n - 1] + Knapsack(wt, val, W - wt[n - 1], n - 1),
		           Knapsack(wt, val, W, n - 1));
	}
	else if (wt[n - 1] > W) // if the weight is greater then the required weight there is no sence for taking that value. 
		return Knapsack(wt, val, W, n - 1); // return as it is by redusing the size of array 
	else
		return -1; 
}

int main() {
	int n,W; 
  cin >> n; // number of items
	int val[n], wt[n]; // values and weights of array
	for (int i = 0; i < n; i++)
		cin >> wt[i];
	for (int i = 0; i < n; i++)
		cin >> val[i];
	
  cin >> W; // Knapsack capacity

	cout << Knapsack(wt, val, W, n) << endl;
	return 0;
}
// T(N) = 2T(N-1) + O(1), which is simplified to O(2^N).
