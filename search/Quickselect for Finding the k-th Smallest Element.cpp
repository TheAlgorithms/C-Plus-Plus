#include <iostream>
#include <vector>
using namespace std;

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

int quickSelect(vector<int>& arr, int left, int right, int k) {
    if (left == right) return arr[left];

    int pivotIndex = partition(arr, left, right);

    if (k == pivotIndex) {
        return arr[k];
    } else if (k < pivotIndex) {
        return quickSelect(arr, left, pivotIndex - 1, k);
    } else {
        return quickSelect(arr, pivotIndex + 1, right, k);
    }
}

int main() {
    vector<int> arr;
    int n, k;

    cout << "Enter the number of elements in the array: ";
    cin >> n;

    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        arr.push_back(num);
    }

    cout << "Enter the value of k (to find the k-th smallest element): ";
    cin >> k;

    if (k < 1 || k > n) {
        cout << "Invalid value of k. Please enter a value between 1 and " << n << "." << endl;
        return 1; // Exit with error code
    }

    cout << k << "-th smallest element is " << quickSelect(arr, 0, arr.size() - 1, k - 1) << endl;
    return 0;
}
