// https://www.geeksforgeeks.org/sort-an-array-of-0s-1s-and-2s/
// C++ program to sort an array
// with 0, 1 and 2 in a single pass(DNF sort)
#include <iostream>

// Function to sort the input array,
// the array is assumed
// to have values in {0, 1, 2}
void sort012(int a[], int arr_size) {
    int lo = 0;
    int hi = arr_size - 1;
    int mid = 0;

    // Iterate till all the elements
    // are sorted
    while (mid <= hi) {
        switch (a[mid]) {
            // If the element is 0
            case 0:
                std::swap(a[lo++], a[mid++]);
                break;

            // If the element is 1 .
            case 1:
                mid++;
                break;

            // If the element is 2
            case 2:
                std::swap(a[mid], a[hi--]);
                break;
        }
    }
}

// Function to print array arr[]
void printArray(int arr[], int arr_size) {
    // Iterate and print every element
    for (int i = 0; i < arr_size; i++) 
        std::cout << arr[i] << " ";
}

// Driver Code
int main() {
    int arr[] = {0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    sort012(arr, n);
    std::cout << "array after segregation ";
    printArray(arr, n);
    return 0;
}
