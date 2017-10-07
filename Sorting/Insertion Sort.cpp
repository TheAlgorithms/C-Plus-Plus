//Insertion Sort

#include<iostream>
using namespace std;

int main()
{
	int n;
    
    cout << "Enter an array size: ";
    cin >> n;
    
	int *arrayPtr = new int[n];
	cout << "\nEnter any " << n << " Numbers for Unsorted Array: \n";
	
	//Input
	for (int i = 0; i < n; i++)
	{
        cout << i + 1 << ") ";
		cin >> arrayPtr[i];
	}
	
	//Sorting
	for (int i = 1; i < n; i++)
	{
		int temp = arrayPtr[i];
		int j = i-1;
        
        for (; j >= 0 && temp < arrayPtr[j]; j--)
		{
			arrayPtr[j + 1] = arrayPtr[j];
		}
        
		arrayPtr[j + 1] = temp;
	}
	
	//Output
	cout << "\nSorted Array: ";
    
	for (int i = 0; i < n; i++)
	{
		cout << arrayPtr[i] << " ";
	}
}

