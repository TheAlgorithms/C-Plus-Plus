/**
 * \file FindPeakElement.cpp
 * \brief [Find peak element in Array]
 * @author Unknown author
 * @author https://github.com/AbhineshJha 
*/

#include <cassert>   // for assert
#include <iostream>  // for IO operations

/**
 * \brief [Algorithm implementation for finding a peak element]
 * \param [in] array array to search in
 * \param [in] size length of array
 * \returns index of a peak element in the array
 * \returns -1 if no peak element is found
 */
int FindPeakElement(int *array, int size) {
    if (size == 0) {
        return -1; // No elements in the array
    }

    if (size == 1) {
        return 0;  // Single element is a peak
    }

    // Check the first element
    if (array[0] >= array[1]) {
        return 0;
    }

    // Check the last element
    if (array[size - 1] >= array[size - 2]) {
        return size - 1;
    }

    // Check elements in the middle
    for (int i = 1; i < size - 1; ++i) {
        if (array[i] >= array[i - 1] && array[i] >= array[i + 1]) {
            return i;
        }
    }

    // If no peak is found, return -1
    return -1;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    int size = 6;
    int array[] = {1, 3, 20, 4, 1, 0};
    assert(FindPeakElement(array, size) == 2);

    size = 5;
    int array2[] = {5, 10, 20, 15, 5};
    assert(FindPeakElement(array2, size) == 2);

    size = 4;
    int array3[] = {10, 20, 15, 2};
    assert(FindPeakElement(array3, size) == 1);

    size = 1;
    int array4[] = {5};
    assert(FindPeakElement(array4, size) == 0);

    std::cout << "All tests have successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
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

        int *array = new int[size];
        int key = 0;

        // Input for the array elements
        std::cout << "Enter the array of " << size << " numbers: ";
        for (int i = 0; i < size; i++) {
            std::cin >> array[i];
        }

        int peakIndex = FindPeakElement(array, size);
        if (peakIndex != -1) {
            std::cout << "Peak element is " << array[peakIndex] << " at index: " << peakIndex << std::endl;
        } else {
            std::cout << "No peak element found in the array." << std::endl;
        }

        delete[] array;
    } else {
        tests();  // run self-test implementations
    }
    return 0;
}
