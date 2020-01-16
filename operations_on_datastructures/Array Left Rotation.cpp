#include <iostream>
using namespace std;
int main()
{
	int n, k;
	cout << "Enter size of array=\t";
	cin >> n;
	cout << "Enter Number of indeces u want to rotate the array to left=\t";
	cin >> k;
	int a[n];
	cout << "Enter  elements of array=\t";
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	int temp = 0;
	for (int i = 0; i < k; i++)
	{
		temp = a[0];
		for (int j = 0; j < n; j++)
		{
			if (j == n - 1)
			{
				a[n - 1] = temp;
			}
			else
			{
				a[j] = a[j + 1];
			}
		}
	}
	cout << "Your rotated array is=\t";
	for (int j = 0; j < n; j++)
	{
		cout << a[j] << " ";
	}
	getchar();
	return 0;
}
