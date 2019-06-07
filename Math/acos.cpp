/* acos func*/
#include <iostream>

using namespace std;
#define PI 3.141592653589793238462643383279502884197169

double acos(double x)
{
	double val;
	if (-1<=x &&x<1) {
		val = PI*1/2 - x -(x*x*x)*1/3 -(x*x*x*x*x)* 3/40 - (x*x*x*x*x*x*x)*5/112;
	}
	else if (x == 1) {
		val = 0;
	}
	else {
		cout<<"value is out of range!!!<<endl;
		val = 0;
	}
	return val;
}
int main(int argc,char**argv)
{
	double param,result;
	param = 0.5;
	result = acos(param);
	cout<< "acos of "<<param<<" is "<<result<<endl;
	return 0;
}
