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

#include <iostream>

/** Maximum number of primes */
#define MAX 10000000

/** array to store the primes */
bool isprime[MAX];

/**
 * This is the function that finds the primes and eliminates
 * the multiples.
 */
void sieve(uint32_t N) {
    isprime[0] = false;
    isprime[1] = false;
    for (uint32_t i = 2; i * i <= N; i++) {
        if (isprime[i]) {
            for (uint32_t j = (i << 1); j <= N; j += i) {
                isprime[j] = false;
            }
        }
    }
}

/**
 * This function prints out the primes to STDOUT
 */
void print(uint32_t N) {
    for (uint32_t i = 1; i <= N; i++) {
        if (isprime[i]) {
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;
}

/**
 * Initialize the array
 */
void init() {
    for (uint32_t i = 1; i < MAX; i++) {
        isprime[i] = true;
    }
}

/** main function */
int main() {
    uint32_t N = 100;
    init();
    sieve(N);
    print(N);
    return 0;
}
