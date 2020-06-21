/*
Author: immortal-j
Implementation Details
Quick sort 3 works on Dutch National Flag Algorithm
The major diffrence between simple quicksort and quick sort 3 comes in the
function quick_sort_partition3 In quick_sort_partition3 we divide the
vector/array into 3 parts i.e a[0...q_l]-->less than pivot
a[q_l+1...q_e-1]-->Equal to pivot
a[q_e...r]-->Greater than pivot
quick sort 3 works faster in some cases as compared to simple quicksort.
specially when there are many identical values.
*/
#include <cstdlib>
#include <iostream>
#include <vector>

/*This function takes first element as pivot and places
  the pivot element at its correct position in sorted
  array i.e all elements less than pivot before it and greater
  than pivot after it
*/
const std::vector<int> quick_sort_partition3(std::vector<int> &arr, int low,
                                             int high) {
  int x = arr[low]; // taking first element as pivot
  int q_l = low; // We initiate q_l to be the part that is less than the pivot
  int count = low;
  int q_e = high; // The part that is greater than the pivot
  std::vector<int> give_back(
      2); // this vector is used to return positions of higher and lower
  while (count <= q_e) {
    if (arr[count] < x) {
      std::swap(arr[q_l], arr[count]);
      q_l++;
      count++; // increment index
    } else if (arr[count] == x) {
      count++; // increment index
    } else {
      std::swap(arr[count], arr[q_e]);
      q_e -= 1;
    }
    give_back[0] = q_l;
    give_back[1] = q_e;
  }
  return give_back;
}
/*
arr-->vector to be sorted
low-->Starting index
high-->Ending Index
randomized_quick_sort is used to generate a random number in the range
low to high to work as a pivot and then the at pivot with element at first
position
*/
const void randomized_quick_sort(std::vector<int> &arr, int low, int high) {
  if (low >= high) {
    return;
  }
  int random = low + rand_r() % (high - low + 1); // provides a random index;
  std::swap(arr[low], arr[random]);
  std::vector<int> markers = quick_sort_partition3(
      arr, low,
      high); // Funtion quick_sort_partition3 is called which returns position
  randomized_quick_sort(
      arr, low,
      markers[0] -
          1); // of elements lower than above value at random index and position
  randomized_quick_sort(arr, markers[1] + 1,
                        high); // of all elements greater than above value at
                               // random index and position
}
// Driver program to test above functions
int main() {
  int sizeofvector;
  std::cin >> sizeofvector;
  std::vector<int> arr(sizeofvector);
  // Takes input
  for (size_t i = 0; i < arr.size(); ++i) {
    std::cin >> arr[i];
  }
  randomized_quick_sort(arr, 0, arr.size() - 1);
  // prints vector/array after sorting
  for (size_t i = 0; i < arr.size(); ++i) {
    std::cout << arr[i] << ' ';
  }
  std::cout << std::endl;
  return 0;
}