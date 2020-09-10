/**
 * @file
 * @brief Counting Inversions using Merge Sort
 *
 * Program to count the number of inversions in an array
 * using merge-sort.
 * 
 * The count of inversions help to determine how close the array
 * is to being sorted in ASCENDING order.
 * 
 * two elements a[i] and a[j] form an inversion if a[i] > a[j] and i < j
 * 
 * Time Complexity --> O(n.log n)
 * Space Complexity --> O(n) ; additional arrat temp[1..n]
 * Algorithm:
 *   1. The idea is similar to merge sort, divide the array into two equal or almost 
 *      equal halves in each step until the base case is reached.
 *   2. Create a function merge that counts the number of inversions when two halves of
 *      the array are merged, create two indices i and j, i is the index for first half 
 *      and j is an index of the second half. if a[i] is greater than a[j], then there are (mid – i)  
 *      inversions, Because left and right subarrays are sorted, so all the remaining elements 
 *      in left-subarray (a[i+1], a[i+2] … a[mid]) will be greater than a[j].
 *   3. Create a recursive function to divide the array into halves and find the answer by summing 
 *      the number of inversions is the first half, number of inversion in the second half and 
 *      the number of inversions by merging the two.
 *   4. The base case of recursion is when there is only one element in the given half.
 *   5. Print the answer
 * 
 */

#include <iostream>

namespace inversion {

/** Funtion prototype for
 * mergeSort()
 * merge()
 */
int mergeSort(int arr[], int temp[], int left, int right);
int merge(int arr[], int temp[], int left, int mid, int right);

/**
 * Funtion countInversion() returns the number of inversion
 * present in the input array. Inversions are an estimate of
 * how close or far off the array is to being sorted.
 * 
 * Number of inversions in a sorted array is 0.
 * Number of inversion in an array[1...n] sorted in 
 * non-ascending order is n(n-1)/2, since each pair of elements
 * contitute an inversion.
 * 
 * @param arr   - array, input for counting inversions in
 * @param array_size    - number of elementa in the array
 * 
 */
int countInversion(int arr[], int array_size)
{
    int temp[array_size];
    return mergeSort(arr, temp, 0, array_size);
}

/**
 * 
 * The mergeSort() function implements Merge Sort, a
 * Divide and conquer algorithm, it divides the input
 * array into two halves and calls itself for each 
 * sub-array and then calls the merge() function to 
 * merge the two halves.
 * 
 * @param arr   - array to be sorted
 * @param temp  - merged resultant array
 * @param left  - lower bound of array
 * @param right - upper bound of array
 * 
 */
int mergeSort(int arr[], int temp[], int left, int right)
{
    int mid, inv_count = 0;
    if(right>left)
    {
        // midpoint to split the array
        mid = (right + left) / 2;
        // Add inversions in left and right sub-arrays
        inv_count += mergeSort(arr, temp, left, mid);   // left sub-array
        inv_count += mergeSort(arr, temp, mid+1, right);

        // inversions in the merge step
        inv_count += merge(arr, temp, left, mid, right);
    }
    return inv_count;
}

/**
 * Function to merge two sub-arrays. merge() function is called 
 * from mergeSort() to merge the array after it split for sorting 
 * by the mergeSort() funtion.
 * 
 * In this case the merge fuction will also count and return 
 * inversions detected when merging the sub arrays.
 * 
 * @param arr    input array
 * @param temp   stores the resultant merged array
 * @param left   lower bound of arr[] and left-sub-array
 * @param mid    midpoint, upper bound of left sub-array,
 *               (mid+1) gives the lower bound of right-sub-array
 * @param right  upper bound of arr[] and right-sub-array
 * 
 */
int merge(int arr[], int temp[], int left, int mid, int right)
{
    int i = left;   /* i --> index of left sub-array */
    int j = mid+1;  /* j --> index for right sub-array */
    int k = left;   /* k --> index for resultant array temp */
    int inv_count = 0;  // inversion count

    while((i <= mid) && (j <= right))
    {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else{
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1); // tricky; may vary depending on selection of sub-array
        }
    } 
    // Add remaining elements from the larger subarray to the end of temp
    while( i <= mid)
        temp[k++] = arr[i++];
    while( j <= right)
        temp[k++] = arr[j++];
    // Copy temp[] to arr[]
    for( k=left; k<=right; k++)
    {
        arr[k] = temp[k];
    }
    return inv_count;
}
    
} // namespace inversion

using namespace inversion::countInversion;

/**
 * UTILITY function to print array.
 * @param arr[]   array to print
 * @param array_size    size of input array arr[]
 * 
 */
void show(int arr[], int array_size)
{   
    std::cout<< "Printing array: \n";
    for( int i=0; i<array_size; i++){
        std::cout<<" "<< arr[i];
    }
    std::cout << "\n";
}

int main(void)
{
 /**   
    // Enter your own array
    int size;
    std::cout << "Enter number of elements: ";
    std::cin >> size;

    // Declare the array
    int *arr = new int[size];

    std::cout << "Enter elements --> \n";
    for( int i=0; i<size; i++)
    {
        std::cout << "Element "<< (i+1) << ": ";
        std::cin >> arr[i];
    }
*/
    size = 100;
    arr[] = {100, 99, 98, 97, 96, 95, 94, 93, 92, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    std::cout << "\n";
    show(arr, size);

    // Counting inversions
    std::cout << "\nThe number of inversions: "<< countInversion(arr, size) << "\n";

    // Output sorted array
    std::cout << "\nSorted array -->  \n";
    show(arr, size);

    delete[] arr;
    return 0;
}
/** @rakshitraj */
