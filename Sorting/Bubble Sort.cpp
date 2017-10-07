//Bubble Sort

#include<iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
    
    int *arrayPtr = new int[n];
    
	cout << "\nEnter any " << n << " Numbers for Unsorted Array: \n";

	//Input
	for(int i=0; i<n; i++)
	{
		cin >> arrayPtr[i];
	}

	//Bubble Sorting
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n-1; j++)
		{
			if (arrayPtr[j] > arrayPtr[j+1])
			{
				int temp = arrayPtr[j];
				arrayPtr[j] = arrayPtr[j + 1];
				arrayPtr[j + 1] = temp;
			}
		}
	}

	//Output
	cout<<"\nSorted Array : ";
	for(int i=0; i<n; i++)
	{
		cout << arrayPtr[i] << " ";
	}
}
