/* asin func */

#include <iostream>
#include <cmath>

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
using namespace std;

double asin(double x)
{
	double val;

	val = x* 1 - (x*x*x) * 1 / 6 + (x*x*x*x*x) * 3 / 40 - (x*x*x*x*x*x*x) * 5 / 112 + (x*x*x*x*x*x*x*x*x) * 35 / 1152;


	return val;
}

int main(int argc, char** argv){
	double param,result;
	param = 0.5;
	result = cos(param);
	cout<< "asin of "<<param<<" is "<<result<<endl;
	return 0;	
}
