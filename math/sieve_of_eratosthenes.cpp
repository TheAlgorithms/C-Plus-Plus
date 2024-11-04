/**
 * @file
 * @brief Prime Numbers using [Sieve of
 * Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)
 * @details
 * Sieve of Eratosthenes is an algorithm that finds all the primes
 * between 2 and N.
 *
 * Time Complexity  : \f$O(N \cdot\log \log N)\f$
 * <br/>Space Complexity : \f$O(N)\f$
 *
 * @see primes_up_to_billion.cpp prime_numbers.cpp
 */

#include <cstdint>
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @namespace sieve_of_eratosthenes
 * @brief Functions for finding Prime Numbers using Sieve of Eratosthenes
 */
namespace sieve_of_eratosthenes {
/**
 * @brief Function to sieve out the primes
 * @details
 * This function finds all the primes between 2 and N using the Sieve of
 * Eratosthenes algorithm. It starts by assuming all numbers (except zero and
 * one) are prime and then iteratively marks the multiples of each prime as
 * non-prime.
 *
 * Contains a common optimization to start eliminating multiples of
 * a prime p starting from p * p since all of the lower multiples
 * have been already eliminated.
 * @param N number till which primes are to be found
 * @return is_prime a vector of `N + 1` booleans identifying if `i`^th number is
 * a prime or not
 */
std::vector<bool> sieve(uint32_t N) {
    std::vector<bool> is_prime(N + 1, true);  // Initialize all as prime numbers
    is_prime[0] = is_prime[1] = false;        // 0 and 1 are not prime numbers

    for (uint32_t i = 2; i * i <= N; i++) {
        if (is_prime[i]) {
            for (uint32_t j = i * i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

/**
 * @brief Function to print the prime numbers
 * @param N number till which primes are to be found
 * @param is_prime a vector of `N + 1` booleans identifying if `i`^th number is
 * a prime or not
 */
void print(uint32_t N, const std::vector<bool> &is_prime) {
    for (uint32_t i = 2; i <= N; i++) {
        if (is_prime[i]) {
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;
}

}  // namespace sieve_of_eratosthenes
}  // namespace math

/**
 * @brief Self-test implementations
 * @return void
 */
static void tests() {
    std::vector<bool> is_prime_1 =
        math::sieve_of_eratosthenes::sieve(static_cast<uint32_t>(10));
    std::vector<bool> is_prime_2 =
        math::sieve_of_eratosthenes::sieve(static_cast<uint32_t>(20));
    std::vector<bool> is_prime_3 =
        math::sieve_of_eratosthenes::sieve(static_cast<uint32_t>(100));

    std::vector<bool> expected_1{false, false, true,  true,  false, true,
                                 false, true,  false, false, false};
    assert(is_prime_1 == expected_1);

    std::vector<bool> expected_2{false, false, true,  true,  false, true,
                                 false, true,  false, false, false, true,
                                 false, true,  false, false, false, true,
                                 false, true,  false};
    assert(is_prime_2 == expected_2);

    std::vector<bool> expected_3{
        false, false, true,  true,  false, true,  false, true,  false, false,
        false, true,  false, true,  false, false, false, true,  false, true,
        false, false, false, true,  false, false, false, false, false, true,
        false, true,  false, false, false, false, false, true,  false, false,
        false, true,  false, true,  false, false, false, true,  false, false,
        false, false, false, true,  false, false, false, false, false, true,
        false, true,  false, false, false, false, false, true,  false, false,
        false, true,  false, true,  false, false, false, false, false, true,
        false, false, false, true,  false, false, false, false, false, true,
        false, false, false, false, false, false, false, true,  false, false,
        false};
    assert(is_prime_3 == expected_3);

}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
