/**
 * @file
 * @brief The Sieve of Eratosthenes
 * @details
 * [Wikipedia](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)
 * Pass "print" as a command line arg to see the generated list of primes
 * @author [Keval Kapdee](https://github.com/thechubbypanda)
 */

#include <iostream> // For IO
#include <vector> // For array-like storage
#include <chrono> // For timing the sieve
#include <string> // For string handling

/**
 * @brief Main function
 * @param argc commandline argument count
 * @param argv commandline array of arguments
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
	// The largest prime we will check for
    auto end = 10000;

	// Store a boolean for every number wich states if that index is prime or not
	auto primes = std::vector<bool>(end, true);

	auto start = std::chrono::high_resolution_clock::now();

	primes[0] = false;
	primes[1] = false;

	// The sieve sets values to false as they are found not prime
	for (int n = 2; n < end; n++) {
		for (int multiple = n << 1; multiple < end; multiple += n) {
			primes[multiple] = false;
		}
	}

	// Time difference calculation
	auto time = std::chrono::duration_cast
	        <std::chrono::duration<double, std::ratio<1>>>
	        (std::chrono::high_resolution_clock::now() - start)
	        .count();

	// Print the primes if we see that "print" was passed as an arg
	if (argc > 1 && argv[1] == std::string("print")) {
		for (int i = 0; i < primes.size(); i++) {
			if (primes[i]) std::cout << i << std::endl;
		}
	}

	std::cout << "Time taken: " << time << " seconds" << std::endl;

	return 0;
}
