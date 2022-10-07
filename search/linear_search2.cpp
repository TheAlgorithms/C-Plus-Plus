/**
 * @author [Ritik Sachan](https://github.com/sachanritik1)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * \brief [Algorithm implementation for recursive linear search]
 * \param [in] array array to search in
 * \param [in] index index of element of array
 * \param [in] key key value to search for
 * \returns index where the key-value occurs in the array
 * \returns -1 if key-value not found
 */
int RecursiveLinearSearch(int array[], int index,int size, int key) {
    if(index<0 || index>=size) return -1;    // to avoid out of bound function call
     /* We reach here only in case element is not present in array, return an
     * invalid entry in that case*/
    if(index==0 && array[index]!=key) return -1;
    if(index>=0 && array[index]==key) return index;
    
    return RecursiveLinearSearch(array,index-1,size,key);
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    int size = 4;
    int *array = new int[size];
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }

    assert(RecursiveLinearSearch(array, size-1,size, 0) == 0);
    assert(RecursiveLinearSearch(array, size-1,size, 1) == 1);
    assert(RecursiveLinearSearch(array, size-1,size, 2) == 2);

    size = 6;
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }

    assert(RecursiveLinearSearch(array,size-1, size, 3) == 3);
    assert(RecursiveLinearSearch(array,size-1, size, 1) == 1);
    assert(RecursiveLinearSearch(array,size-1, size, 5) == 5);

    std::cout << "All tests have successfully passed!\n";
    delete[] array;  // free memory up
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

        std::cout << "\nEnter the number to be searched: ";
        std::cin >> key;

        int index = RecursiveLinearSearch(array,size-1, size, key);
        if (index != -1) {
            std::cout << "Number found at index: " << index << "\n";
        } else {
            std::cout << "Array element not found";
        }
        delete[] array;
    } else {
        tests();  // run self-test implementations
    }
    return 0;
}