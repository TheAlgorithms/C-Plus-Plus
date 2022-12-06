#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

namespace sorting {

 template <typename T>
 void shellSort(T *arr, int n) {
    for (int i = n / 2; i > 0; i = i / 2) {
        for (int j = i; j < n; j++) {
            for (int k = j - i; k >= 0; k = k - i) {
                if (arr[k] < arr[k + i]) {
                    break;
                } else {
                    int temp = arr[k + i];
                    arr[k + i] = arr[k];
                    arr[k] = temp;
                }
            }
        }
    }
}

 template <typename T>
 void shellSort(std::vector<T> *arr) {
    size_t n = arr->size();
    for (int i = n / 2; i > 0; i = i / 2) {
       for (int j = i; j < n; j++) {
           for (int k = j - i; k >= 0; k = k - i) {
               if (arr[0][k] < arr[0][k + i]) {
                   break;
               } else {
                   int temp = arr[0][k + i];
                   arr[0][k + i] = arr[0][k];
                   arr[0][k] = temp;
               }
           }
       }
    }
 }
 }

void tests() {
     // positive case
     int arr1[10] = {10, 99, 56, 8, 128, 1, 76, 48, 300, 4};
     std::cout << "Test 1... ";
     sorting::shellSort(arr1, 10);
     assert(std::is_sorted(arr1, arr1 + 10));
     std::cout << "passed" << '\n';

     // negative case
     int arr2[8] = {-55, -20, -5, -77, -12, -45, -32, -10};
     std::cout << "Test 2... ";
     sorting::shellSort(arr2, 8);
     assert(std::is_sorted(arr2, arr2 + 8));
     std::cout << "passed" << '\n';

     // mix positive and negative
     int arr3[8] = {1028, 45, -60, 0, -14, 35, 7, -4};
     std::cout << "Test 3... ";
     sorting::shellSort(arr3, 8);
     assert(std::is_sorted(arr3, arr3 + 8));
     std::cout << "passed" << '\n';

     // float
     float arr4[8] = {4.0, -7.4, 0, 17.5, -2.3, 6.4, 1.5, -6.6};
     std::cout << "Test 4... ";
     sorting::shellSort(arr4, 8);
     assert(std::is_sorted(arr4, arr4 + 8));
     std::cout << "passed" << '\n';

     // using vector
     std::vector<float> arr5({4.0, -7.4, 0, 17.5, -2.3, 6.4, 1.5, -6.6});
     std::cout << "Test 5... ";
     sorting::shellSort(&arr5);
     assert(std::is_sorted(std::begin(arr5), std::end(arr5)));
     std::cout << "passed" << std::endl;
 }

int main() { 
    tests();

    // For user interaction
    size_t n;
    std::cout << "Enter the length of array (0 to exit)";
    std::cin >> n;

    if (n == 0) {
        return 0;
    }

    int *arr = new int[n];
    std::cout << "Enter any" << n << "Numbers for Unsorted Array : ";

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    sorting::shellSort(arr, n);

    std::cout << "\nSorted Array : ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';

    delete[] arr;
    return 0;
}