// C/C++ program for recursive implementation
// of Bubble sort
#include <bits/stdc++.h>
using namespace std;

// A function to implement bubble sort
void bubbleSort(int arr[], int n) {
  // Base case
  if (n == 1)
    return;

  int count = 0;
  // One pass of bubble sort. After
  // this pass, the largest element
  // is moved (or bubbled) to end.
  for (int i = 0; i < n - 1; i++)
    if (arr[i] > arr[i + 1]) {
      swap(arr[i], arr[i + 1]);
      count++;
    }

  // Check if any recursion happens or not
  // If any recursion is not happen then return
  if (count == 0)
    return;

  // Largest element is fixed,
  // recur for remaining array
  bubbleSort(arr, n - 1);
}

/* Function to print an array */
void printArray(int arr[], int n) {
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

// Driver program to test above functions
int main() {
  int t;
  cout << "Enter the size of array : ";
  cin >> t;
  int arr[t];
  cout << "Enter the numbers: " << endl;
  //  store input from user to array
  for (int i = 0; i < t; ++i) {
    cin >> arr[i];
  }
  int n = sizeof(arr) / sizeof(arr[0]);
  bubbleSort(arr, n);
  printf("Sorted array : \n");
  printArray(arr, n);
  return 0;
}
