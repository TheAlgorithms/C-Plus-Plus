//ln.cpp
#include <iostream>
using namespace std;

double ln(double);

double ln(double x)
{
	double old_sum = 0.0;
	double xmlxpl = (x - 1) / (x + 1);
	double xmlxpl_2 = xmlxpl * xmlxpl;
	double denom = 1.0;
	double frac = xmlxpl;
	double term = frac;
	double sum = term;

	while (sum != old_sum)
	{
		old_sum = sum;
		denom += 2.0;
		frac *= xmlxpl_2;
		sum += frac / denom;
	}
	return 2.0 * sum;
}

int main()
{
	double x, a;
	cout << "This program calculates the logarithm base e." << endl;

	cout << "Enter a positive value: ";
	cin >> x;

	a = ln(x);
	cout << "log10(" << x << ") = " << a;


	return 0;
}
