

#include <iostream> 
using namespace std; 

int search(int arr[], int n, int x) 
{ 
	int i; 
	for (i = 0; i < n; i++) 
		if (arr[i] == x) 
			return i; 
	return -1; 
} 

int main(void) 
{ 
	int n;
	cin >> n;
	
	int x;
	cin >> x;
	
	int arr[n];
	for(int i=0; i<n; i++)
		cin >> arr[i];
	
	int result = search(arr, n, x); 

	(result == -1)? cout<<"Element is not present in array"
				: cout<<"Element is present at index " <<result; 
return 0; 
} 
