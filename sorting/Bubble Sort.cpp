#include <bits/stdc++.h> 
using namespace std; 

void swap(int *xp, int *yp) 
{ 
	int temp = *xp; 
	*xp = *yp; 
	*yp = temp; 
} 

// A function to implement bubble sort 
void bubbleSort(int arr[], int n) 
{ 
	int i, j; 
	for (i = 0; i < n-1; i++)	 
	
	// Last i elements are already in place 
	for (j = 0; j < n-i-1; j++) 
		if (arr[j] > arr[j+1]) 
			swap(&arr[j], &arr[j+1]); 
} 

/* Function to print an array */
void printArray(int arr[], int n) 
{ 
	int i; 
	for (i = 0; i < n; i++) 
		cout << arr[i] << " "<<"\n"; 
	
} 

// Driver code 
int main() 
{ 
	int n;
	cin >> n;
	int arr[n];
	
	//looping for input of array
	
	for(int i =0; i< n; i++)
		cin >> arr[i];
	
	bubbleSort(arr, n); 
	cout<<"Sorted array: \n"; 
	printArray(arr, n); 
	return 0; 
} 



/*The working principle of the Bubble sort algorithm:

Bubble sort algorithm is the bubble sorting algorithm. The most important reason for calling the bubble is that the largest number is thrown at the end of this algorithm.
This is all about the logic.
In each iteration, the largest number is expired and when iterations are completed, the sorting takes place.

What is Swap?

Swap in the software means that two variables are displaced.
An additional variable is required for this operation. x = 5, y = 10.
We want x = 10, y = 5. Here we create the most variable to do it.

int z;
z = x;
x = y;
y = z;

The above process is a typical displacement process.
When x assigns the value to x, the old value of x is lost.
That's why we created a variable z to create the first value of the value of x, and finally, we have assigned to y.

Bubble Sort Algorithm Analysis (Best Case - Worst Case - Average Case)

Bubble Sort Worst Case Performance is O (n²). Why is that? Because if you remember Big O Notation, we were calculating the complexity of the algorithms in the nested loops.
The n * (n - 1) product gives us O (n²) performance. In the worst case all the steps of the cycle will occur.
Bubble Sort (Avarage Case) Performance. Bubble Sort is not an optimal algorithm.
in average, O (n²) performance is taken.
Bubble Sort Best Case Performance. O (n).
However, you can't get the best status in the code we shared above. This happens on the optimized bubble sort algorithm. It's right down there.
* /
