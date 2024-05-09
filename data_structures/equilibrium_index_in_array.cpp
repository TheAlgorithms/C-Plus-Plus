/*
Find the Equilibrium Index of an Array.

Given a sequence arr[] of size n, this function returns
an equilibrium index (if any) or -1 if no equilibrium index exists.

The equilibrium index of an array is an index such that the sum of
elements at lower indexes is equal to the sum of elements at higher indexes.



Example Input:
arr = [-7, 1, 5, 2, -4, 3, 0]
Output: 3

*/
#include <bits/stdc++.h>
using namespace std;

int equilibrium_index(vector<int> arr) {
	/*
	Find the equilibrium index of an array.
	
	Args:
		arr (vector<int>): The input array of integers.
	
	Returns:
		int: The equilibrium index or -1 if no equilibrium index exists.
	
	Examples:
		>>> equilibrium_index([-7, 1, 5, 2, -4, 3, 0])
		3
		>>> equilibrium_index([1, 2, 3, 4, 5])
		-1
		>>> equilibrium_index([1, 1, 1, 1, 1])
		2
		>>> equilibrium_index([2, 4, 6, 8, 10, 3])
		-1
	*/
	int totalSum = 0;
	for (auto &i:arr) {
	sum += i;
	}
	// can also do `int totalSum = std::accumulate(arr.begin(),arr.end());`
	int leftSum = 0; // Sum of elements to the left of the current index
	// Iterate through the array to find the equilibrium index
	for (int i = 0; i < arr.size(); ++i) {
		totalSum -= arr[i];
		if (totalSum == leftSum) {
			return i;
		}
		leftSum += arr[i];
	}
	return -1;
}


int main(void) {
	vector<int> arr;
	while (cin) {
		int x;
		cin >> x;
		arr.push_back(x);
	}
	cout << equilibrium_index(arr) << endl;
}
