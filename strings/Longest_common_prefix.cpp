// C++ program to find longest common prefix
// of given array of words.
#include<iostream>
#include<algorithm>

using namespace std;

// Function to find the longest common prefix
string longestCommonPrefix(string ar[], int n)
{

	// If size is 0, return empty string
	if (n == 0)
		return "";

	if (n == 1)
		return ar[0];

	// Sort the given array
	sort(ar, ar + n);

	// Find the minimum length from
	// first and last string
	int en = min(ar[0].size(),
				ar[n - 1].size());

	// Now the common prefix in first and
	// last string is the longest common prefix
	string first = ar[0], last = ar[n - 1];
	int i = 0;
	while (i < en && first[i] == last[i])
		i++;

	string pre = first.substr(0, i);
	return pre;
}

// Driver Code
int main()
{
	string ar[] = {"geeksforgeeks", "geeks",
						"geek", "geezer"};
	int n = sizeof(ar) / sizeof(ar[0]);
	cout << "The longest common prefix is: "
		<< longestCommonPrefix(ar, n);
	return 0;
}
