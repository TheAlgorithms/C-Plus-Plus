//Bubble Sort

#include<iostream>
using namespace std;

int main()
{
	int Array[6];
	cout<<"\nEnter any 6 Numbers for Unsorted Array : ";
	
	//Input
	for(int i=0; i<6; i++)
	{
		cin>>Array[i];
	}
	
	//Sorting
	for(int i=1; i<6; i++)
	{
		int temp=Array[i];
		int j=i-1;
		while(j>=0 && temp<Array[j])
		{
			Array[j+1]=Array[j];
			j--;
		}
		Array[j+1]=temp;
	}
	
	//Output
	cout<<"\nSorted Array : ";
	for(int i=0; i<6; i++)
	{
		cout<<Array[i]<<"\t";
	}
}

