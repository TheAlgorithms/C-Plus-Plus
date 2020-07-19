/**
 * @file
 * @brief Implementation of [Bogosort algorithm](https://en.wikipedia.org/wiki/Bogosort)
 *
 * @details
 *      In computer science, bogosort (also known as permutation sort, stupid sort, slowsort, 
 *      shotgun sort, random sort, monkey sort, bobosort or shuffle sort) is a highly inefficient 
 *      sorting algorithm based on the generate and test paradigm. Two versions of this algorithm 
 *      exist: a deterministic version that enumerates all permutations until it hits a sorted one,
 *      and a randomized version that randomly permutes its input.Randomized version is implemented here. 
 *
 * ### Algorithm
 * Shuffle the array untill array is sorted.
 *
 * @author [Deep Raval](https://github.com/imdeep2905)
 */
#include <iostream>
#include <algorithm>
#include <array>
#include <cassert>


/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {
/**
 * Function to shuffle the elements of an array. (for reference)
 * @tparam T typename of the array
 * @tparam N length of array
 * @param arr array to shuffle
 * @returns new array with elements shuffled from a given array
 */
template <typename T, size_t N>
std::array <T, N> shuffle (std::array <T, N> arr) {
    for (int i = 0; i < N; i++) {
        // Swaps i'th  index with random index (less than array size)
        std::swap(arr[i], arr[std::rand() % N]);
    }
    return arr;
}
/**
 * Implement randomized Bogosort algorithm and sort the elements of a given array.
 * @tparam T typename of the array
 * @tparam N length of array
 * @param arr array to sort
 * @returns new array with elements sorted from a given array
 */
template <typename T, size_t N>
std::array <T, N> randomized_bogosort (std::array <T, N> arr) {
    // Untill array is not sorted
    while (!std::is_sorted(arr.begin(), arr.end())) {
        std::random_shuffle(arr.begin(), arr.end());// Shuffle the array
    }
    return arr;
}

}  // namespace sorting

/**
 * Function to display array on screen 
 * @tparam T typename of the array
 * @tparam N length of array
 * @param arr array to display
 */
template <typename T, size_t N>
void show_array (const std::array <T, N> &arr) {
    for (int x : arr) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

/**
 * Function to test above algorithm
 */
void test() {
    // Test 1
    std::array <int, 5> arr1;
    for (int &x : arr1) {
        x = std::rand() % 100;
    }
    std::cout << "Original Array : ";
    show_array(arr1);
    arr1 = sorting::randomized_bogosort(arr1);
    std::cout << "Sorted Array : ";
    show_array(arr1);
    assert(std::is_sorted(arr1.begin(), arr1.end()));
    // Test 2
    std::array <int, 5> arr2;
    for (int &x : arr2) {
        x = std::rand() % 100;
    }
    std::cout << "Original Array : ";
    show_array(arr2);
    arr2 = sorting::randomized_bogosort(arr2);
    std::cout << "Sorted Array : ";
    show_array(arr2);
    assert(std::is_sorted(arr2.begin(), arr2.end()));
}

/** Driver Code */
int main() {
    // Testing
    test();
    // Example Usage
    std::array <int, 5> arr = {3, 7, 10, 4, 1}; // Defining array which we want to sort
    std::cout << "Original Array : ";
    show_array(arr);
    arr = sorting::randomized_bogosort(arr); // Callling bogo sort on it
    std::cout << "Sorted Array : ";
    show_array(arr); // Printing sorted array
    return 0;
}
