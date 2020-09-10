/**
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
 * 
 */

#include <iostream>

using namespace std;

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

/**
 * UTILITY function to print array.
 * @param arr[]   array to print
 * @param array_size    size of input array arr[]
 * 
 */
void show(int arr[], int array_size)
{   
    cout<< "Printing array: \n";
    for( int i=0; i<array_size; i++){
        cout<<" "<< arr[i];
    }
    cout << endl;
}

int main( void )
{
    int size;
    cout << "Enter number of elements: ";
    cin >> size;

    // Declare the array
    int *arr = new int[size];

    cout << "Enter elements --> "<< endl;
    for( int i=0; i<size; i++)
    {
        cout << "Element "<< (i+1) << ": ";
        cin >> arr[i];
    }

    cout << endl;
    show(arr, size);

    // Counting inversions
    cout << endl << "The number of inversions: "<< countInversion(arr, size) << endl;

    // Output sorted array
    cout << endl << "Sorted array -->  "<< endl;
    show(arr, size);

    delete[] arr; 
    return 0;
}
/** @rakshitraj */
