#include<iostream>
using namespace std;

// A recursive function to find nth catalan number
unsigned long int catalan(unsigned int n)
{
	// Base case
	if (n <= 1) return 1;

	// catalan(n) is sum of catalan(i)*catalan(n-i-1)
	unsigned long int res = 0;
	for (int i=0; i<n; i++)
		res += catalan(i)*catalan(n-i-1);

	return res;
}

// Driver program to test above function
int main()
{
	for (int i=0; i<10; i++)
		cout << catalan(i) << " ";
	return 0;
}
