#include <bits/stdc++.h>
using namespace std;

// ---------------------------- Insertion Sort ----------------------------
void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ---------------------------- Heap Sort ----------------------------
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr, int begin, int end) {
    int n = end - begin + 1;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ---------------------------- Quick Sort Partition ----------------------------
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// ---------------------------- IntroSort Utility ----------------------------
void introSortUtil(vector<int>& arr, int begin, int end, int depthLimit) {
    int size = end - begin + 1;

    // Use InsertionSort for small partitions
    if (size < 16) {
        insertionSort(arr, begin, end);
        return;
    }

    // If recursion depth limit is zero, switch to HeapSort
    if (depthLimit == 0) {
        heapSort(arr, begin, end);
        return;
    }

    int pivot = partition(arr, begin, end);
    introSortUtil(arr, begin, pivot - 1, depthLimit - 1);
    introSortUtil(arr, pivot + 1, end, depthLimit - 1);
}

// ---------------------------- IntroSort Driver ----------------------------
void introSort(vector<int>& arr) {
    int n = arr.size();
    int depthLimit = 2 * log(n);
    introSortUtil(arr, 0, n - 1, depthLimit);
}

// ---------------------------- Testing ----------------------------
int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5, 20, 15, 3, 2};

    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    introSort(arr);

    cout << "Sorted array:   ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    return 0;
}

/*
---------------------------- Complexity ----------------------------
Time Complexity:
- Best Case: O(n log n) (QuickSort dominates)
- Average Case: O(n log n)
- Worst Case: O(n log n) (due to HeapSort fallback)

Space Complexity:
- O(log n) for recursion stack (QuickSort)
*/
