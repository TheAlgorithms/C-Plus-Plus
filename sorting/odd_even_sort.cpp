#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Odd-Even Sort function
 * @param arr The array to be sorted
 * @param size The size of the array
 */
void oddEvenSort(vector<int> &arr, int size) {
    bool sorted = false;  // Initially, the array is assumed to be unsorted
    while (!sorted) {
        sorted = true;  // Assume the array is sorted

        // Perform Bubble sort on odd indexed elements
        for (int i = 1; i < size - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);  // Swap if the current element is greater than the next
                sorted = false;  // If a swap is made, array is not sorted yet
            }
        }

        // Perform Bubble sort on even indexed elements
        for (int i = 0; i < size - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);  // Swap if the current element is greater than the next
                sorted = false;  // If a swap is made, array is not sorted yet
            }
        }
    }
}

/**
 * @brief Display function to print the array
 * @param arr The array to be displayed
 * @param size The size of the array
 */
void display(const vector<int> &arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << "\n";  // Print each element of the array
    }
}

int main() {
    int size, temp;
    cout << "Enter the number of elements: ";
    cin >> size;

    vector<int> arr(size);  // Create a vector of input size

    cout << "Enter the unsorted elements:\n";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];  // Take input from the user
    }

    oddEvenSort(arr, size);  // Call the odd-even sort function

    cout << "Sorted array:\n";
    display(arr, size);  // Display the sorted array

    return 0;
}
/*
oddEvenSort: This function implements the Odd-Even Sort algorithm. It sorts the array by first processing the odd indices and then the even indices until no swaps are required.
display: A simple function to print the sorted array.
Main Function: Takes input from the user, calls the sorting function, and displays the sorted result. */
