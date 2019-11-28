#include<iostream>

using namespace std;

void show_pascal(int **arr, int n)
{
	//pint Pascal's Triangle
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n + i; ++j)
		{
			if (arr[i][j] == 0)
				cout << " ";
			else
				cout << arr[i][j];
		}
		cout << endl;
	}
}

int **pascal_triangle(int **arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = n - i - 1; j < n + i; ++j)
		{
			if (j == n - i - 1 || j == n + i - 1)
				arr[i][j] = 1;				//The edge of the Pascal triangle goes in 1
			else
				arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j + 1];
		}
	}

	return arr;
}

int main()
{
	int n = 0;

	cout << "Set Pascal's Triangle Height" << endl;
	cin >> n;
	
	//memory allocation (Assign two-dimensional array to store Pascal triangle)
	int **arr = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		arr[i] = new int[2 * n - 1];
		memset(arr[i], 0, sizeof(int)*(2 * n - 1));
	}
	
	pascal_triangle(arr, n);
	show_pascal(arr, n);

	//deallocation
	for (int i = 0; i < n; ++i)
	{
		delete[] arr[i];
	}
	delete[] arr;

	return 0;
}
