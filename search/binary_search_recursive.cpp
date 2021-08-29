/**
 * @file
 * @brief [Recursive implementation of the binary search
 * algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm)
 * @author [Shane Kadish](https://github.com/shanekadish)
 * @see binary_search.cpp
 */

#include <cassert>   /// for assert
#include <iostream>  /// for io operations

/**
 * @namespace search
 * @brief Search algorithms
 */
namespace search {

/** binary_search_recursive function
 * \param [in] arr array to search
 * \param [in] left left pointer
 * \param [in] right right pointer
 * \param [in] key value to find
 * \returns index if key is found
 * \returns -1 if key is not found
 */
int binary_search_recursive(int arr[], int left, int right, int key) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        if (key == arr[mid])
            return mid;
        else if (key < arr[mid])
            return binary_search_recursive(arr, left, mid - 1, key);
        else
            return binary_search_recursive(arr, mid + 1, right, key);
    }
    // if left and right pointers overlap, the key isn't present in the array
    return -1;
}

}  // namespace search

static void test() {
    int testArray1[6] = {2, 4, 6, 8, 10, 12};
    assert(search::binary_search_recursive(testArray1, 0, 5, 7) ==
           -1);  // should return -1 as 7 not in testArray1
    std::cout << "Test 1 passed" << std::endl;

    int testArray2[7] = {1, 3, 5, 7, 9, 11, 12};
    assert(search::binary_search_recursive(testArray2, 0, 6, 15) ==
           -1);  // should return -1 as 15 not in testArray2
    std::cout << "Test 2 passed" << std::endl;

    int testArray3[6] = {2, 4, 6, 8, 10, 12};
    assert(search::binary_search_recursive(testArray3, 0, 5, 12) ==
           5);  // should return 5 as 12 is at index 5 in testArray3
    std::cout << "Test 3 passed" << std::endl;

    int testArray4[7] = {1, 3, 5, 7, 9, 11, 12};
    assert(search::binary_search_recursive(testArray4, 0, 6, 3) ==
           1);  // should return 1 as 3 is at index 1 in testArray4
    std::cout << "Test 4 passed" << std::endl;

    int testArray5[7] = {-4, -1, 0, 1, 3, 5, 7};
    assert(search::binary_search_recursive(testArray5, 0, 6, -4) ==
           0);  // should return 0 as -4 is at index 0 in testArray5
    std::cout << "Test 5 passed" << std::endl;

    std::cout << "All tests passed" << std::endl;
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char const* argv[]) {
    test();
    int size, key;
    std::cout << "Enter array size: ";
    std::cin >> size;
    std::cout << "Enter array elements: ";

    int* arr = new int[size];

    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    std::cout << "Enter key to search for: ";
    std::cin >> key;

    int res = search::binary_search_recursive(arr, 0, size - 1, key);
    if (res != -1)
        std::cout << key << " found at index " << res << std::endl;
    else
        std::cout << key << " not found" << std::endl;

    delete[] arr;
    return 0;
}

