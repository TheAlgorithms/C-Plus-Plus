// An implementation of Gnome Sort.
#include <iostream>
using namespace std;

void GnomeSort(int ary[], int size)
{	
	// Starting position is second element.
	int position = 1, placeholder;	

	while (position != size) {
	
		// If the current element is smaller than the one before it,
		// swap the two and decrement the position.
		if (ary[position] < ary[position - 1])    
		{
			placeholder = ary[position];
			ary[position] = ary[position - 1];
			ary[position - 1] = placeholder;

			position--;
		}

		// Otherwise, increment the current position.
		else
			position++;
	}
}

// Driver for testing
int main()
{
	int ary[] = { 12, 37, -3, -2, 0, 9, 7 }, size = 7;

	cout << "Original array: ";

	for (int num : ary) {

		cout << num << " ";
	}
	cout << endl;

	GnomeSort(ary, size);

	cout << "Sorted array: ";

	for (int num : ary) {

		cout << num << " ";
	}
	cout << endl;

    return 0;
}

