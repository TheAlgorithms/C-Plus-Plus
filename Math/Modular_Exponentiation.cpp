/*
Modular Exponentiation:
Sometimes when performing x^y where x and y are very large,
the answer is taken modulo a very large prime to prevent overflow.

Using following property of modular arithmetic:
(ab) mod p = (a mod p)(b mod p) mod p

Time complexity: O(log y)

Author: WilliamHYZhang
Credit: https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/
*/
#include <iostream>
using namespace std;

const int MOD = 1000000007; //10e9 = 7, large prime common in many programming problems

long long mpow(long long x, long long y){ //returns (x^y) % MOD
	//initialize return value
	long long ret = 1;
	//update x
	x = x % MOD;
	while(y > 0){
		//if y is odd, multiply return value with x and take modulus
		if(y & 1)
			ret = (ret*x) % MOD;
		//y is even
		y >>= 1; //right shift, equivalent to y = y/2
		//square x and take modulus
		x = (x*x) % MOD;
	}
	return ret;
}

int main(){
	//Some examples
	cout << "(2 ^ 5) mod " << MOD << " is: " << mpow(2, 5) << endl;
	cout << "(420 ^ 69) mod " << MOD << " is: " << mpow(420, 69) << endl;
	cout << "(1234567890 ^ 1234567890) mod " << MOD << " is: " << mpow(1234567890, 1234567890) << endl;
}