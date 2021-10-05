// C++ program to find n-th number whose binary
// representation is palindrome.
#include <bits/stdc++.h>
using namespace std;

// Finds if the kth bit is set in the binary
// representation
int isKthBitSet(int x, int k)
{
	return (x & (1 << (k - 1))) ? 1 : 0;
}

// Returns the position of leftmost set bit
// in the binary representation
int leftmostSetBit(int x)
{
	int count = 0;
	while (x) {
		count++;
		x = x >> 1;
	}
	return count;
}

// Finds whether the integer in binary
// representation is palindrome or not
int isBinPalindrome(int x)
{
	int l = leftmostSetBit(x);
	int r = 1;

	// One by one compare bits
	while (l > r) {

		// Compare left and right bits and converge
		if (isKthBitSet(x, l) != isKthBitSet(x, r))
			return 0;
		l--;
		r++;
	}
	return 1;
}

int findNthPalindrome(int n)
{
	int pal_count = 0;

	// Start from 1, traverse through
	// all the integers
	int i = 0;
	for (i = 1; i <= INT_MAX; i++) {
		if (isBinPalindrome(i)) {
			pal_count++;
		}
		// If we reach n, break the loop
		if (pal_count == n)
			break;
	}

	return i;
}

// Driver code
int main()
{
	int n = 9;
	
	// Call
	cout << findNthPalindrome(n);
}
