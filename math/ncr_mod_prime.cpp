/**
 * @file ncr_mod_prime.cpp
 * @brief Computes nCr modulo prime using factorials and Lucas theorem.
 * @details
 * For n,p within manageable range, precompute factorial and inverse factorial
 * arrays and answer nCr in O(1). For very large n with small prime p, Lucas
 * theorem decomposes n and r in base p and multiplies small combinations.
 * @author OpenAI
 * @see https://en.wikipedia.org/wiki/Lucas%27s_theorem
 */

#include <cassert>
#include <iostream>
#include <vector>

/**
 * @brief Computes (base^exp) % mod.
 * @param base base value.
 * @param exp exponent value.
 * @param mod modulus.
 * @returns modular exponentiation result.
 */
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1LL) {
            result = static_cast<long long>((__int128)result * base % mod);
        }
        base = static_cast<long long>((__int128)base * base % mod);
        exp >>= 1LL;
    }
    return result;
}

/**
 * @brief Precomputes factorial and inverse factorial modulo p.
 * @param p prime modulus.
 * @param fact output factorial table.
 * @param inv_fact output inverse factorial table.
 * @returns void.
 */
void build_factorials(int p, std::vector<long long> &fact,
                      std::vector<long long> &inv_fact) {
    fact.assign(static_cast<size_t>(p), 1LL);
    inv_fact.assign(static_cast<size_t>(p), 1LL);
    for (int i = 1; i < p; ++i) {
        fact[static_cast<size_t>(i)] = fact[static_cast<size_t>(i - 1)] * i % p;
    }
    inv_fact[static_cast<size_t>(p - 1)] = mod_pow(fact[static_cast<size_t>(p - 1)], p - 2, p);
    for (int i = p - 2; i >= 0; --i) {
        inv_fact[static_cast<size_t>(i)] = inv_fact[static_cast<size_t>(i + 1)] * (i + 1) % p;
    }
}

/**
 * @brief Computes C(n,r) % p for 0 <= n,r < p using precomputed tables.
 * @param n total items.
 * @param r chosen items.
 * @param p prime modulus.
 * @param fact factorial table.
 * @param inv_fact inverse factorial table.
 * @returns nCr modulo p.
 */
long long ncr_small(int n, int r, int p, const std::vector<long long> &fact,
                    const std::vector<long long> &inv_fact) {
    if (r < 0 || r > n) {
        return 0;
    }
    return fact[static_cast<size_t>(n)] * inv_fact[static_cast<size_t>(r)] % p *
           inv_fact[static_cast<size_t>(n - r)] % p;
}

/**
 * @brief Computes C(n,r) % p using Lucas theorem.
 * @param n total items (can be very large).
 * @param r chosen items.
 * @param p small prime modulus.
 * @returns nCr modulo p.
 */
long long ncr_lucas(long long n, long long r, int p) {
    if (r < 0 || r > n) {
        return 0;
    }
    std::vector<long long> fact, inv_fact;
    build_factorials(p, fact, inv_fact);

    long long result = 1;
    while (n > 0 || r > 0) {
        int ni = static_cast<int>(n % p);
        int ri = static_cast<int>(r % p);
        if (ri > ni) {
            return 0;
        }
        result = result * ncr_small(ni, ri, p, fact, inv_fact) % p;
        n /= p;
        r /= p;
    }
    return result;
}

/**
 * @brief Computes C(n,r) % p with precomputed factorials for n < p.
 * @param n total items.
 * @param r chosen items.
 * @param p prime modulus.
 * @returns nCr modulo p.
 */
long long ncr_mod_prime(long long n, long long r, int p) {
    if (r < 0 || r > n) {
        return 0;
    }
    if (n >= p) {
        return ncr_lucas(n, r, p);
    }
    std::vector<long long> fact, inv_fact;
    build_factorials(p, fact, inv_fact);
    return ncr_small(static_cast<int>(n), static_cast<int>(r), p, fact, inv_fact);
}

/**
 * @brief Self-tests for nCr modulo prime functions.
 * @returns void.
 */
static void test() {
    assert(ncr_mod_prime(5, 2, 13) == 10);
    assert(ncr_mod_prime(10, 3, 17) == 1);
    assert(ncr_mod_prime(10, 11, 17) == 0);
    assert(ncr_lucas(1000, 200, 13) == ncr_mod_prime(1000, 200, 13));
    assert(ncr_lucas(1000000000000LL, 12345LL, 2) == 0);

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
