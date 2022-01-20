/**
 * \file
 * \brief [Linear search
 * algorithm](https://en.wikipedia.org/wiki/Linear_search)
 *
 * @author Unknown author
 * @author [Ritika Mukherjee](https://github.com/ritikaa17)
 */

#include <iostream>   /// for IO operations

/**
 * \brief [Algorithm implementation for linear search]
 * \param [in] array array to search in
 * \param [in] size length of array
 * \param [in] key key value to search for
 * \returns index where the key-value occurs in the array
 * \returns -1 if key-value not found
 */
int LinearSearch(int *array, int size, int key) 
{
    for (int i = 0; i < size; ++i) 
    {
        if (array[i] == key) {
            return i;
        }
    }

    /* We reach here only in case element is not present in array, return an invalid entry in that case*/
    return -1;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    int size = 0;
    std::cout << "\nEnter the size of the array: ";
    std::cin >> size;

    int *array = new int[size];
    int key = 0;

    // Input for the array elements
    std::cout << "Enter the array of " << size << " numbers: ";
    for (int i = 0; i < size; i++) {
        std::cin >> array[i];
    }

    std::cout << "\nEnter the number to be searched: ";
    std::cin >> key;

    int index = LinearSearch(array, size, key);
    if (index != -1)
    {
        std::cout << "Number found at index: " << index;
    } 
    else 
    {
        std::cout << "Array element not found";
    }

    delete[] array;
    return 0;
}
