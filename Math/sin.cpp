#include <iostream>
using namespace std;
const double PI = 3.1415926535897932384650288;

double sin(double x) {
	double sign = 1;
	if (x < 0) {
		sign = -1.0;
		x = -x;
	}
	if (x > 360) x -= int(x / 360) * 360;
	x *= PI / 180.0;
	double res = 0;
	double term = x;
	int k = 1;
	while (res + term != res) {
		res += term;
		k += 2;
		term *= -x * x / k / (k - 1);
	}

	return sign * res;
}

int main()
{
	double input;
	cin >> input;
	cout << sin(input) << endl;

	return 0;
}
