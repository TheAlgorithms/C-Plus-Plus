/**
 * @file
 * @brief Counting Inversions using [Merge
 Sort](https://en.wikipedia.org/wiki/Merge_sort)
 *
 * @details
 * Program to count the number of inversions in an array
 * using merge-sort.
 *
 * The count of inversions help to determine how close the array
 * is to be sorted in ASCENDING order.
 *
 * two elements a[i] and a[j] form an inversion if `a[i]` > `a[j]` and i < j
 *
 * Time Complexity --> `O(n.log n)`

 * Space Complexity --> `O(n)` ; additional array `temp[1..n]`
 * ### Algorithm

 *   1. The idea is similar to merge sort, divide the array into two equal or
 almost
 *      equal halves in each step until the base case is reached.
 *   2. Create a function merge that counts the number of inversions when two
 halves of
 *      the array are merged, create two indices i and j, i is the index for
 first half
 *      and j is an index of the second half. if `a[i]` is greater than `a[j]`,
 then there are (mid – i)
 *      inversions, Because left and right subarrays are sorted, so all the
 remaining elements
 *      in left-subarray (a[i+1], a[i+2] … a[mid]) will be greater than a[j].
 *   3. Create a recursive function to divide the array into halves and find the
 answer by summing
 *      the number of inversions is the first half, number of inversion in the
 second half and
 *      the number of inversions by merging the two.
 *   4. The base case of recursion is when there is only one element in the
 given half.
 *   5. Print the answer
 *
 * @author [Rakshit Raj](https://github.com/rakshitraj)
 */
