/**
 * Copyright 2020 @author Abhishek Ajoy Menon
 *
 * @file
 *
 * A generic implementation of pancake_sort.
 */
#include<iostream>
/* Sorting an array of integers in ascending order

 * The algorithm finds the largest number in the array
 * and moves it to the end of the array.
 * This moving of array to the end is done by reversing the array
 * from the start to the location of the largest number (which 
 * brings the largest number to the beginning) and then reversing 
 * the whole array. The reversing process is analogous to flipping
 * pancakes, hence the name.
*/
/**
 *  flip(): Reverses arr[0..i]
 */
void flip(int arr[], int i) {
    int temp, start = 0;
    while (start < i) {
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}
/**
 * findMax(): Returns index of the  maximum element in arr[0..n-1]
 */
int findMax(int arr[], int n) {
    int mi, i;
    for (mi = 0, i = 0; i < n; ++i)
    if (arr[i] > arr[mi])
    mi = i;
    return mi;
}
/** 
 * pancakeSort(): The main function that sorts given array using flip operations
 */
void pancakeSort(int *arr, int n) {
    // Start from the complete array and
    // one by one reduce current size by one
    for (int curr_size = n; curr_size > 1; --curr_size) {
        // Find index of the  maximum element in  arr[0..curr_size-1]
        int mi = findMax(arr, curr_size);
        // Move the maximum element to end of
        // current array if it's not already at the end
        if (mi != curr_size-1) {
            // To move at the end,first move maximum number to beginning
            flip(arr, mi);
            // Now move the maximum number to end by reversing current array
            flip(arr, curr_size-1);
        }
    }
}
/**
 * main():
 * Reads the number of elements in the array 
 * and then reads the elements. The array is sorted by calling the 
 * pancakeSort function. The sorted array is then displayed.
*/
int main() {
    int arr[20];
    int n;
    std::cout << "\nEnter the no of elements:";
    std::cin >> n;
    pancakeSort(arr, n);
    std::cout << "\nEnter the elements:";
    for ( int i = 0; i < n; i++ ) {
        std::cin >> arr[i];
    }
    pancakeSort(arr, n);
    std::cout << "\nSorted Array " << std::endl;
    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << " ";
    return 0;
    std::cout << std::endl;
}
