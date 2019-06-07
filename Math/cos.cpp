/* cos func */
#include <iostream>
using namespace std;

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

double cos(double x)
{
	double val;
	
	val = 1 - (x*x) * 1 / 2 + (x*x*x*x) * 1 / 24 - (x*x*x*x*x*x) * 1 / 720;
	

	return val;
}

int main() {
	double param,result;
	param = 0.5;
	result = cos(param);
	cout<< "cos of "<<param<<" is "<<result<<endl;
	return 0;
}
