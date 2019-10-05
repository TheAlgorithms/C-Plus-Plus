/*
 * Trial Division is an slow algorithm to determine if a number is prime.
 * If the number n to test is dividable by 2, it is not a prime number.
 * Otherwise, it is an odd number, so further trial division can be made
 * starting with 3 and testing every following odd number. If the number
 * to test is not dividable by any number smaller than its square it is
 * a prime number.
 */

#include <iostream>

bool trialDivisionTest(int n)
{
	if (n % 2 == 0)
	{
		return false;
	}

	int divisor = 3;
	while (divisor <= std::sqrt(n))
	{
		if (n % divisor == 0)
		{
			return false;
		}
		divisor += 2;
	}

	return true;
}

int main()
{
	int n;
	std::cout << "Enter a number to test: ";
	std::cin >> n;
	if (trialDivisionTest(n))
	{
		std::cout << n << " is a prime number" << std::endl;
	}
	else
	{
		std::cout << n << " is not a prime number" << std::endl;
	}
}
