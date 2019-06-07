#include <cstdio>
#include <iostream>
using namespace std;

double log10(double);
double ln(double);
#define LN10 2.3025850929940456840179914546844

double log10(double x)
{
	return ln(x) / LN10;
}

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
	printf("This program calculates the logarithm base 10.\n");

	printf("Enter a positive value: ");
	while (1 == scanf("%lf", &x) && x > 0.0)
	{
		double a = log10(x);
		printf("log10(%lf) = %.12lf\n", x, a);
		printf("Enter a positive value: ");
	}
	return 0;
}
