#include <bits/stdc++.h>
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
    vector<int> arr = {3, 2, 1, 5, 6, 4};
    int k = 2;
    cout << k << "-th smallest element is " << quickSelect(arr, 0, arr.size() - 1, k - 1) << endl;
    return 0;
}
