/*The C++ program implements bitonic sort, a parallel sorting algorithm that works when the number of elements is a power of 2. 
The array is divided into two halves: one half is sorted in ascending order, and the other in descending order. These halves are then merged into a single sorted array.

Key Functions:
compAndSwap():

Purpose: Compares two elements and swaps them if needed.
*/

#include <algorithm>  // For std::swap function
#include <iostream>   // For input/output operations

// Function to compare and swap two elements based on sorting direction.
// dir = 1 means ascending order, dir = 0 means descending order.
void compAndSwap(int a[], int i, int j, int dir) {
    // If the direction and the comparison condition are satisfied, swap a[i] and a[j]
    if (dir == (a[i] > a[j]))
        std::swap(a[i], a[j]);
}

// Function to merge a bitonic sequence.
// dir = 1 means ascending order, dir = 0 means descending order.
// The array segment starts from index 'low' and contains 'cnt' elements.
void bitonicMerge(int a[], int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        // Compare and swap elements to create two halves that follow the sorting direction
        for (int i = low; i < low + k; i++)
            compAndSwap(a, i, i + k, dir);
        // Recursively merge both halves
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low + k, k, dir);
    }
}

// Function to sort a sequence into bitonic form and then merge it.
// dir = 1 means ascending order, dir = 0 means descending order.
// The array segment starts from index 'low' and contains 'cnt' elements.
void bitonicSort(int a[], int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        // First, recursively sort the first half in ascending order
        bitonicSort(a, low, k, 1);
        // Then, sort the second half in descending order
        bitonicSort(a, low + k, k, 0);
        // Finally, merge the entire sequence in the specified direction (asc/desc)
        bitonicMerge(a, low, cnt, dir);
    }
}

// Function to sort the entire array in the specified direction using bitonicSort.
// dir = 1 means ascending order, dir = 0 means descending order.
void sort(int a[], int N, int up) {
    // Start the bitonic sort from the 0th index, covering all N elements.
    bitonicSort(a, 0, N, up);
}

// Main function to execute the bitonic sort algorithm
int main() {
    // Example array to be sorted
    int a[] = {3, 7, 4, 8, 6, 2, 1, 5};
    int N = sizeof(a) / sizeof(a[0]);  // Calculate number of elements in the array

    int up = 1;  // Set sorting direction to ascending (up = 1)
    
    // Sort the array using bitonic sort
    sort(a, N, up);

    // Output the sorted array
    std::cout << "Sorted array: \n";
    for (int i = 0; i < N; i++)
        std::cout << a[i] << " ";
    
    return 0;
}

/*
->compAndSwap(): Swaps two elements based on the sorting direction.
->bitonicMerge(): Merges a bitonic sequence into the correct sorted order (either ascending or descending).
->bitonicSort(): Recursively sorts the two halves of the array in opposite orders and then merges them.
->sort(): Main function to trigger the bitonic sort over the entire array.
->main(): Driver function that initializes the array and outputs the sorted result.
   */
