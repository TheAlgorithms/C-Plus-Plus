#include <iostream>
using namespace std;
const double E = 2.71828;

double cosh(int y)
{
	double temp, e1, e2;

	if (y == 0)
		return 1;

	temp = cosh( y / 2);

	if (y % 2 == 0)
	{
		e1 = temp * temp;
		e2 = 1 / temp * temp;
		return e1 + e2 / 2;
	}
	else
	{
		if (y > 0)
		{
			e1 = E*temp * temp;
			e2 = 1 / E*temp * temp;
			return e1 + e2 / 2;
		}
		else
		{
			e1 = (temp*temp) / E;
				e2 = 1/((temp*temp) / E);
			return e1 + e2 / 2;
		}
	}
}


int main()
{
	double a, result;

	cout << "This is the cosh(x).\nEnter the value of x: ";
	cin >> a ;

	cout << cosh(a);

	return 0;
}
