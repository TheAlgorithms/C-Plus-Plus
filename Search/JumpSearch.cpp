// C++ program to search using jump search algo
//Contributed by Arpit Godghate
//Github: @arpitg24

#include<iostream> 
#include<cmath>
using namespace std; 

int jumpSearch(int arr[], int x, int n) 
{ 
	
	int step = sqrt(n); 

	int prev = 0; 
	while (arr[min(step, n)-1] < x) 
	{ 
		prev = step; 
		step += sqrt(n); 
		if (prev >= n) 
			return -1; 
	} 

	while (arr[prev] < x) 
	{ 
		prev++; 

		 
		if (prev == min(step, n)) 
			return -1; 
	} 
	if (arr[prev] == x) 
		return prev; 

	return -1; 
} 

int main() 
{  //Enter the number of elements to be entered in the array
   int k;
   cin>>k;
	int arr[k];
   for(int i=0;i<k;++i){
     cin>>arr[i];
   }
   // Enter the number to be found
	int x;
   cin>>x;
	int n = sizeof(arr) / sizeof(arr[0]); 

	int index = jumpSearch(arr, x, n); 

	cout << "\nNumber " << x << " is at position " << index+1; 
	return 0; 
} 



