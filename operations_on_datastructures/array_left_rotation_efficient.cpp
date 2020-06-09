#include <iostream>
/**
 * This program can be used to rotate an array d times towards left.
 * Variables used:
 * n   : Size of the Array.
 * d   : Number of indices you want to rotate.
 * arr : Used to copy first d elements of the array.
 * a   : Main array used.
 * i   : Loop variable.
 * j   : Loop variable.
 * 
 * This program uses a more efficient logic to rotate the array as each element is
 * roated d times in only single iteration. This uses less time for more long
 * arrays. */
int main() {
  int n, d;
  std::cout << "Enter size of array=";
  std::cin >> n;
  std::cout << "Enter Number of indeces u want to rotate the array to left=";
  std::cin >> d;
  int *a = new int[n];
  std::cout << "Enter elements of array(seprated by space)=";
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  int *arr = new int[d];
  for (int i = 0; i < d; i++) {
    arr[i] = a[i];
  }
  int j = 0;
  for (int i = d; i < n; i++) {
    a[j] = a[i];
    j++;
  }
  j = 0;
  for (int i = n - d; i < n; i++) {
    a[i] = arr[j];
    j++;
  }

  std::cout << "Your rotated array is=";
  for (int j = 0; j < n; j++) {
    std::cout << a[j] << " ";
  }
  std::cout << "\n";
  return 0;
}
