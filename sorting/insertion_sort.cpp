/**
 *
 * \file
 * \brief [Insertion Sort Algorithm
 * (Insertion Sort)](https://en.wikipedia.org/wiki/Insertion_sort)
 *
 * \details
 * Insertion sort is a simple sorting algorithm that builds the final
 * sorted array one at a time. It is much less efficient compared to
 * other sorting algorithms like heap sort, merge sort or quick sort.
 * However it has several advantages such as
 * 1. Easy to implement
 * 2. For small set of data it is quite efficient
 * 3. More efficient that other Quadratic complexity algorithms like
 *    Selection sort or bubble sort.
 * 4. It's stable that is it does not change the relative order of
 *    elements with equal keys
 * 5. Works on hand means it can sort the array or list as it receives.
 *
 * It is based on the same idea that people use to sort the playing cards in
 * their hands.
 * the algorithms goes in the manner that we start iterating over the array
 * of elements as soon as we find a unsorted element that is a misplaced
 * element we place it at a sorted position.
 *
 * Example execution steps:
 * 1. Suppose initially we have
 * \f{bmatrix}{4 &3 &2 &5 &1\f}
 * 2. We start traversing from 4 till we reach 1
 * when we reach at 3 we find that it is misplaced so we take 3 and place
 * it at a correct position thus the array will become
 * \f{bmatrix}{3 &4 &2 &5 &1\f}
 * 3. In the next iteration we are at 2 we find that this is also misplaced so
 * we place it at the correct sorted position thus the array in this iteration
 * becomes
 * \f{bmatrix}{2 &3 &4 &5 &1\f}
 * 4. We do not do anything with 5 and move on to the next iteration and
 * select 1 which is misplaced and place it at correct position. Thus, we have
 * \f{bmatrix}{1 &2 &3 &4 &5\f}
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/** \namespace sorting
 * \brief Sorting algorithms
 */
namespace sorting {
/** \brief
 * Insertion Sort Function
 *
 * @tparam T type of array
 * @param [in,out] arr Array to be sorted
 * @param n Size of Array
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

/** Insertion Sort Function
 *
 * @tparam T type of array
 * @param [in,out] arr pointer to array to be sorted
 */
template <typename T>
void insertionSort(std::vector<T> *arr) {
    size_t n = arr->size();

    for (size_t i = 1; i < n; i++) {
        T temp = arr[0][i];
        int32_t j = i - 1;
        while (j >= 0 && temp < arr[0][j]) {
            arr[0][j + 1] = arr[0][j];
            j--;
        }
        arr[0][j + 1] = temp;
    }
}

}  // namespace sorting

/**
 * @brief Create a random array objecthelper function to create a random array
 *
 * @tparam T type of array
 * @param arr array to fill (must be pre-allocated)
 * @param N number of array elements
 */
template <typename T>
static void create_random_array(T *arr, int N) {
    while (N--) {
        double r = (std::rand() % 10000 - 5000) / 100.f;
        arr[N] = static_cast<T>(r);
    }
}

/** Test Cases to test algorithm */
void tests() {
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

/** Main Function */
int main() {
    /// Running predefined tests to test algorithm
    tests();

    /// For user insteraction
    size_t n;
    std::cout << "Enter the length of your array (0 to exit): ";
    std::cin >> n;
    if (n == 0) {
        return 0;
    }

    int *arr = new int[n];
    std::cout << "Enter any " << n << " Numbers for Unsorted Array : ";

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    sorting::insertionSort(arr, n);

    std::cout << "\nSorted Array : ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;
    delete[] arr;
    return 0;
}
