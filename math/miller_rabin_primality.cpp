/**
 * @file miller_rabin_primality.cpp
 * @brief Deterministic Miller-Rabin primality test for 64-bit range.
 * @details
 * Implements Miller-Rabin with a fixed witness set
 * {2,3,5,7,11,13,17,19,23,29,31,37}, which is deterministic for tested
 * numbers in competitive programming constraints below 3.2e18.
 * Uses safe modular multiplication with __int128.
 * @author OpenAI
 * @see https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
 */

#include <cassert>
#include <iostream>
#include <vector>

/**
 * @brief Multiplies two numbers modulo mod without overflow.
 * @param a first factor.
 * @param b second factor.
 * @param mod modulus.
 * @returns (a*b) % mod.
 */
unsigned long long mul_mod(unsigned long long a, unsigned long long b,
                           unsigned long long mod) {
    return static_cast<unsigned long long>((__int128)a * b % mod);
}

/**
 * @brief Computes modular exponentiation for unsigned long long values.
 * @param base base value.
 * @param exp exponent value.
 * @param mod modulus.
 * @returns (base^exp) % mod.
 */
unsigned long long pow_mod(unsigned long long base, unsigned long long exp,
                           unsigned long long mod) {
    unsigned long long result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1ULL) {
            result = mul_mod(result, base, mod);
        }
        base = mul_mod(base, base, mod);
        exp >>= 1ULL;
    }
    return result;
}

/**
 * @brief Tests primality for n using deterministic witnesses.
 * @param n integer to test.
 * @returns true when n is prime, false otherwise.
 */
bool is_prime(unsigned long long n) {
    if (n < 2) {
        return false;
    }
    for (unsigned long long p : std::vector<unsigned long long>{2ULL, 3ULL, 5ULL,
                                                                 7ULL, 11ULL,
                                                                 13ULL, 17ULL,
                                                                 19ULL, 23ULL,
                                                                 29ULL, 31ULL,
                                                                 37ULL}) {
        if (n % p == 0ULL) {
            return n == p;
        }
    }

    unsigned long long d = n - 1;
    int s = 0;
    while ((d & 1ULL) == 0ULL) {
        d >>= 1ULL;
        ++s;
    }

    const std::vector<unsigned long long> witnesses = {
        2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL,
        17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL};

    for (unsigned long long a : witnesses) {
        if (a >= n) {
            continue;
        }
        unsigned long long x = pow_mod(a, d, n);
        if (x == 1ULL || x == n - 1) {
            continue;
        }
        bool witness_composite = true;
        for (int r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                witness_composite = false;
                break;
            }
        }
        if (witness_composite) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Self-tests for Miller-Rabin primality routine.
 * @returns void.
 */
static void test() {
    assert(!is_prime(0));
    assert(!is_prime(1));
    assert(is_prime(2));
    assert(is_prime(9999999967ULL));
    assert(!is_prime(10000000000ULL));
    assert(!is_prime(341550071728321ULL));

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
