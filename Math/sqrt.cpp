//Used The Babylonian Method Algorithm
#include <iostream>
using namespace std;

double SQRT(double, double);


double SQRT(double input, double x)
{
	for (int i = 0; i < 10; i++) { x = (x + (input / x)) / 2; }    

	return x;
}

void main()
{
	double input, x, result;

	cout << "Enter the count of sqrt: ";
	cin >> x;
	cout << "Enter the Value: ";
	cin >> input;
	result = SQRT(input, x);
	cout << "The result: " << result << endl;

}
