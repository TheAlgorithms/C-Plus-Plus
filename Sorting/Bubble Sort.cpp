// Bubble Sort

#include<iostream>

using namespace std;

int main ()
{
	// Input
	int n;
	cout << "Enter Length of Array" << endl;
	cin >> n;
	int Array[n];
	cout << "Enter any " << n << " Numbers for Unsorted Array : " << endl;
	for (int i = 0; i < n; i++) { cin >> Array[i]; }

	// Bubble Sorting
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n-1; j++) {
			if (Array[j] > Array[j+1]) {
				int temp = Array[j];
				Array[j] = Array[j+1];
				Array[j+1] = temp;
			}
		}
	}

	// Output
	cout << "Sorted Array : " << endl;
	for(int i = 0; i < n; i++) {
		cout << Array[i] << "  ";
	}

    return 0;
}
