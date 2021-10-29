// C++ program to implement
// the above approach

#include <bits/stdc++.h>
using namespace std;

// Function to find minimum
// number of fountains to be
// activated
int minCntFoun(int a[], int N)
{

	// dp[i]: Stores the position of
	// rightmost fountain that can
	// be covered by water of leftmost
	// fountain of the i-th fountain
	int dp[N];
	
	// initializing all dp[i] values to be -1,
	// so that we don't get garbage value
	for(int i=0;i<N;i++){
		dp[i]=-1;
	}

	// Stores index of leftmost fountain
	// in the range of i-th fountain
	int idxLeft;

	// Stores index of rightmost fountain
	// in the range of i-th fountain
	int idxRight;

	// Traverse the array
	for (int i = 0; i < N; i++) {
		idxLeft = max(i - a[i], 0);
		idxRight = min(i + (a[i] + 1), N);
		dp[idxLeft] = max(dp[idxLeft],
						idxRight);
	}

	// Stores count of fountains
	// needed to be activated
	int cntfount = 1;

	idxRight = dp[0];

	// Stores index of next fountain
	// that needed to be activated
	// initializing idxNext with -1
	// so that we don't get garbage value
	int idxNext=-1;

	// Traverse dp[] array
	for (int i = 0; i < N; i++)
	{
		idxNext = max(idxNext,
					dp[i]);

		// If left most fountain
		// cover all its range
		if (i == idxRight)
		{
			cntfount++;
			idxRight = idxNext;
		}
	}

	return cntfount;
}

// Driver Code
int main()
{
	int a[] = { 1, 2, 1 };
	int N = sizeof(a) / sizeof(a[0]);
	cout << minCntFoun(a, N);
}
