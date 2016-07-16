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
	
	//Bubble Sorting
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<5; j++)
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
	for(int i=0; i<6; i++)
	{
		cout<<Array[i]<<"\t";
	}
}
