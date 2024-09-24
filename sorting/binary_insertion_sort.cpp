#include <algorithm>  /// for algorithm functions like std::is_sorted
#include <cassert>    /// for assert to check if the sorting is correct
#include <iostream>   /// for input-output operations
#include <vector>     /// for using std::vector to store and sort the elements

/**
 * \namespace sorting
 * @brief Contains sorting algorithms
 * 
 * This namespace groups all the sorting-related algorithms together.
 */
namespace sorting {

/**
 * \brief Binary search function to find the correct position for an element.
 * 
 * This function uses binary search to determine the most suitable position for 
 * inserting a new element into an already sorted portion of the array.
 * 
 * \tparam T The type of elements in the array (e.g., int, float, etc.).
 * \param arr The array (vector) in which we are searching for the position to insert the element.
 * \param val The value to be inserted in the sorted part of the array.
 * \param low The lower bound (starting index) of the array range we are searching in.
 * \param high The upper bound (ending index) of the array range we are searching in.
 * \returns The index where the value `val` should be inserted.
 */
template <class T>
int64_t binary_search(std::vector<T> &arr, T val, int64_t low, int64_t high) {
    // If the range contains only one element, return the appropriate position
    if (high <= low) {
        // If the value to insert is greater than the element at 'low', return 'low + 1', otherwise 'low'
        return (val > arr[low]) ? (low + 1) : low;
    }

    // Calculate the middle index of the current range
    int64_t mid = low + (high - low) / 2;

    // If the value is less than the middle element, search in the left half
    if (arr[mid] > val) {
        return binary_search(arr, val, low, mid - 1);
    }
    // If the value is greater than the middle element, search in the right half
    else if (arr[mid] < val) {
        return binary_search(arr, val, mid + 1, high);
    }
    // If the value is equal to the middle element, insert it just after 'mid'
    else {
        return mid + 1;
    }
}

/**
 * \brief Binary Insertion Sort function that sorts the array using binary search for insertion.
 * 
 * This function sorts the array by finding the appropriate position for each element using 
 * binary search and inserting it into the sorted part of the array. It reduces the number of 
 * comparisons compared to linear insertion sort, but the number of shifts (swaps) remains the same.
 * 
 * \tparam T The type of elements in the array (e.g., int, float, etc.).
 * \param arr The array (vector) to be sorted.
 */
template <typename T>
void insertionSort_binsrch(std::vector<T> &arr) {
    int64_t n = arr.size();  // Get the size of the array

    // Traverse the array from the second element to the last
    for (int64_t i = 1; i < n; i++) {
        T key = arr[i];       // The current element to be inserted
        int64_t j = i - 1;    // The last index of the sorted part of the array

        // Find the location to insert the current element using binary search
        int64_t loc = sorting::binary_search(arr, key, 0, j);

        // Shift elements that are greater than 'key' to one position ahead
        while (j >= loc) {
            arr[j + 1] = arr[j];  // Move element to the right
            j--;
        }
        arr[j + 1] = key;  // Insert the key at the correct position
    }
}
}  // namespace sorting

/**
 * @brief Function to test the Binary Insertion Sort algorithm with different test cases.
 * 
 * This function tests the sorting algorithm using different sets of data 
 * and asserts that the array is sorted correctly after the sort operation.
 */
static void test() {
    // Test case 1: Sorting integers
    std::vector<int64_t> arr1({5, -3, -1, -2, 7});
    std::cout << "1st test... ";
    sorting::insertionSort_binsrch(arr1);  // Sort the array
    assert(std::is_sorted(arr1.begin(), arr1.end()));  // Check if the array is sorted
    std::cout << "passed" << std::endl;  // Output result if test passed

    // Test case 2: Sorting a larger set of integers
    std::vector<int64_t> arr2({12, 26, 15, 91, 32, 54, 41});
    std::cout << "2nd test... ";
    sorting::insertionSort_binsrch(arr2);  // Sort the array
    assert(std::is_sorted(arr2.begin(), arr2.end()));  // Check if the array is sorted
    std::cout << "passed" << std::endl;

    // Test case 3: Sorting floating-point numbers
    std::vector<float> arr3({7.1, -2.5, -4.0, -2.1, 5.7});
    std::cout << "3rd test... ";
    sorting::insertionSort_binsrch(arr3);  // Sort the array
    assert(std::is_sorted(arr3.begin(), arr3.end()));  // Check if the array is sorted
    std::cout << "passed" << std::endl;

    // Test case 4: Sorting another set of floating-point numbers
    std::vector<float> arr4({12.8, -3.7, -20.7, -7.1, 2.2});
    std::cout << "4th test... ";
    sorting::insertionSort_binsrch(arr4);  // Sort the array
    assert(std::is_sorted(arr4.begin(), arr4.end()));  // Check if the array is sorted
    std::cout << "passed" << std::endl;
}

/**
 * @brief Main function.
 * 
 * This is the entry point of the program. It runs the test function to verify 
 * the correctness of the Binary Insertion Sort algorithm.
 * 
 * @return 0 on successful execution.
 */
int main() {
    test();  // Run the test cases
    return 0;  // Exit the program
}
