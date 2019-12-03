// Bubble Sort

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	// Input size
	size_t n;
	cout << "Enter the amount of numbers to sort: ";
	cin >> n;

	// Input data
	vector<int> numbers(n);
	cout << "Enter " << n << " numbers: ";
	for (size_t i = 0; i < n; ++i)
	{
		cin >> numbers[i];
	}

	// Bubble Sorting
	bool swapped;
	for (size_t i = 0; (i < n) && (swap_check); ++i)
	{
		swapped = false;
		for (size_t j = 0; j < n - 1 - i; ++j)
		{
			if (numbers[j] > numbers[j + 1])
			{
				swap(numbers[j], numbers[j + 1]);
				swapped = true;
			}
		}
	}

	// Output
	cout << "\nSorted Array : ";
	cout << numbers[0];
	for (size_t i = 0; i < n; ++i)
	{
		cout << ", " << numbers[i];
	}
	return 0;
}
