// Insertion Sort

#include <iostream>

int main() {
    int n;
    std::cout << "\nEnter the length of your array : ";
    std::cin >> n;
    int *Array = new int[n];
    std::cout << "\nEnter any " << n << " Numbers for Unsorted Array : ";

    // Input
    for (int i = 0; i < n; i++) {
        std::cin >> Array[i];
    }

    // Sorting
    for (int i = 1; i < n; i++) {
        int temp = Array[i];
        int j = i - 1;
        while (j >= 0 && temp < Array[j]) {
            Array[j + 1] = Array[j];
            j--;
        }
        Array[j + 1] = temp;
    }

    // Output
    std::cout << "\nSorted Array : ";
    for (int i = 0; i < n; i++) {
        std::cout << Array[i] << "\t";
    }

    delete[] Array;
    return 0;
}
