//Bubble Sort

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n;
	short swap_check = 1;
	cout << "Enter the amount of numbers to sort: ";
	cin >> n;
	vector<int> numbers;
	cout << "Enter " << n << " numbers: ";
	int num;

	//Input
	for (int i = 0; i < n; i++)
	{
		cin >> num;
		numbers.push_back(num);
	}

	//Bubble Sorting
	for (int i = 0; (i < n) && (swap_check == 1); i++)
	{
		swap_check = 0;
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (numbers[j] > numbers[j + 1])
			{
				swap_check = 1;
				swap(numbers[j], numbers[j + 1]);// by changing swap location. I mean, j. If the number is greater than j + 1, then it means the location.
			}
		}
	}

	//Output
	cout << "\nSorted Array : ";
	for (int i = 0; i < numbers.size(); i++)
	{
		if (i != numbers.size() - 1)
		{
			cout << numbers[i] << ", ";
		}
		else
		{
			cout << numbers[i] << endl;
		}
	}
	return 0;
}

/*The working principle of the Bubble sort algorithm:

Bubble sort algorithm is the bubble sorting algorithm. The most important reason for calling the bubble is that the largest number is thrown at the end of this algorithm.
This is all about the logic.
In each iteration, the largest number is expired and when iterations are completed, the sorting takes place.

What is Swap?

Swap in the software means that two variables are displaced.
An additional variable is required for this operation. x = 5, y = 10.
We want x = 10, y = 5. Here we create the most variable to do it.

int z;
z = x;
x = y;
y = z;

The above process is a typical displacement process.
When x assigns the value to x, the old value of x is lost.
That's why we created a variable z to create the first value of the value of x, and finally, we have assigned to y.

Bubble Sort Algorithm Analysis (Best Case - Worst Case - Average Case)

Bubble Sort Worst Case Performance is O (n²). Why is that? Because if you remember Big O Notation, we were calculating the complexity of the algorithms in the nested loops.
The n * (n - 1) product gives us O (n²) performance. In the worst case all the steps of the cycle will occur.
Bubble Sort (Avarage Case) Performance. Bubble Sort is not an optimal algorithm.
in average, O (n²) performance is taken.
Bubble Sort Best Case Performance. O (n).
However, you can't get the best status in the code we shared above. This happens on the optimized bubble sort algorithm. It's right down there.
* /
