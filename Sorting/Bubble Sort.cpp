//Bubble Sort

#include<iostream>
using namespace std;

int main()
{
	int n;
	short swap=0;
	cin >> n;
	int Array[n];
	cout<<"\nEnter any "<<n<<" Numbers for Unsorted Array : ";

	//Input
	for(int i=0; i<n; i++)
	{
		cin>>Array[i];
	}

	//Bubble Sorting
	for(int i=0; i<n; i++)
	{
		swap=0;
		for(int j=0; j<n-1-i; j++)
		{
			if(Array[j]>Array[j+1])
			{
				swap=1;
				int temp=Array[j];
				Array[j]=Array[j+1];
				Array[j+1]=temp;
			}
		}
		if(swap == 0)
		{	
			break;
		}
	}

	//Output
	cout<<"\nSorted Array : ";
	for(int i=0; i<n; i++)
	{
		cout<<Array[i]<<"\t";
	}
}
