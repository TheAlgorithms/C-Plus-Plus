#include <iostream>
using namespace std;

// Maximum number of digits in output
// x^n where 1 <= x, n <= 10000 and overflow may happen
#define MAX 100000

// This function multiplies x
// with the number represented by res[].
// res_size is size of res[] or
// number of digits in the number
// represented by res[]. This function
// uses simple school mathematics
// for multiplication.
// This function may value of res_size
// and returns the new value of res_size
int multiply(int x, int res[], int res_size)
{

	// Initialize carry
	int carry = 0;

	// One by one multiply n with
	// individual digits of res[]
	for (int i = 0; i < res_size; i++)
	{
		int prod = res[i] * x + carry;

		// Store last digit of
		// 'prod' in res[]
		res[i] = prod % 10;

		// Put rest in carry
		carry = prod / 10;
	}

	// Put carry in res and
	// increase result size
	while (carry)
	{
		res[res_size] = carry % 10;
		carry = carry / 10;
		res_size++;
	}
	return res_size;
}

// This function finds
// power of a number x
void power(int x, int n)
{

	//printing value "1" for power = 0
	if (n == 0)
	{
		cout << "1";
		return;
	}

	int res[MAX];
	int res_size = 0;
	int temp = x;

	// Initialize result
	while (temp != 0)
	{
		res[res_size++] = temp % 10;
		temp = temp / 10;
	}

	// Multiply x n times
	// (x^n = x*x*x....n times)
	for (int i = 2; i <= n; i++)
		res_size = multiply(x, res, res_size);

	cout << x << "^" << n << " = ";
	for (int i = res_size - 1; i >= 0; i--)
		cout << res[i];
}

// Driver program
int main()
{
	int exponent, base;
	printf("Enter base ");
	scanf("%id \n", &base);
	printf("Enter exponent ");
	scanf("%id", &exponent);
	power(base, exponent);
	return 0;
}
