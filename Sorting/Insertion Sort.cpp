//Insertion Sort

#include<iostream>
using namespace std;

int main()
{
	/*int n;
      int Array[n];*/
	int n;
	cin>>n;
	int Array[n];
	cout<<"\nEnter any 6 Numbers for Unsorted Array : \n";

	//Input
	for(int i=0; i<n; i++)
	{
		cin>>Array[i];
	}

	//Sorting
	for(int i=1; i<n; i++)
	{
		int temp=Array[i];
		int j=i-1;
		/*while(j>=0 && temp<Array[j])   VERY SILLY MISTAKE!
		                                This will give the correct answer but it is conceptually wrong.  
		{                               As in Insertion sort, first we find the correct place for the encountered element and then place that element at that position 
		                                by shifting the bigger elements one step forward. In that code we are doing "Comparison + Swapping" but in Insertion sort,
		                                the algorithm says "Comparison +Shifting" .  
					Array[j+1]=Array[j];
			j--;
		}
		Array[j+1]=temp;
		*/
		while(j>=0&&temp<Array[j]) //correct approach:)
		{
			j--;
		}
		int k;
		for( k=i;k>j+1;k--)
		{
			Array[k]=Array[k-1];
		}
		Array[k]=temp;

	}

	//Output
	cout<<"\nSorted Array : ";
	for(int i=0; i<n; i++)
	{
		cout<<Array[i]<<"\t";
	}
}

