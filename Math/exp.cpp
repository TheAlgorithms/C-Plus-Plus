#include <iostream>
using namespace std;
const double E = 2.71828;

double exp(int y)
{
	double temp;

	if (y == 0)
		return 1;

	temp = exp( y / 2);

	if (y % 2 == 0)
		return temp * temp;
	else
	{
		if (y > 0)
			return E * temp*temp;
		else
			return (temp*temp) / E;
	}
}


int main()
{
	double a;

	cout << "This is the exponential funcion e^x.\nEnter the value of x: ";
	cin >> a ;
	cout << exp(a);

	return 0;
}
