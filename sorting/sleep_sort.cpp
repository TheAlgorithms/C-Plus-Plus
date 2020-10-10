#include <stdio.h> 
#include <windows.h> 
#include <process.h> 
void routine(void *a) 
{ 
	int n = *(int *) a; // typecasting from void to int 
	Sleep(n); 
	printf("%d ", n); 
} 
void sleepSort(int arr[], int n) 
{ 
	HANDLE threads[n]; 
	// Create the threads for each of the input array elements 
  
	for (int i = 0; i < n; i++) 
		threads[i] = (HANDLE)_beginthread(&routine, 0, &arr[i]); 
	WaitForMultipleObjects(n, threads, TRUE, INFINITE); 
	return; 
} 

// Driver program
int main() 
{ 
	// It does not work for negative numbers 
	int arr[] = {34, 23, 122, 9}; 
	int n = sizeof(arr) / sizeof(arr[0]); 
	sleepSort (arr, n); 
	return(0); 
} 
