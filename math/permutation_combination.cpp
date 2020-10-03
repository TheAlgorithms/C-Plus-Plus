#include <iostream>

// fact() calculates the factorial using recursion.
uint32_t fact(uint32_t num) {
	if(num == 0) {
		return 1;
	}
	else {
		return num * fact(num - 1);
	}
}

// perm() calculates the permutations using the formula:
// P(n, r) = n! / (n - r)!
uint32_t perm(uint32_t n, uint32_t r) {
	return fact(n) / fact(n - r);
}

// comb() calculates the combinations using the formula:
// C(n, r) = n! / ((n - r)! * r!)
uint32_t comb(uint32_t n, uint32_t r ) {
	return fact(n) / (fact(n - r) * fact(r));
}

int main() {
	uint32_t n;
	uint32_t r;

	// Values for n and r are asked.
	std::cout << "Enter the value of n: ";
	std::cin >> n;
	std::cout << "Enter the value of r ";
	std::cin >> r;

	// The combinations and the permutations are displayed.
	std::cout << "\nThe Permutations are: " << perm(n, r) << std::endl;
	std::cout << "The combinations are: " << comb(n, r) << "\n" << std::endl;
	return 0;
}
