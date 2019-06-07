/* atan2 func */

#include <iostream>

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
using namespace std;

double atan2(double x,double y)
{
	x = x / y;
	double val;
	if (x < 0) {
		val = -(x - (x*x*x) / 3 + (x*x*x*x*x) / 5 - (x*x*x*x*x*x*x) / 7);
	}
	else {
		val = x - (x*x*x) / 3 + (x*x*x*x*x) / 5 - (x*x*x*x*x*x*x) / 7;
	}
	return val;
}


int main(int argc, char** argv){
	double a, b,result;
	a = 5.0; b = 10.0;
	result = atan2 (a,b);
	cout<<"The arc tangent for a="<<a<<" b="<<b<<" is "<<result<<" degrees.\n"<<endl;
	return 0;	
}
