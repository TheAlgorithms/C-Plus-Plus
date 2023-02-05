/**
 * @function DigitSum
 * @description Calculate the sum of all digits of a natural number (number base 10).
 * @param {number} num - A natural number.
 * @return {number} - Sum of all digits of given natural number.
 * @see https://en.wikipedia.org/wiki/Digit_sum
 * @example DigitSum(12) = 3
 * @example DigitSum(9045) = 18
 */

#include <iostream>
#include <cmath>

int DigitSum(int num)
{
	if (num < 0)
	{
		std::cerr << "only natural numbers are supported" << std::endl;
		return -1;
	}
	
	int sum = 0;
	while (num != 0)
	{
		sum += num % 10;
		num = floor(num / 10);
	}
	
	return sum;
}

int main()
{
	std::cout << DigitSum(324) << std::endl;
}
