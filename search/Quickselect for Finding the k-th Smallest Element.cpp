#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to partition the array and return the pivot index
int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right];
    int i = left;

    for (int j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}

// Function to find the k-th smallest element using QuickSelect
int quickSelect(vector<int>& arr, int left, int right, int k) {
    if (left == right) return arr[left]; // Base case: only one element

    int pivotIndex = partition(arr, left, right);

    if (k == pivotIndex) {
        return arr[k]; // Found the k-th smallest element
    } else if (k < pivotIndex) {
        return quickSelect(arr, left, pivotIndex - 1, k); // Search left
    } else {
        return quickSelect(arr, pivotIndex + 1, right, k); // Search right
    }
}

int main() {
    vector<int> arr = {3, 2, 1, 5, 6, 4};
    int k = 2; // We want the 2nd smallest element

    // Input validation for k
    if (k < 1 || k > arr.size()) {
        cout << "Error: k must be between 1 and " << arr.size() << endl;
        return -1;
    }

    cout << k << "-th smallest element is " << quickSelect(arr, 0, arr.size() - 1, k - 1) << endl;
    return 0;
}
