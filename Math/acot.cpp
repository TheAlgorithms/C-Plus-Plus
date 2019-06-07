/* acot func */

#include <iostream>

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
using namespace std;

double acot(double x)
{
	double val;

	val = PI*1/2 - x+ (x*x*x) * 1 /3 - (x*x*x*x*x) * 1 /5 +(x*x*x*x*x*x*x) * 1 / 7 - (x*x*x*x*x*x*x*x*x) *1/9;


	return val;
}


int main(int argc, char** argv){
	double a, b,result;
	a = 1.0; 
	result = acot (1);
	cout<<"The arc cos for a="<<a<<" is "<<result<<" degrees.\n"<<endl;
	return 0;	
}
