/**
 * @file
 * @brief [The Sieve of
 * Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)
 * @details
 * Store an array of booleans where a true value indicates that it's index is
 * prime. For all the values in the array starting from 2 which we know is
 * prime, we walk the array in multiples of the current outer value setting them
 * to not prime. If we remove all multiples of a value as we see it, we'll be
 * left with just primes.
 *
 * Pass "print" as a command line arg to see the generated list of primes
 * @author [Keval Kapdee](https://github.com/thechubbypanda)
 */

#include <cassert>   /// For assert
#include <chrono>    /// For timing the sieve
#include <iostream>  /// For IO operations
#include <string>    /// For string handling
#include <vector>    /// For std::vector

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief Performs the sieve
 * @param vec Array of bools, all initialised to true, where the number of
 * elements is the highest number we wish to check for primeness
 * @returns void
 */
void sieve(std::vector<bool> *vec) {
    (*vec)[0] = false;
    (*vec)[1] = false;

    // The sieve sets values to false as they are found not prime
    for (uint64_t n = 2; n < vec->size(); n++) {
        for (uint64_t multiple = n << 1; multiple < vec->size();
             multiple += n) {
            (*vec)[multiple] = false;
        }
    }
}

/**
 * @brief Prints all the indexes of true values in the passed std::vector
 * @param primes The vector that has been passed through `sieve(...)`
 * @returns void
 */
void print_primes(std::vector<bool> const &primes) {
    for (uint64_t i = 0; i < primes.size(); i++) {
        if (primes[i]) {
            std::cout << i << std::endl;
        }
    }
}
}  // namespace math

/**
 * @brief Self-tests the sieve function for major inconsistencies
 * @returns void
 */
static void test() {
    auto primes = std::vector<bool>(10, true);
    math::sieve(&primes);
    assert(primes[0] == false);
    assert(primes[1] == false);
    assert(primes[2] == true);
    assert(primes[3] == true);
    assert(primes[4] == false);
    assert(primes[5] == true);
    assert(primes[6] == false);
    assert(primes[7] == true);
    assert(primes[8] == false);
    assert(primes[9] == false);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @param argc commandline argument count
 * @param argv commandline array of arguments
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations

    // The largest prime we will check for
    auto max = 10000;

    // Store a boolean for every number which states if that index is prime or
    // not
    auto primes = std::vector<bool>(max, true);

    // Store the algorithm start time
    auto start = std::chrono::high_resolution_clock::now();

    // Run the sieve
    math::sieve(&primes);

    // Time difference calculation
    auto time = std::chrono::duration_cast<
                    std::chrono::duration<double, std::ratio<1>>>(
                    std::chrono::high_resolution_clock::now() - start)
                    .count();

    // Print the primes if we see that "print" was passed as an arg
    if (argc > 1 && argv[1] == std::string("print")) {
        math::print_primes(primes);
    }

    // Print the time taken we found earlier
    std::cout << "Time taken: " << time << " seconds" << std::endl;

    return 0;
}
