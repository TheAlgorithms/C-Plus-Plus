// C++ program to Count Inversions
// in an array
#include <iostream>
#include <vector>

int getInvCount(const std::vector<int>& arr, const int& n)
{
	int inv_count = 0;
	for (int i = 0; i < n - 1; i++){
		for (int j = i + 1; j < n; j++){
			if (arr[i] > arr[j]){
				inv_count+=1;
			}
		}
	}

	return inv_count;
}

// Driver Code
int main()
{
	int n=5;
	std::vector<int> arr(n);
	for(int i = 0;i < n; i++){
		arr[i] = n-i;
	}
	std::cout << "Number of inversions are " << getInvCount(arr, n) << "\n";
	return 0;
}
