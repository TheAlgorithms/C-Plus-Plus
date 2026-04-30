/**
 * \file
 * \brief Linear search algorithm implementation
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * @author Unknown author
 * @author [Ritika Mukherjee](https://github.com/ritikaa17)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * \brief Algorithm implementation for linear search
 * \param [in] array array to search in
 * \param [in] size length of array
 * \param [in] key key value to search for
 * \returns index where the key-value occurs in the array
 * \returns -1 if key-value not found or invalid input
 */
int LinearSearch(int* array, int size, int key) {
    // Handle invalid input
    if (array == nullptr || size <= 0) {
        return -1;
    }

    for (int i = 0; i < size; ++i) {
        if (array[i] == key) {
            return i;
        }
    }

    return -1;
}

/**
 * @brief Self-test implementations
 */
static void tests() {
    int size = 4;
    int* array = new int[size];
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }

    assert(LinearSearch(array, size, 0) == 0);
    assert(LinearSearch(array, size, 1) == 1);
    assert(LinearSearch(array, size, 2) == 2);

    delete[] array;

    size = 6;
    array = new int[size];
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }

    assert(LinearSearch(array, size, 3) == 3);
    assert(LinearSearch(array, size, 1) == 1);
    assert(LinearSearch(array, size, 5) == 5);

    // Edge case test
    assert(LinearSearch(nullptr, 0, 5) == -1);

    std::cout << "All tests have successfully passed!\n";
    delete[] array;
}

/**
 * @brief Main function
 */
int main() {
    int mode = 0;

    std::cout << "Choose mode\n";
    std::cout << "Self-test mode (1), interactive mode (2): ";

    std::cin >> mode;

    if (mode == 2) {
        int size = 0;
        std::cout << "\nEnter the size of the array [in range 1-30 ]: ";
        std::cin >> size;

        while (size <= 0 || size > 30) {
            std::cout << "Size can only be 1-30. Please choose another value: ";
            std::cin >> size;
        }

        int* array = new int[size];
        int key = 0;

        std::cout << "Enter the array of " << size << " numbers: ";
        for (int i = 0; i < size; i++) {
            std::cin >> array[i];
        }

        std::cout << "\nEnter the number to be searched: ";
        std::cin >> key;

        int index = LinearSearch(array, size, key);
        if (index != -1) {
            std::cout << "Number found at index: " << index << "\n";
        } else {
            std::cout << "Array element not found";
        }
        delete[] array;
    } else {
        tests();
    }
    return 0;
}