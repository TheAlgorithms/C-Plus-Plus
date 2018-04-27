/* C++ implementation Odd Even Sort */
#include<iostream>
using namespace std;

void switchElmts(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void oddEven(int arr[], int size)
{
	bool sorted = false;
	while(!sorted)
	{
		sorted = true;
		for(int i = 1; i < size-1; i += 2)//Odd
		{
			if(arr[i] > arr[i+1])
			{
				switchElmts(arr,i,i+1);
				sorted = false;
			}
		}

		for(int i = 0; i < size-1; i += 2)//Even
		{
			if(arr[i] > arr[i+1])
			{
				switchElmts(arr,i,i+1);
				sorted = false;
			}
		}
	}
}

void show(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	cout<<A[i]<<"\n";
}


int main()
{
	int size;
	cout<<"\nEnter the number of elements : ";

	cin>>size;

	int arr[size];

	cout<<"\nEnter the unsorted elements : ";

	for (int i = 0; i < size; ++i)
	{
		cout<<"\n";
		cin>>arr[i];
	}

	oddEven(arr, size);

	cout<<"Sorted array\n";
	show(arr, size);
	return 0;
}
