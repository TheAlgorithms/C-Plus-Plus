/**
 * @file
 * @brief Insertion Sort Algorithm
 * @author [Dhanush S](https://github.com/Fandroid745)
 * 
 * @details
 * Insertion sort is a simple sorting algorithm that builds the final
 * sorted array one element at a time. It is much less efficient compared
 * to other sorting algorithms like heap sort, merge sort, or quick sort.
 * 
 * However, it has several advantages:
 * - Easy to implement.
 * - Efficient for small data sets.
 * - More efficient than other O(n²) algorithms like selection sort or bubble sort.
 * - Stable: it does not change the relative order of elements with equal keys.
 * 
 * Insertion sort works similarly to how people sort playing cards in their hands.
 * The algorithm iterates through the list and inserts each element into its correct 
 * position in the sorted portion of the array.
 * 
 * The time complexity of the algorithm is \f$O(n^2)\f$, and in some cases, it
 * can be \f$O(n)\f$.
 * 
 * Example execution:
 * 1. Start with the array [4, 3, 2, 5, 1].
 * 2. Insert 3 in its correct position: [3, 4, 2, 5, 1].
 * 3. Insert 2: [2, 3, 4, 5, 1].
 * 4. Continue this until the array is sorted: [1, 2, 3, 4, 5].
 */


#include <algorithm>   /// for std::is_sorted
#include <cassert>     /// for assert function in testing
#include <iostream>    /// for std::cout and std::endl
#include <vector>      /// for using std::vector

/** 
 * @namespace sorting
 * @brief Contains sorting algorithms
 */
namespace sorting {

/**
 * @brief Insertion Sort Function
 * 
 * @tparam T Type of the array elements
 * @param[in,out] arr Array to be sorted
 * @param n Size of the array
 */
template <typename T>
void insertionSort(T *arr, int n) {
    for (int i = 1; i < n; i++) {
        T temp = arr[i];
        int j = i - 1;
        while (j >= 0 && temp < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

/**
 * @brief Insertion Sort for a vector
 * 
 * @tparam T Type of the vector elements
 * @param [in,out] arr Pointer to the vector to be sorted
 */
template <typename T>
void insertionSort(std::vector<T> *arr) {
    size_t n = arr->size();

    for (size_t i = 1; i < n; i++) {
        T temp = arr->at(i);
        int32_t j = i - 1;
        while (j >= 0 && temp < arr->at(j)) {
            arr->at(j + 1) = arr->at(j);
            j--;
        }
        arr->at(j + 1) = temp;
    }
}

}  // namespace sorting

/**
 * @brief Helper function to create a random array
 * 
 * @tparam T Type of the array elements
 * @param arr Array to fill (must be pre-allocated)
 * @param N Number of elements in the array
 */
template <typename T>
static void create_random_array(T *arr, int N) {
    while (N--) {
        double r = (std::rand() % 10000 - 5000) / 100.f;
        arr[N] = static_cast<T>(r);
    }
}

/** 
 * @brief self test implementation
 * @return void
 */
static void tests() {
    int arr1[10] = {78, 34, 35, 6, 34, 56, 3, 56, 2, 4};
    std::cout << "Test 1... ";
    sorting::insertionSort(arr1, 10);
    assert(std::is_sorted(arr1, arr1 + 10));
    std::cout << "passed" << std::endl;

    int arr2[5] = {5, -3, 7, -2, 1};
    std::cout << "Test 2... ";
    sorting::insertionSort(arr2, 5);
    assert(std::is_sorted(arr2, arr2 + 5));
    std::cout << "passed" << std::endl;

    float arr3[5] = {5.6, -3.1, -3.0, -2.1, 1.8};
    std::cout << "Test 3... ";
    sorting::insertionSort(arr3, 5);
    assert(std::is_sorted(arr3, arr3 + 5));
    std::cout << "passed" << std::endl;

    std::vector<float> arr4({5.6, -3.1, -3.0, -2.1, 1.8});
    std::cout << "Test 4... ";
    sorting::insertionSort(&arr4);
    assert(std::is_sorted(std::begin(arr4), std::end(arr4)));
    std::cout << "passed" << std::endl;

    int arr5[50];
    std::cout << "Test 5... ";
    create_random_array(arr5, 50);
    sorting::insertionSort(arr5, 50);
    assert(std::is_sorted(arr5, arr5 + 50));
    std::cout << "passed" << std::endl;

    float arr6[50];
    std::cout << "Test 6... ";
    create_random_array(arr6, 50);
    sorting::insertionSort(arr6, 50);
    assert(std::is_sorted(arr6, arr6 + 50));
    std::cout << "passed" << std::endl;
}

/** 
 * @brief Main function
 * @return 0 on successful exit.
 */
int main() {
    tests(); /// run self test implementations
    return 0;
}
