//Author : Junth Basnet
//Time Complexity : O(logn)

#include<bits/stdc++.h>
using namespace std;

long long binaryExponentiation(int a, int n) {
	if (n == 0) {
		return 1;
	}
	if (n % 2 == 1) {
		return binaryExponentiation(a, n - 1) * a;
	}
	else {
		long long b = binaryExponentiation(a, n / 2);
		return b * b;
	}

}

int main() {
	int base, power;
	cout << "Enter the base and power:";
	cin >> base;
	cin >> power;

	long long result = binaryExponentiation(base, power);
	cout << result;

	return 0;
}