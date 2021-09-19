// Selection Sort

#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter how many numbers you want for Array : " << endl; 
    cin >> n;
    int Array[n];
    cout << "Enter any " <<n << " Numbers for Unsorted Array : " << endl;

    // Input
    for (int i = 0; i < n; i++) {
        cin >> Array[i];
    }

    // Selection Sorting
    for (int i = 0; i < n; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (Array[j] < Array[min]) {
                min = j;  // Finding the smallest number in Array
            }
        }
        int temp = Array[i];
        Array[i] = Array[min];
        Array[min] = temp;
    }

    // Output
    cout << "\nSorted Array : ";
    for (int i = 0; i < n; i++) {
        cout << Array[i] << "\t";
    }
}
