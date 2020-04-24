#include <iostream>
using namespace std;
int fib(int n)
{
	int res[3];
	res[0] = 0;
	res[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		res[2] = res[1] + res[0];
		res[0] = res[1];
		res[1] = res[2];
	}
	return res[1];
}
int main(int argc, char const *argv[])
{
	int n;
	cout << "Enter n: ";
	cin >> n;
	cout << "Fibonacci number is ";
	cout << fib(n) << endl;
	return 0;
}
