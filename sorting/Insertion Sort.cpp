//Insertion Sort

#include <iostream>
using namespace std;

int main()
{
	int n;
	cout << "\nEnter the length of your array : ";
	cin >> n;
	int Array[n];
	cout << "\nEnter any " << n << " Numbers for Unsorted Array : ";

	//Input
	for (int i = 0; i < n; i++)
	{
		cin >> Array[i];
	}

	//Sorting
	for (int i = 1; i < n; i++)
	{
		int temp = Array[i];
		int j = i - 1;
		while (j >= 0 && temp < Array[j])
		{
			Array[j + 1] = Array[j];
			j--;
		}
		Array[j + 1] = temp;
	}

	//Output
	cout << "\nSorted Array : ";
	for (int i = 0; i < n; i++)
	{
		cout << Array[i] << "\t";
	}
	return 0;
}
