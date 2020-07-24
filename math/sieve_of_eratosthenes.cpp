/**
 * @file
 * @brief Get list of prime numbers using Sieve of Eratosthenes
 * @details
 * Sieve of Eratosthenes is an algorithm that finds all the primes
 * between 2 and N.
 *
 * Time Complexity  : \f$O(N \cdot\log \log N)\f$
 * <br/>Space Complexity : \f$O(N)\f$
 *
 * @see primes_up_to_billion.cpp prime_numbers.cpp
 */

#include <cassert>
#include <iostream>
#include <vector>

/**
 * This is the function that finds the primes and eliminates the multiples.
 * Contains a common optimization to start eliminating multiples of
 * a prime p starting from p * p since all of the lower multiples
 * have been already eliminated.
 * @param N number of primes to check
 * @return is_prime a vector of `N + 1` booleans identifying if `i`^th number is a prime or not
 */
std::vector<bool> sieve(uint32_t N) {
    std::vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;
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
 * This function prints out the primes to STDOUT
 * @param N number of primes to check
 * @param is_prime a vector of `N + 1` booleans identifying if `i`^th number is a prime or not
 */
void print(uint32_t N, const std::vector<bool> &is_prime) {
    for (uint32_t i = 2; i <= N; i++) {
        if (is_prime[i]) {
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;
}

/**
 * Test implementations
 */
void tests() {
  //                    0      1      2     3     4      5     6      7     8      9      10
  std::vector<bool> ans{false, false, true, true, false, true, false, true, false, false, false};
  assert(sieve(10) == ans);
}

/**
 * Main function
 */
int main() {
    tests();

    uint32_t N = 100;
    std::vector<bool> is_prime = sieve(N);
    print(N, is_prime);
    return 0;
}
