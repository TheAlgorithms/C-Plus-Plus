//Selection Sort

#include <iostream>
#include<vector>
using namespace std;

int main()
{
	int n;
	cout<<"Enter Number Of Elements "<<endl;
	cin>>n;
	vector<int> Array;
	cout << "Enter any"<<n<< "Numbers for Unsorted Array : ";
    int inp;
	//Input
	for (int i = 0; i < n; i++)
	{
		cin>>inp;
		Array.push_back(inp);
	}

	//Selection Sorting
	for (int i = 0; i < n; i++)
	{
		int min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (Array[j] < Array[min])
			{
				min = j; //Finding the smallest number in Array
			}
		}
		int temp = Array[i];
		Array[i] = Array[min];
		Array[min] = temp;
	}

	//Output
	cout << "\nSorted Array : ";
	for (int i = 0; i < n; i++)
	{
		cout << Array[i] << "\t";
	}
}
