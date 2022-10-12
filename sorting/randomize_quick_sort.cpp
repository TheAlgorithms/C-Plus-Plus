
/*

@brief: This program implements the randomized quick sort algorithm
using hoare's partition scheme.

Quick Sort is a divide and conquer algorithm. It picks and element as
pivot and partition the given array around the picked pivot. There
are many different versions of quickSort that pick pivot in different
ways.

This the randomized version of quick sort. It picks a random element
and swaps it with the first element. This is done to avoid the worst
case scenario of quick sort.

Implementation Details:
1. The partition function takes the first element as the pivot and
   partitions the array into two parts.
2. The partition_r function takes a random element as the pivot and
   partitions the array into two parts.
3. The quicksort function recursively calls the partition_r function
    to sort the array.
4. The main function takes the input from the user and calls the
    quicksort function to sort the array.

Time Complexity: O(nlogn)
Space Complexity: O(n)


* @author [Yashasewi](https://github.com/Yashasewi)
 * @see related_file.cpp, another_file.cpp

*/

/*
Pseudocode:


quicksort(Array[], low, high)
// low is the starting index, high is the ending index
    if(low < high)
        pivot = partition_r(Array, low, high)   // pivot is partitioning index
        quicksort(Array, low, pivot)        // sort elements before partition
        quicksort(Array, pivot+1, high)    // sort elements after partition

// This function takes the array and low and high indices and
// and set random element between low and high as the pivot and partitions the array
// into two parts.

partition_r(Array[], low, high)
    pivot = random(low, high)   // pivot is the random index
    swap(Array[low], Array[pivot])  // swap the pivot with the first element
    return partition(Array, low, high)  // call the partition function



// This function takes last element as pivot, places the pivot element at
// its correct position in sorted array, and places all smaller
// (smaller than pivot) to left of pivot and all greater elements to right


partition(Array[], low, high)   // low is the starting index, high is the ending index
    pivot = Array[low]  // pivot is the first element
    i = low - 1    // index of smaller element
    j = high + 1    // index of larger element

    while(true)     // infinite loop until broken
        do  // increment the index of smaller element
            i = i + 1   // until the element is greater than pivot
        while(Array[i] < pivot) // or equal to pivot
        do  // decrement the index of larger element
            j = j - 1   // until the element is smaller than pivot
        while(Array[j] > pivot) // or equal to pivot
        if(i >= j)  // if the indexes cross each other
            return j    // return the partitioning index
        swap(Array[i], Array[j])    // swap the elements at i and j


*/

// C++ program for implementation of randomized quick sort
// using hoare's partition scheme

#include <cstdlib>  // for rand() and srand()
#include <iostream> // for cout and cin
#include<vector>    // for vector
namespace sorting {

/*
This function takes the array and low and high indices and
last element as pivot, places the pivot element at its correct
position in sorted array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
*/


int partition(std::vector<int> &arr, int low, int high) {
    int pivot = arr[low];  // pivot is the first element
    int i = low - 1;    // index of smaller element
    int j = high + 1;    // index of larger element

    while (true) {     // infinite loop until broken
        do {  // increment the index of smaller element
            i++;   // until the element is greater than pivot
        } while (arr[i] < pivot); // or equal to pivot
        do {  // decrement the index of larger element
            j--;   // until the element is smaller than pivot
        } while (arr[j] > pivot); // or equal to pivot
        if (i >= j) {  // if the indexes cross each other
            return j;    // return the partitioning index
        }
        std::swap(arr[i], arr[j]);    // swap the elements at i and j
    }
}
        /*
        This function takes the array and low and high indices and
        set random element between low and high as the pivot and partitions the array
        into two parts.
        */

int partition_r(std::vector<int> &arr, int low, int high) {
    int pivot = low + rand() % (high - low);   // pivot is the random index
    std::swap(arr[low], arr[pivot]);  // swap the pivot with the first element
    return partition(arr, low, high);  // call the partition function
}
 
        /*
        This function recursively calls the partition_r function
        to sort the array.
        */

void quicksort(std::vector<int> &arr, int low, int high) {
    if (low < high) {
        int pivot = partition_r(arr, low, high);   // pivot is partitioning index
        quicksort(arr, low, pivot);        // sort elements before partition
        quicksort(arr, pivot + 1, high);    // sort elements after partition
    }
}
}  // namespace sorting


/*
function to print the array
*/

void printArray(std::vector<int> &arr) {
    for(int i : arr) {
        std::cout << i << " ";
    }

    std::cout << std::endl;
}


/*
This is the main function.
It takes the input from the user and calls the quicksort function
to sort the array.
*/

using sorting::quicksort;

int main() {
    int n = 0;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;
    std::vector<int> arr(n);
    std::cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    quicksort(arr, 0, n - 1);
    std::cout << "Sorted array: ";
    printArray(arr);
    return 0;
}

