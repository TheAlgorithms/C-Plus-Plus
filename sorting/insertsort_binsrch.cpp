/*
    The original insertion sort algorithm works on the principle of finding the most suitable place for the elements one by one. It pushes those values to one place right which are greater than the value of the element that we are concerned about.
    This is actually an operation of searching and it can be improved by applying binary search thereby optimizing the program.
    Some major advantages are:
    1. The relative order of items with equal keys does not change.
    2. The ability to sort a list as it is being received.
    3. Better than other sorting algorithms which have quadratic complexities as insertion sort is O(n) and by using binary search we can bring it down to O(logn).
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/* 
    Recursive binary search to find the best place to put the value that we are converned about.

        @param arr - sub-array given from the insert_sort_bin_search function in which we will find
                    the suitable position for our value
        @val - the value for which we are searching the place
        @low - the lowest index value of array to search from
        @high - the highest index value of array to search from
*/
int binary_search(int arr[],int val,int low,int high)
{
    /* When the search is over ie. we are at the place where the element best suits, we return the position. */
    if (high <= low)
        return (val > arr[low]) ? (low + 1) : low;
    
    int mid = low + (high-low)/2;
    if(arr[mid]>val)
        return binary_search(arr,val,low,mid-1);
    else if(arr[mid]<val)
        return binary_search(arr,val,mid+1,high);
    else
        return mid+1;
}

/* 
    Insertion sort using binary search. It uses the original insertion sort with searching operation assigned to the binary search function.

        @param arr - the original array to sort
        @param size - size of the array
*/
void insert_sort_bin_search(int arr[],int size)
{
    int i,j,key;
    for(i=1;i<size;i++)
    {
        key = arr[i];
        j = i-1;
        // find location where selected should be inseretd.
        int loc = binary_search(arr,key,0,j);
        // Move all elements after loc to create space.
        while(j>=loc)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

// Function to print the array
void printarray(int arr[],int n)
{
    cout<<"Sorted Array:\n";
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
}

// Driver program
int main()
{
    int n;
    cout<<"Enter size: ";
    cin>>n;
    int arr[n];
    cout<<"Enter the elements: ";
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    insert_sort_bin_search(arr,n);
    
    printarray(arr,n);

    return 0;
}