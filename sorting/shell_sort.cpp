#include <iostream>

int main() {
    int size = 10;
    int* array = new int[size];
    // Input
    std::cout << "\nHow many numbers do want to enter in unsorted array : ";
    std::cin >> size;
    std::cout << "\nEnter the numbers for unsorted array : ";
    for (int i = 0; i < size; i++) {
        std::cin >> array[i];
    }

    // Sorting
    for (int i = size / 2; i > 0; i = i / 2) {
        for (int j = i; j < size; j++) {
            for (int k = j - i; k >= 0; k = k - i) {
                if (array[k] < array[k + i]) {
                    break;
                } else {
                    int temp = array[k + i];
                    array[k + i] = array[k];
                    array[k] = temp;
                }
            }
        }
    }

    // Output
    std::cout << "\nSorted array : ";
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << "\t";
    }

    delete[] array;
    return 0;
}
