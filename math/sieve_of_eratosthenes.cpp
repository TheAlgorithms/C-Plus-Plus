/**
 * @file
 * @brief Get list of prime numbers using Sieve of Eratosthenes
 * Sieve of Eratosthenes is an algorithm to find the primes
 * that is between 2 to N (as defined in main).
 *
 * Time Complexity  : \f$O(N \cdot\log N)\f$
 * <br/>Space Complexity : \f$O(N)\f$
 *
 * @see primes_up_to_billion.cpp prime_numbers.cpp
 */

#include <iostream> // for io operations

/**
 * This is the function that finds the primes and eliminates
 * the multiples.
 */
void sieve(uint32_t N, bool *isprime) {
    isprime[0] = true;
    isprime[1] = true;
    for (uint32_t i = 2; i * i <= N; i++) {
        if (!isprime[i]) {
            for (uint32_t j = (i << 1); j <= N; j = j + i) {
                isprime[j] = true;
            }
        }
    }
}

/**
 * This function prints out the primes to STDOUT
 */
void print(uint32_t N, const bool *isprime) {
    for (uint32_t i = 2; i <= N; i++) {
        if (!isprime[i]) {
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;
}

/**
 * Main function
 */
int main() {
    uint32_t N = 100;
    bool *isprime = new bool[N];
    sieve(N, isprime);
    print(N, isprime);
    delete[] isprime;

    return 0;
}
