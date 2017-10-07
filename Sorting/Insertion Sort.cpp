//Insertion Sort

#include<iostream>
using namespace std;

int main()
{
	int n;
    cin >> n;
	int *arrayPtr = new int[n];
	
	//Input
	for(int i=0; i<n; i++)
	{
		cin>>arrayPtr[i];
	}
	
	//Sorting
	for(int i=1; i<n; i++)
	{
		int temp=arrayPtr[i];
		int j=i-1;
		while(j>=0 && temp<arrayPtr[j])
		{
			arrayPtr[j+1]=arrayPtr[j];
			j--;
		}
		arrayPtr[j+1]=temp;
	}
	
	//Output
	cout<<"\nSorted Array : ";
	for(int i=0; i<n; i++)
	{
		cout<<arrayPtr[i]<<"\t";
	}
}

