#include<iostream>
using namespace std;

int LinearSearch(int *array, int key)
{
	for (int i = 0; i < 10; ++i)
	{
		if (array[i]==key)
		{
			return key;
		}
	}

	return -1;
}


int main()
{
	int array[10];
	int key;

	//Input array
	cout<<"\nEnter the Array of 10 numbers : ";
	for (int i = 0; i < 10; i++)
	{
		cin>>array[i];
	}
	cout<<"\nEnter the number to be searched : ";
	cin>>key;

	int index=LinearSearch(array, key);
	if (index!=-1)
	{
		cout<<"\nNumber found at index : "<<index;
	}
	else
	{
		cout<<"\nNot found";
	}
	
	return 0;
}
