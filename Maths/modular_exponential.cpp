#include <iostream>
using namespace std;

int modular_exponential(int base, int power, int mod) {
	if (power < 0)
		return -1;
	int result = 1;
	base %= mod;

	while (power > 0) {
		if (power & 1)
			result = (result * base) % mod;
		power = power >> 1;
		base = (base * base) % mod;
	}
	return result;
}

int main() {
	cout << modular_exponential(3, 200, 13) << endl;
	return 0;
}
