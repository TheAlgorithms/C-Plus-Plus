#include <iostream>

// Theorem : a*b = gcd(a,b) * lcm(a,b); so lcm(a,b) = (a*b)/(gcd(a,b))

int gcd(int a,int b){
	return b == 0 ? a : gcd(b,a%b);
}

int main(){

	int a,b;

	std::cout << "Program to calculate lcm(A,B) (least common multiple(a,b))" << std::endl;
	std::cout << "Enter A: ";
	std::cin >> a;
	std::cout << "Enter B: ";
	std::cin >> b;

	std::cout << "LCM(A,B) is equal to : " << (a*b)/(gcd(a,b)) << std::endl;

	return 0;
}