#include <cassert>   /// for assert
#include <cstdint>   /// for typedef datatype uint64_t
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {
/**
 * @namespace inversion
 * @brief Functions for counting inversions using Merge Sort algorithm
 */
namespace inversion {

// Functions used --->
// int mergeSort(int* arr, int* temp, int left, int right);
// int merge(int* arr, int* temp, int left, int mid, int right);
// int countInversion(int* arr, const int size);
// void show(int* arr, const int size);

/**
 * @brief Function to merge two sub-arrays.
 *
 * @details
 * merge() function is called from mergeSort()
 * to merge the array after it split for sorting
 * by the mergeSort() funtion.
 *
 * In this case the merge fuction will also count and return
 * inversions detected when merging the sub arrays.
 *
 * @param arr    input array, data-menber of vector
 * @param temp   stores the resultant merged array
 * @param left   lower bound of `arr[]` and left-sub-array
 * @param mid    midpoint, upper bound of left sub-array,
 *               `(mid+1)` gives the lower bound of right-sub-array
 * @param right  upper bound of `arr[]` and right-sub-array
 * @returns number of inversions found in merge step
 */
template <typename T>
uint32_t merge(T* arr, T* temp, uint32_t left, uint32_t mid, uint32_t right) {
    uint32_t i = left;       /* i --> index of left sub-array */
    uint32_t j = mid + 1;    /* j --> index for right sub-array */
    uint32_t k = left;       /* k --> index for resultant array temp */
    uint32_t inv_count = 0;  // inversion count

    while ((i <= mid) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count +=
                (mid - i +
                 1);  // tricky; may vary depending on selection of sub-array
        }
    }
    // Add remaining elements from the larger subarray to the end of temp
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    // Copy temp[] to arr[]
    for (k = left; k <= right; k++) {
        arr[k] = temp[k];
    }
    return inv_count;
}

/**
 * @brief Implement merge Sort and count inverions while merging
 *
 * @details
 * The mergeSort() function implements Merge Sort, a
 * Divide and conquer algorithm, it divides the input
 * array into two halves and calls itself for each
 * sub-array and then calls the merge() function to
 * merge the two halves.
 *
 * @param arr   - array to be sorted
 * @param temp  - merged resultant array
 * @param left  - lower bound of array
 * @param right - upper bound of array
 * @returns number of inversions in array
 */
template <typename T>
uint32_t mergeSort(T* arr, T* temp, uint32_t left, uint32_t right) {
    uint32_t mid = 0, inv_count = 0;
    if (right > left) {
        // midpoint to split the array
        mid = (right + left) / 2;
        // Add inversions in left and right sub-arrays
        inv_count += mergeSort(arr, temp, left, mid);  // left sub-array
        inv_count += mergeSort(arr, temp, mid + 1, right);

        // inversions in the merge step
        inv_count += merge(arr, temp, left, mid, right);
    }
    return inv_count;
}

/**
 * @brief Function countInversion() returns the number of inversion
 * present in the input array. Inversions are an estimate of
 * how close or far off the array is to being sorted.
 *
 * @details
 * Number of inversions in a sorted array is 0.
 * Number of inversion in an array[1...n] sorted in
 * non-ascending order is n(n-1)/2, since each pair of elements
 * contitute an inversion.
 *
 * @param arr   - array, data member of std::vector<int>, input for counting
 * inversions
 * @param array_size    - number of elementa in the array
 * @returns number of inversions in input array, sorts the array
 */
template <class T>
uint32_t countInversion(T* arr, const uint32_t size) {
    std::vector<T> temp;
    temp.reserve(size);
    temp.assign(size, 0);
    return mergeSort(arr, temp.data(), 0, size - 1);
}

/**
 * @brief UTILITY function to print array.
 * @param arr[]   array to print
 * @param array_size    size of input array arr[]
 * @returns void
 *
 */
template <typename T>
void show(T* arr, const uint32_t array_size) {
    std::cout << "Printing array: \n";
    for (uint32_t i = 0; i < array_size; i++) {
        std::cout << " " << arr[i];
    }
    std::cout << "\n";
}

}  // namespace inversion
}  // namespace sorting

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // Test 1
    std::vector<uint64_t> arr1 = {
        100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84,
        83,  82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67,
        66,  65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50,
        49,  48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33,
        32,  31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,
        15,  14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1};
    uint32_t size1 = arr1.size();
    uint32_t inv_count1 = 4950;
    uint32_t result1 = sorting::inversion::countInversion(arr1.data(), size1);
    assert(inv_count1 == result1);
    // Test 2
    std::vector<int> arr2 = {22, 66, 75, 23, 11, 87, 2, 44, 98, 43};
    uint32_t size2 = arr2.size();
    uint32_t inv_count2 = 20;
    uint32_t result2 = sorting::inversion::countInversion(arr2.data(), size2);
    assert(inv_count2 == result2);
    // Test 3
    std::vector<double> arr3 = {33.1, 45.2, 65.4, 76.5, 1.0,
                                2.9,  5.4,  7.7,  88.9, 12.4};
    uint32_t size3 = arr3.size();
    uint32_t inv_count3 = 21;
    uint32_t result3 = sorting::inversion::countInversion(arr3.data(), size3);
    assert(inv_count3 == result3);
    // Test 4
    std::vector<char> arr4 = {'a', 'b', 'c', 'd', 'e'};
    uint32_t size4 = arr4.size();
    uint32_t inv_count4 = 0;
    uint32_t result4 = sorting::inversion::countInversion(arr4.data(), size4);
    assert(inv_count4 == result4);
}

// /**
//  * @brief Program Body contains all main funtionality
//  * @returns void
//  */
// template <typename T>
// static void body() {
//     // Input your own sequence
//     uint_t size;
//     T input;
//     std::cout << "Enter number of elements:";
//     std::cin >> size;
//
//     std::vector<T> arr;
//     arr.reserve(size);
//
//     std::cout << "Enter elements -->\n";
//     for (uint64_t i=1; i<=size; i++) {
//         std::cout << "Element "<< i <<" :";
//         std::cin >> input;
//         arr.push_back(input);
//     }
//
//     if (size != arr.size()) {
//         size = arr.size();
//     }
//
//     std::cout << "\n";
//     sorting::inversion::show(arr.data(), size);
//     std::cout << "\n";
//
//     // Counting inversions
//     std::cout << "\nThe number of inversions: "<<
//     sorting::inversion::countInversion(arr.data(), size) << "\n";
//
//     // Output sorted array
//     std::cout << "\nSorted array -->  \n";
//     sorting::inversion::show(arr.data(), size);
// }

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // Run test implementations
    // body(); // test your own array
    return 0;
}
