#include <iostream>

//binary exponentiation without recursion

long long binpow(long long a,long long b){

	long long res = 1;

	while(b > 0){
		if(b%2 == 1) res = res * a;
		a = a * a;
		b/=2;
	}

	return res;

}

//binary exponentiation without recursion using module

long long modbinpow(long long a,long long b,long long m){

	a%=m;

	long long res = 1;

	while(b > 0){
		if(b%2 == 1) res = res * a % m;
		a = a * a % m;
		b/=2;
	}

	return res;

}

int main(){

	std::cout << "Program to calculate power b to the base a module m(without recursion)\n";
	long long a,b,m;
	std::cout << "Enter base : ";
	std::cin >> a;
	std::cout << "Enter power : ";
	std::cin >> b;
	std::cout << "Enter module :";
	std::cin >> m;
	std::cout << "Power " << b << " to the base " << a << " is: ";
	std::cout <<  binpow(a, b) << std::endl;
	std::cout << "Power " << b << " to the base " << a << " module " << m << " is : ";
	std::cout <<  modbinpow(a, b, m) << std::endl;
	return 0;

}