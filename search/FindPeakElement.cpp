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
#include <iostream>
#include <cassert>

int findPeakElement(int *array, int left, int right, int size) {
    if (size == 0) {
        return -1; // No elements in the array
    }

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if mid is a peak element
        if ((mid == 0 || array[mid] >= array[mid - 1]) && (mid == size - 1 || array[mid] >= array[mid + 1])) {
            return mid;
        }
        // If the element to the right of mid is greater, move right
        else if (mid < size - 1 && array[mid] < array[mid + 1]) {
            left = mid + 1;
        }
        // Otherwise, move left
        else {
            right = mid - 1;
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
    assert(findPeakElement(array, 0, size - 1, size) == 2);

    size = 5;
    int array2[] = {5, 10, 20, 15, 5};
    assert(findPeakElement(array2, 0, size - 1, size) == 2);

    size = 4;
    int array3[] = {10, 20, 15, 2};
    assert(findPeakElement(array3, 0, size - 1, size) == 1);

    size = 1;
    int array4[] = {5};
    assert(findPeakElement(array4, 0, size - 1, size) == 0);

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

        // Input for the array elements
        std::cout << "Enter " << size << " numbers in ascending order: ";
        for (int i = 0; i < size; i++) {
            std::cin >> array[i];
        }

        int peakIndex = findPeakElement(array, 0, size - 1, size);
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

