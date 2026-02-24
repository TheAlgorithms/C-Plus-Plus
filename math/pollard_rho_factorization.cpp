/**
 * @file pollard_rho_factorization.cpp
 * @brief Integer factorization with Pollard's Rho + Miller-Rabin.
 * @details
 * Uses deterministic Miller-Rabin primality test and Pollard's Rho cycle
 * detection method to split composite numbers. Expected running time is around
 * O(n^(1/4)) for finding a non-trivial factor in practice.
 * @author OpenAI
 * @see https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

/**
 * @brief Computes (a*b) % mod safely for 64-bit values.
 * @param a first factor.
 * @param b second factor.
 * @param mod modulus.
 * @returns modular product.
 */
unsigned long long mul_mod(unsigned long long a, unsigned long long b,
                           unsigned long long mod) {
    return static_cast<unsigned long long>((__int128)a * b % mod);
}

/**
 * @brief Computes (base^exp) % mod.
 * @param base base value.
 * @param exp exponent.
 * @param mod modulus.
 * @returns modular power.
 */
unsigned long long pow_mod(unsigned long long base, unsigned long long exp,
                           unsigned long long mod) {
    unsigned long long result = 1ULL % mod;
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
 * @brief Checks if n is prime using deterministic Miller-Rabin witnesses.
 * @param n integer to test.
 * @returns true if n is prime, false otherwise.
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
        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Polynomial used by Pollard's Rho iteration.
 * @param x current value.
 * @param c constant parameter.
 * @param mod modulus.
 * @returns next sequence value.
 */
unsigned long long f(unsigned long long x, unsigned long long c,
                     unsigned long long mod) {
    return (mul_mod(x, x, mod) + c) % mod;
}

/**
 * @brief Finds a non-trivial factor of n with Pollard's Rho.
 * @param n odd composite number.
 * @returns one factor in range (1, n).
 */
unsigned long long pollard_rho(unsigned long long n) {
    if (n % 2ULL == 0ULL) {
        return 2ULL;
    }
    if (n % 3ULL == 0ULL) {
        return 3ULL;
    }

    for (unsigned long long c = 1ULL; c < 50ULL; ++c) {
        unsigned long long x = 2ULL;
        unsigned long long y = 2ULL;
        unsigned long long d = 1ULL;

        while (d == 1ULL) {
            x = f(x, c, n);
            y = f(f(y, c, n), c, n);
            unsigned long long diff = x > y ? x - y : y - x;
            d = std::gcd(diff, n);
        }
        if (d != n) {
            return d;
        }
    }
    return n;
}

/**
 * @brief Recursively decomposes n into prime factors.
 * @param n number to factor.
 * @param factors output list of prime factors.
 * @returns void.
 */
void factorize(unsigned long long n, std::vector<unsigned long long> &factors) {
    if (n == 1ULL) {
        return;
    }
    if (is_prime(n)) {
        factors.push_back(n);
        return;
    }
    unsigned long long divisor = pollard_rho(n);
    if (divisor == n) {
        factors.push_back(n);
        return;
    }
    factorize(divisor, factors);
    factorize(n / divisor, factors);
}

/**
 * @brief Self-tests for Pollard's Rho factorization.
 * @returns void.
 */
static void test() {
    std::vector<unsigned long long> f1;
    factorize(1ULL, f1);
    assert(f1.empty());

    std::vector<unsigned long long> f2;
    factorize(97ULL, f2);
    std::sort(f2.begin(), f2.end());
    assert((f2 == std::vector<unsigned long long>{97ULL}));

    std::vector<unsigned long long> f3;
    factorize(8051ULL, f3);  // 83 * 97
    std::sort(f3.begin(), f3.end());
    assert((f3 == std::vector<unsigned long long>{83ULL, 97ULL}));

    std::vector<unsigned long long> f4;
    factorize(1000000000039ULL, f4);  // prime
    assert(f4.size() == 1 && f4[0] == 1000000000039ULL);

    std::vector<unsigned long long> f5;
    factorize(1234567890ULL, f5);
    std::sort(f5.begin(), f5.end());
    assert((f5 == std::vector<unsigned long long>{2ULL, 3ULL, 3ULL, 5ULL, 3607ULL, 3803ULL}));

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
