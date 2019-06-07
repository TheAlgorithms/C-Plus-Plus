//tanhx = sinhx/coshx
#include <iostream>
using namespace std;
const double E = 2.71828;

double tanh(int y)
{
	double temp, e1, e2;
	double sinhx, coshx;

	if (y == 0)
		return 1;

	temp = cosh( y / 2);

	if (y % 2 == 0)
	{
		e1 = temp * temp;
		e2 = 1 / temp * temp;
		sinhx = e1 - e2 / 2;
		coshx = e1 + e2 / 2;
		return sinhx/coshx;
	}
	else
	{
		if (y > 0)
		{
			e1 = E*temp * temp;
			e2 = 1 / E*temp * temp;
			sinhx = e1 - e2 / 2;
			coshx = e1 + e2 / 2;
			return sinhx / coshx;
		}
		else
		{
			e1 = (temp*temp) / E;
			e2 = 1/((temp*temp) / E);
			sinhx = e1 - e2 / 2;
			coshx = e1 + e2 / 2;
			return sinhx / coshx;
		}
	}
}


int main()
{
	double a, result;

	cout << "This is the tanh(x).\nEnter the value of x: ";
	cin >> a ;

	cout << tanh(a);

	return 0;
}
