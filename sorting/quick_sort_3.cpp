/*
Author: immortal-j
Implementation Details
Quick sort 3 works on Dutch National Flag Algorithm
The major diffrence between simple quicksort and quick sort 3 comes in the
function partition3 In quick_sort_partition3 we divide the vector/array into 3
parts. quick sort 3 works faster in some cases as compared to simple quicksort.
*/
#include <iostream>
// function to swap elements
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// function to print an array
void print_arr(int arr[], int n) {
  for (int i = 0; i < n; ++i)
    std::cout << arr[i] << " ";
  std::cout << "\n";
}

/* This function partitions arr[] in three parts
a) arr[l..i] contains all elements smaller than pivot
b) arr[i+1..j-1] contains all occurrences of pivot
c) arr[j..r] contains all elements greater than pivot */
void partition3(int arr[], int low, int high, int *i, int *j) {
  // To handle 2 elements
  if (high - low <= 1) {
    if (arr[high] < arr[low])
      swap(&arr[high], &arr[low]);
    *i = low;
    *j = high;
    return;
  }

  int mid = low;
  int pivot = arr[high];
  while (mid <= high) {
    if (arr[mid] < pivot)
      swap(&arr[low++], &arr[mid++]);
    else if (arr[mid] == pivot)
      mid++;
    else if (arr[mid] > pivot)
      swap(&arr[mid], &arr[high--]);
  }

  // update i and j
  *i = low - 1;
  *j = mid; // or high-1
}

// 3-way partition based quick sort
void quicksort(int arr[], int low, int high) {
  if (low >= high) // 1 or 0 elements
    return;

  int i, j;

  // i and j are passed as reference
  partition3(arr, low, high, &i, &j);

  // Recur two halves
  quicksort(arr, low, i);
  quicksort(arr, j, high);
}

// Driver program for above functions
int main() {
  int size, i;
  std::cout << "Enter Number of elements\n";
  std::cin >> size;
  int *arr = new int[size];
  for (i = 0; i < size; i++) {
    std::cin >> arr[i];
  }
  quicksort(arr, 0, size - 1);
  std::cout << "Sorted Array is:";
  print_arr(arr, size);
  std::cout << "\n";
  return 0;

}

