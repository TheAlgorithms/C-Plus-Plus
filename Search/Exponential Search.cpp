#include <iostream> 
using namespace std; 

int binarySearch(int a[], int, int, int); 

int exponentialSearch(int a[], int n, int key) 
{ 
	if (a[0] == key) 
		return 0; 

	int i = 1; 
	while (i < n && a[i] <= key) 
		i = i*2; 

	return binarySearch(a, i/2, min(i, n), key); 
} 

int binarySearch(int a[], int l, int r, int key) 
{ 
	if (r >= l) 
	{ 
		int mid = l + (r - l)/2; 

		if (a[mid] == key) 
			return mid; 

		if (a[mid] > key) 
			return binarySearch(a, l, mid-1, key); 

		return binarySearch(a, mid+1, r, key); 
	} 

	return -1; 
} 


int main(void) 
{ 

int n, key;
cout << "Enter size of array: ";
cin >> n;
cout << "Enter array elements: ";
int a[n];
for (int i = 0; i < n; ++i)
{
	cin >> a[i];
}
cout << "Enter search key: ";
cin >> key;
int result = exponentialSearch(a, n, key); 
(result == -1)? printf("Element is not present in array\n") 
				: printf("Element is present at index %d\n", 
													result); 
return 0; 
} 
