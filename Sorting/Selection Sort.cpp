//Selection Sort

#include <iostream>
using namespace std;

int main()
{	
	int n;
	cout << "/nEnter the length of array :";
	cin >> n;
	int Array[n];
	cout << "\nEnter Numbers for Unsorted Array : ";

	//Input
	for (int i = 0; i < n; i++)
	{
		cin >> Array[i];
	}

	//Selection Sorting
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (Array[j] < Array[i])
			{
				int temp = Array[j];
				Array[j] = Array[i];
				Array[i] = temp;
			}
		}
	}

	//Output
	cout << "\nSorted Array : ";
	for (int i = 0; i < n; i++)
	{
		cout << Array[i] << "\t";
	}
}
