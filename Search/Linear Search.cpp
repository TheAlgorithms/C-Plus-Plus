#include <iostream>
using namespace std;

int LinearSearch(int *array, int size, int key)
{
	for (int i = 0; i < size; ++i)
	{
		if (array[i] == key)
		{
			return i;
		}
	}

	return -1;
}

// beginning of main 
int main()
{
	int size;      //declaration of variable size
	cout << "\nEnter the size of the Array : ";
	cin >> size;

	int array[size];     // declaring an array of size 'size'
	int key;

	//Input array
	cout << "\nEnter the Array of " << size << " numbers : ";
	for (int i = 0; i < size; i++)
	{
		cin >> array[i];
	}

	cout << "\nEnter the number to be searched : ";
	cin >> key;

	int index = LinearSearch(array, size, key);
	if (index != -1)
	{
		cout << "\nNumber found at index : " << index;
	}
	else
	{
		cout << "\nNot found";
	}

	return 0;
} // closing of main
