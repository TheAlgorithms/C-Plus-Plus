/**
 *
 * \file
 * \brief [Insertion Sort Algorithm
 * (Insertion Sort)](https://en.wikipedia.org/wiki/Insertion_sort)
 *
 * \author
 *
 * \details
 * Insertion sort is a simple sorting algorithm that builds the final
 * sorted array one at a time. It is much less efficient compared to
 * other sorting algorithms like heap sort, merge sort or quick sort.
 * However it has several advantages such as
 * <pre>
 * 1 - easy to implement
 * 2 - For small set of data it is quite efficient
 * 3 - More efficient that other Quadratic complexity algorithms like
 *     Selection sort or bubble sort.
 * 4 - It's stable that is it does not change the relative order of
 *     elements with equal keys
 * 5 - Works on hand means it can sort the array or list as it receives.
 * </pre>
 *
 * It is based on the same idea that people use to sort the playing cards in
 * their hands.
 * the algorithms goes in the manner that we start iterating over the array
 * of elements as soon as we find a unsorted element that is a misplaced
 * element we place it at a sorted position.
 * 
 * Suppose initially we have
 * <pre>
 * 4 3 2 5 1
 * 
 * we start traversing from 4 till we reach 1
 * when we reach at 3 we find that it is misplaced so we take 3 and place
 * it at a correct position thus the array will become
 * 
 * 3 4 2 5 1
 *
 * in the next iteration we are at 2 we find that this is also misplaced so
 * we place it at the correct sorted position thus the array in this iteration
 * becomes
 *
 * 2 3 4 5 1
 *
 * we does not do anything with 5 and move on to the next iteration and select
 * 1 which is misplaced and place it at correct position. Thus, we have
 *
 * 1 2 3 4 5
 * </pre>
 *
 */

#include <iostream>

/** \brief
 * Insertion Sort Function
 * 
 * @param arr Array to be sorted
 * @param n Size of Array
 *
 */
void insertionSort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && temp < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

/** Main Function */
int main() {
    int n;
    std::cout << "Enter the length of your array : ";
    std::cin >> n;
    int *arr = new int[n];
    std::cout << "Enter any " << n << " Numbers for Unsorted Array : ";

    for (int i = 0; i < n; i++)  std::cin >> arr[i];

    insertionSort(arr, n);

    std::cout << "\nSorted Array : ";
    for (int i = 0; i < n; i++)  std::cout << arr[i] << " ";

    std::cout << std::endl;
    delete[] arr;
    return 0;
}
