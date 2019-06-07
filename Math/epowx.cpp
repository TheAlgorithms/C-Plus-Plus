/* e pow x func*/
#include <iostream>

using namespace std;
#define PI 3.141592653589793238462643383279502884197169

double epowx(double x)
{
	double val;
	val = 1 + x + (x*x) * 1 / 2 + (x*x*x) * 1 / 6 + (x*x*x*x) * 1 / 24 + (x*x*x*x*x) * 1 / 120 + (x*x*x*x*x*x) * 1 / 720;// +(x^n)*1/n!
	
	return val;
}

int main(int argc,char**argv)
{
	double param,result;
	param = 2;
	result = epowx(param);
	cout<< "e pow of x = "<<param<<" is "<<result<<endl;
	return 0;
}
