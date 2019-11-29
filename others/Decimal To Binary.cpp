// This function convert decimal to binary number
//
#include <iostream>
using namespace std;

int main()
{
	int number;
	cout << "Enter a number:";
	cin >> number;
	int remainder, binary = 0, var = 1;

	do
	{
		remainder = number % 2;
		number = number / 2;
		binary = binary + (remainder * var);
		var = var * 10;

	} while (number > 0);
	cout << "the binary is :";
	cout << binary;
	cout << endl;
	return 0;
}
