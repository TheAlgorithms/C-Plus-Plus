#include <iostream>
using namespace std;
double ceil(double input)
{
	if (input == (int)input)
	{
		return input;
	}
	else
	{
		return (int)input + 1;
	}
}
int main()
{
	double input;
	cin >> input;
	cout << ceil(input) << endl;


	return 0;
}
