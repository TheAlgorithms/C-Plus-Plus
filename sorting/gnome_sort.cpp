/**
 * Copyright 2020 @author beqakd
 * @file
 * A basic implementation of gnome sort algorithm.
 */

#include <iostream>  // for io operations

/**
 * Gnome sort algorithm is not the best one. But it is used widely
 * it looks two elements prev one and next one. If they are on
 * right order it forwards, otherwise it swaps elements.
 * @param arr our array of elements.
 * @param size size of given array
 * @return it just changes array of pointer so it does not needs to return.
 * time Complexity:
 *      O(n^2)
 *      Some cases it works on O(n), but overall time is O(n^2)
 */
template <class T> void gnomeSort(T arr[], int size) {
    // few easy cases
    if (size <= 1)
        return;

    int index = 0;  // initialize some variables.
    while (index < size) {
        // check for swap
        if ((index == 0) || (arr[index] >= arr[index - 1])) {
        index++;
        } else {
        std::swap(arr[index], arr[index - 1]);  // swap
        index--;
        }
    }
}

/**
 * Our main function with example of sort method.
 */
int main() {
    // Example 1. Creating array of int,
    int arr[] = {-22, 100, 150, 35, -10, 99};
    int size = sizeof(arr) / sizeof(arr[0]);
    gnomeSort(arr, size);
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n" << std::endl;

    // Example 2. Creating array of doubles.
    double double_arr[6] = {-100.2, 10.2, 20.0, 9.0, 7.5, 7.2};
    size = sizeof(double_arr) / sizeof(double_arr[0]);
    gnomeSort(double_arr, size);
    for (int i = 0; i < size; i++)
        std::cout << double_arr[i] << " ";
    return 0;
}
