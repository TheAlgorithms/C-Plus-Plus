#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

namespace sorting {
//using array
 void radixSort(int *arr, int n) {
    int count[10];
    int* output = new int[n];
    memset(output, 0, n * sizeof(*output));
    memset(count, 0, sizeof(count));
    int max = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    int maxdigits = 0;
    while (max) {
        maxdigits++;
        max /= 10;
    }
    for (int j = 0; j < maxdigits; j++) {
        for (int i = 0; i < n; i++) {
            int t = std::pow(10, j);
            count[(arr[i] % (10 * t)) / t]++;
        }
        int k = 0;
        for (int p = 0; p < 10; p++) {
            for (int i = 0; i < n; i++) {
                int t = std::pow(10, j);
                if ((arr[i] % (10 * t)) / t == p) {
                    output[k] = arr[i];
                    k++;
                }
            }
        }
        memset(count, 0, sizeof(count));
        for (int i = 0; i < n; ++i) {
            arr[i] = output[i];
        }
    }
    delete[] output;
}
 //using  vector
 void radixSort(std::vector<int> *arr) {
    size_t n = arr->size();
    int count[10];
    int* output = new int[n];
    memset(output, 0, n * sizeof(*output));
    memset(count, 0, sizeof(count));
    int max = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[0][i] > max) {
            max = arr[0][i];
        }
    }
    int maxdigits = 0;
    while (max) {
        maxdigits++;
        max /= 10;
    }
    for (int j = 0; j < maxdigits; j++) {
        for (int i = 0; i < n; i++) {
            int t = std::pow(10, j);
            count[(arr[0][i] % (10 * t)) / t]++;
        }
        int k = 0;
        for (int p = 0; p < 10; p++) {
            for (int i = 0; i < n; i++) {
                int t = std::pow(10, j);
                if ((arr[0][i] % (10 * t)) / t == p) {
                    output[k] = arr[0][i];
                    k++;
                }
            }
        }
        memset(count, 0, sizeof(count));
        for (int i = 0; i < n; ++i) {
            arr[0][i] = output[i];
        }
    }
    delete[] output;
 }

 }

void tests() {
     // positive case using array
     int arr1[10] = {10, 99, 56, 8, 128, 1, 76, 48, 300, 4};
     std::cout << "Test 1... ";
     sorting::radixSort(arr1, 10);
     assert(std::is_sorted(arr1, arr1 + 10));
     std::cout << "passed" << '\n';

     // positiva case using vector
     std::vector<int> arr2({4, 7, 0, 17, 2, 6, 1, 15});
     std::cout << "Test 2... ";
     sorting::radixSort(&arr2);
     assert(std::is_sorted(std::begin(arr2), std::end(arr2)));
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
    std::cout << "Enter positive Integer" << n << "Numbers for Unsorted Array : ";

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    sorting::radixSort(arr, n);

    std::cout << "\nSorted Array : ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';

    delete[] arr;
    return 0;
}