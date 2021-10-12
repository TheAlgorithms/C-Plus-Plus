#include <iostream>
#include <vector>
#include <chrono>
#include <string>

int main(int argc, char *argv[]) {
	auto end = 10000;
	auto primes = std::vector<bool>(end, true);

	auto start = std::chrono::high_resolution_clock::now();

	primes[0] = false;
	primes[1] = false;

	for (int n = 2; n < end; n++) {
		for (int multiple = n << 1; multiple < end; multiple += n) {
			primes[multiple] = false;
		}
	}

	auto time = std::chrono::duration_cast
	        <std::chrono::duration<double, std::ratio<1>>>
	        (std::chrono::high_resolution_clock::now() - start)
	        .count();

	if (argc > 1 && argv[1] == std::string("print")) {
		for (int i = 0; i < primes.size(); i++) {
			if (primes[i]) std::cout << i << std::endl;
		}
	}

	std::cout << "Time taken: " << time << " seconds" << std::endl;

	return 0;
}
