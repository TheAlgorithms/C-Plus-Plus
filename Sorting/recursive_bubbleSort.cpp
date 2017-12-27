#include <bits/stdc++.h>
using namespace std;
 

void bubbleSort(int arr[], int n)   //bubble sort FUNCTION
{
    // Base case
    if (n == 1)
        return;
 
    
    for (int i=0; i<n-1; i++)
        if (arr[i] > arr[i+1])
        swap(arr[i], arr[i+1]);
 
    
    
    bubbleSort(arr, n-1); // recursion for remaining array
}
 
//Function which print an array 
void printArray(int arr[], int n)
{
    for (int i=0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
 
// main function
int main()
{
    int arr[] = {12, 19, 8, 7, 45, 13};
    int n = sizeof(arr)/sizeof(int);
    bubbleSort(arr, n);
    
    printf("Sorted array : \n");
    
    printArray(arr, n);
    return 0;
}
