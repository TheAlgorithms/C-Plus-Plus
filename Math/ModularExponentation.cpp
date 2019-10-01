#include<iostream>
using namespace std;

/*********************************
	@author Manas Uniyal
*********************************/

long long get_power(long long base, long long exponent, long long mod){
	if(exponent == 1){
		return base % mod;
	}
	long long x = get_power(base, exponent/2, mod);
	x = (x*x) % mod;
	if(exponent % 2){
		x  = (x*base) % mod;
	}
	return x;
}

int main(){
	long long base = 123;
	long long exponent = 897234;
	long long mod = 934;
	cout<<get_power(base, exponent, mod);
	return 0;
}
