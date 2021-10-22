#include<bits/stdc++.h>
using namespace std;

#define debug(x){cout<<"x : "<<x<<endl;}

void printArray(int A[], int size) {
	for (auto i = 0; i < size; i++)
		cout << A[i] << " ";
}

void mergeSort(int array[], int const begin, int const end) {
	if (begin >= end) {
		return;
	}

	auto mid = begin + (end - begin) / 2;
}

int main() {
#ifndef ONLINE_JUDGE
	//for getting input from input.txt
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int arr[] = {12, 11, 13, 5, 6, 7 };
	auto arr_size = sizeof(arr) / sizeof(int);

	cout << "Given array is \n";
	printArray(arr, arr_size);

	mergeSort(arr, 0, arr_size - 1);

	cout << "\nSorted array is \n";
	printArray(arr, arr_size);
	return 0;
}