/* atan func */
#include <iostream>

using namespace std;
#define PI 3.141592653589793238462643383279502884197169

double atan(double x)
{
	double val;
	if (x < 0) {
		val = -(x - (x*x*x) / 3 + (x*x*x*x*x) / 5 - (x*x*x*x*x*x*x) / 7);
	}
	else if (x > 1) {
		val = PI / 2 - atan(1 / x);
		
	}
	else {
		val = x - (x*x*x) / 3 + (x*x*x*x*x) / 5 - (x*x*x*x*x*x*x) / 7;
	}
	return val;
}

int main(int argc,char**argv)
{
	double param,result;
	param = 0.5;
	result = atan(param);
	cout<< "atan of "<<param<<" is "<<result<<endl;	
	return 0;
}
