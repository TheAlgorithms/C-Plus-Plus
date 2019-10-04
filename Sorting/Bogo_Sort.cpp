// Bogo Sort
// How not to do sorting

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

bool isSorted(const std::vector<int>& numbers)
{
	for (int i = 1; i < numbers.size(); i++)
	{
		if (numbers.at(i) < numbers.at(i - 1))
		{
			return false;
		}
	}
	return true;
}

void bogoSort(std::vector<int>& numbers)
{
	srand(time(NULL));

	while (!isSorted(numbers))
	{
		int a = rand() % numbers.size();
		int b = rand() % numbers.size();
		std::iter_swap(numbers.begin() + a, numbers.begin() + b);
	}
}

int main()
{
	int n;
	std::cout << "Enter the amount of numbers to sort: ";
	std::cin >> n;
	std::vector<int> numbers;
	std::cout << "Enter " << n << " numbers: ";
	int num;

	//Input
	for (int i = 0; i < n; i++)
	{
		std::cin >> num;
		numbers.push_back(num);
	}

	bogoSort(numbers);

	//Output
	std::cout << "\nSorted Array : ";
	for (int i = 0; i < numbers.size(); i++)
	{
		if (i != numbers.size() - 1)
		{
			std::cout << numbers[i] << ", ";
		}
		else
		{
			std::cout << numbers[i] << std::endl;
		}
	}
	return 0;
}
