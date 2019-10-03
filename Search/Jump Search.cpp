#include <iostream>
#include <math.h>
using namespace std; 
  
int jumpSearch(int arr[], int x, int n) 
{ 
    // Finding block size to be jumped 
    int step = sqrt(n); 
  
    // Finding the block where element is 
    // present (if it is present) 
    int prev = 0; 
    while (arr[min(step, n) - 1] < x) 
    { 
        prev = step; 
        step += sqrt(n); 
        if (prev >= n) 
            return -1; 
    } 
  
    // Doing a linear search for x in block 
    // beginning with prev. 
    while (arr[prev] < x) 
    { 
        prev++; 
  
        // If we reached next block or end of 
        // array, element is not present. 
        if (prev == min(step, n)) 
            return -1; 
    } 
    // If element is found 
    if (arr[prev] == x) 
        return prev; 
  
    return -1; 
}

int min(int a, int b){
    int m;
    (a <= b)? m = a : m = b;
    return m;
} 
  
int main(void) 
{ 
    
    int key;
    int size = 9;
    int array[] = {0, 3, 6, 8, 10, 13, 21, 52, 67, 81};

	cout << "\nEnter the number to be searched : ";
	cin >> key; 
 
    int result = jumpSearch(array, key, size); 
    (result == -1)? printf("Element is not present in array") : printf("Element is present at index %d", result); 
    return 0; 
} 