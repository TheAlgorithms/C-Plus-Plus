/**
 * \file
 * \brief [Linear search
 * algorithm](https://en.wikipedia.org/wiki/Linear_search)
 */
#include <iostream>

/**
 * Algorithm implementation
 * \param [in] array array to search in
 * \param [in] size length of array
 * \param [in] key key value to search for
 * \returns index where the key-value occurs in the array
 * \returns -1 if key-value not found
 */
int LinearSearch(int *array, int size, int key) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == key) {
            return i;
        }
    }

    return -1;
}

/** main function */
int main() {
    int size;
    std::cout << "\nEnter the size of the Array : ";
    std::cin >> size;

    int *array = new int[size];
    int key;

    // Input array
    std::cout << "\nEnter the Array of " << size << " numbers : ";
    for (int i = 0; i < size; i++) {
        std::cin >> array[i];
    }

    std::cout << "\nEnter the number to be searched : ";
    std::cin >> key;

    int index = LinearSearch(array, size, key);
    if (index != -1) {
        std::cout << "\nNumber found at index : " << index;
    } else {
        std::cout << "\nNot found";
    }

    delete[] array;
    return 0;
}
