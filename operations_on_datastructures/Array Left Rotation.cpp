#include <iostream>
/**
 * This program is used to rotate the given array d times to the left.
 * Variables:
 * int n  : Size of the Array
 * int k  : Number of indeces u want to rotate the array to left
 * int a[]: Dynamically allocated input array
 * int i  : Loop Variable
 * int j  : Loop Variable
 * 
 * This is a quite inefficient method to rotate array as it requires a lot of steps just to rotate one element d times. */
int main() {
  int n, k;
  std::cout << "Enter size of array=";
  std::cin >> n;
  std::cout << "Enter Number of indeces u want to rotate the array to left=";
  std::cin >> k;
  int *a = new int[n];
  std::cout << "Enter  elements of array=";
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  int temp = 0;
  for (int i = 0; i < k; i++) {
    temp = a[0];
    for (int j = 0; j < n; j++) {
      if (j == n - 1) {
        a[n - 1] = temp;
      } else {
        a[j] = a[j + 1];
      }
    }
  }
  std::cout << "Your rotated array is=\t";
  for (int j = 0; j < n; j++) {
    std::cout << a[j] << " ";
  }
  std::cout << "\n";
  return 0;
}
