#include <iostream>
using namespace std; 
  
int binarySearch(int arr[], int, int, int); 
  
int exponentialSearch(int arr[], int n, int x){ 
    
    if (arr[0] == x)                                    //If x is found at the beginning return
        return 0; 
  
    int i = 1; 
    while (i < n && arr[i] <= x) 
        i = i * 2; 
    
    return binarySearch(arr, i/2, min(i, n), x);        //Calling binary for the subarray
} 


int binarySearch(int arr[], int l, int r, int x){        //Recursive Binary Search{
    if (r >= l) 
    { 
        int mid = l + (r - l)/2; 

        if (arr[mid] == x) 
            return mid; 
  

        if (arr[mid] > x) 
            return binarySearch(arr, l, mid-1, x); 
  

        return binarySearch(arr, mid+1, r, x); 
    } 
  
    return -1; 
} 

int min(int a, int b){
    int m;
    (a <= b)? m = a : m = b;
    return m;
}
  
int main(void) 
{ 
    int size;
    int key;

    cout << "Enter array size: \n";
    cin >> size;

    int array[size];
	
	cout << "\nEnter the Array of " << size << " numbers : ";
	for (int i = 0; i < size; i++)
	{
		cin >> array[i];
	}

	cout << "\nEnter the number to be searched : ";
	cin >> key; 
 
    int result = exponentialSearch(array, size, key); 
    (result == -1)? printf("Element is not present in array") : printf("Element is present at index %d", result); 
    return 0; 
} 