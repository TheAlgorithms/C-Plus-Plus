//Bubble Sort

#include<iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int Array[n];
	cout<<"\nEnter any 6 Numbers for Unsorted Array : ";

	//Input
	for(int i=0; i<n; i++)
	{
		cin>>Array[i];
	}

	//Bubble Sorting
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n-1; j++)
		{
			if(Array[j]>Array[j+1])
			{
				int temp=Array[j];
				Array[j]=Array[j+1];
				Array[j+1]=temp;
			}
		}
	}

	//Output
	cout<<"\nSorted Array : ";
	for(int i=0; i<n; i++)
	{
		cout<<Array[i]<<"\t";
	}
}
