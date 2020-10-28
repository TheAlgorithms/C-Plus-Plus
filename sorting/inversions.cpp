// C++ program to Count Inversions
// in an array
#include <iostream>
#include <vector>
using namespace std;

int getInvCount(vector<int>& arr, int n)
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
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	int n;
	cin>>n;
	vector<int> arr(n);
	for(int i = 0;i < n; i++){
		cin >> arr[i];
	}
	cout << "Number of inversions are " << getInvCount(arr, n) << "\n";
	return 0;
}
