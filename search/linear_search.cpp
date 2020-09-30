/**
 * \file
 * \brief [Linear search
 * algorithm](https://en.wikipedia.org/wiki/Linear_search)
 */
#include <iostream>
using namespace std;
/**
 * Algorithm implementation
 * \param [in] array array to search in
 * \param [in] size length of array
 * \param [in] key key value to search for
 * \returns index where the key-value occurs in the array
 * \returns -1 if key-value not found
 */

/** main function */
int main() {
    int size = 0;
    std::cout << "\nEnter the size of the Array : ";
    std::cin >> size;

    int array[size];
    int key = 0;
    int index = -1;
    // Input array
    std::cout << "\nEnter the Array of " << size << " numbers : ";
    for (int i = 0; i < size; i++) {
        std::cin >> array[i];
    }

    std::cout << "\nEnter the number to be searched : ";
    std::cin >> key;

    for(int i=0;i<size;i++)
    {
        if(array[size]==key)
        {
            index = i;
            break;
        }
        break;
    }
    
    if (index != -1) {
        std::cout << "\nNumber found at index : " << index;
    } else {
        std::cout << "\nNot found";
    }

    return 0;
}
