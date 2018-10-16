#include<iostream>
using namespace std;

int three_part_binary_search(int a[], int x, int low, int high) {
	if (low < high){
		int m1 = (low + high) / 3 + 1;
		int m2 = 2 * (low + high) / 3 + 1;

		if (x == a[m1])
			return m1;
		else if (x == a[m2])
			return m2;
		else if (x < a[m1])
			return three_part_binary_search(a, x, low, m1 - 1);
		else if (x<a[m2])
			return three_part_binary_search(a, x, m1 + 1, m2 - 1);
		else if (x>a[m2])
			return three_part_binary_search(a, x, m2 + 1, high);
	}
	else
		return -1;
}

int main() {
	int a[1000000],n,val;
	cout << "Enter the size of array: ";
	cin >> n;
	cout << "Input array elements: ";
	for(int i=0;i<n;i++)
		cin >> a[i];
	cout<<"Enter the Value to be Searched: ";
	cin >> val;
	int idx = three_part_binary_search(a, val, 0, n-1);
	if(idx==-1) 
		cout << "Value not found in the array";
	else
		cout << "Value found at position: " << idx;
	
	return 0;
}
