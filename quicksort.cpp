//pivot as a left position//
#include<iostream>
using namespace std;
int partition(int b[], int lb, int ub)
{
	int pivot = b[lb];
	int start = lb;
	int end = ub;
	while (start < end)
	{
		while (b[start] <= pivot)
		{
			start++;
		}
		while (b[end] > pivot)
		{
			end--;
		}
		if (start < end)
		{
			swap(b[start], b[end]);
		}
	}
	swap(b[lb], b[end]);
	return end;
}
void quicksort(int b[], int lb, int ub)
{
	if (lb < ub)
	{
		int loc = partition(b, lb, ub);
		quicksort(b, lb, loc - 1);
		quicksort(b, loc + 1, ub);
	}
}
void swap(int* x, int* y)
{
	int t = *x;
	*x = *y;
	*y = t;
}
int main()
{
	int b[5];
	cout << "enter 5 numbers:";
	for (int i = 0; i < 5; i++)
	{
		cin >> b[i];
	}
	int n = sizeof(b) / sizeof(b[0]);
	quicksort(b, 0, n - 1);
	cout << "sorted array:";
	for (int j = 0; j < 5; j++)
	{
		cout << b[j] << " ";
	}
	return 0;
}