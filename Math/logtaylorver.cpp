/* log taylor series func */
#include <iostream>

using namespace std;
#define PI 3.141592653589793238462643383279502884197169
double log(double x);
double pow(double x,double y);
double log(double x)
{
	double val;
	double s = x-1;
	for (int i=1;i<20;i++){
		val += pow(-1,i)*pow(s,i)/i;
	}

	//val = (x - 1) - (x - 1)*(x - 1) / 2 + (x - 1)*(x - 1)*(x - 1) / 3 - (x - 1)*(x - 1)*(x - 1)*(x - 1) / 4 + (x - 1)*(x - 1)*(x - 1)*(x - 1)*(x - 1) / 5 - (x - 1)*(x - 1)*(x - 1)*(x - 1)*(x - 1)*(x - 1) / 6;

	return val;
}
double pow(double x,double y){
	if(y==0){return x;}
	else{return x*pow(x,y-1);}
}

int main(int argc,char**argv)
{
	double param,result;
	param = 2;
	result = log(param);
	cout<< "log of "<<param<<" is "<<result<<endl;
	return 0;
}
