#include <iostream>
using namespace std;
int arr[1000000];
int fib(int n)
{
	if (arr[n] == -1)
	{
		if (n <= 1)
			arr[n] = n;
		else
			arr[n] = fib(n - 1) + fib(n - 2);
	}
	return arr[n];
}
int main(int argc, char const *argv[])
{
	int n;
	cout << "Enter n: ";
	cin >> n;
	for (int i = 0; i < n + 1; ++i)
	{
		arr[i] = -1;
	}
	cout << "Fibonacci number is " << fib(n) << endl;
	return 0;
}