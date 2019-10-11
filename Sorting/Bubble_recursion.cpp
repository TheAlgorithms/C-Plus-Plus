#include <bits/stdc++.h> 
using namespace std; 
  
// A function to implement bubble sort using recursion
void bubbleSort(int arr[], int n) 
{ 
 
    if (n == 1) 
        return; 

    for (int i=0; i<n-1; i++) 
        if (arr[i] > arr[i+1]) 
            swap(arr[i], arr[i+1]); 
    bubbleSort(arr, n-1); 
} 
void printArray(int arr[], int n) 
{ 
    for (int i=0; i < n; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 
  

int main() 
{ 
    int n;
	cout<<"Enter the number of elements in the array\n";
	cin>>n;
	int arr[n];
	cout<<"Enter the elements of the array\n";
	for(int i=0;i<n;i++)
	cin>>arr[i];   
    bubbleSort(arr, n); 
    printf("Bubble Sorted array : \n"); 
    printArray(arr, n); 
    return 0; 
} 
