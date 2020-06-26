
/*C++ inbuilt function for finding GCD*/

#include <iostream>
using namespace std;
int gcd(int a, int b) {
	if (b == 0) 
		return a; 
	return gcd(b, a % b); 	
} 
int main() 
{ 
	int a = 8, b = 6; 
	cout<<"GCD of two num is "<<gcd(a, b); 
	return 0; 
} 
//also theere is simple way to do gcd by using    __gcd(m, n)  where m ,n are numbers
