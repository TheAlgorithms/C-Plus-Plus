// Selection Sort

#include <array>
#include <iostream>

int main() {
    std::array<int,6> Array{};
    std::cout << "\nEnter any 6 Numbers for Unsorted Array : ";

    // Input
    for (int & i : Array) {
        std::cin >> i;
    }

    // Selection Sorting
    for (int i = 0; i < 6; i++) {
        int min = i;
        for (int j = i + 1; j < 6; j++) {
            if (Array[j] < Array[min]) {
                min = j;  // Finding the smallest number in Array
            }
        }
        int temp = Array[i];
        Array[i] = Array[min];
        Array[min] = temp;
    }

    // Output
    std::cout << "\nSorted Array : ";
    for (int i : Array) {
        std::cout << i << "\t";
    }
}
