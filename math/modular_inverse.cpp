/**
 * @file modular_inverse.cpp
 * @brief Computes modular inverse using Fermat and extended Euclid methods.
 * @details
 * For prime moduli and gcd(a, mod)=1, inverse can be computed as a^(mod-2)
 * by Fermat's little theorem. For the general case, extended Euclidean
 * algorithm provides inverse when gcd(a, mod)=1.
 * @author OpenAI
 * @see https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
 */

#include <cassert>
#include <iostream>

/**
 * @brief Computes x, y and gcd for ax + by = gcd(a,b).
 * @param a first integer.
 * @param b second integer.
 * @param x reference to store coefficient of a.
 * @param y reference to store coefficient of b.
 * @returns gcd(a, b).
 */
long long extended_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a >= 0 ? a : -a;
    }
    long long x1 = 0, y1 = 0;
    long long g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

/**
 * @brief Computes (base^exp) % mod using binary exponentiation.
 * @param base base value.
 * @param exp exponent.
 * @param mod modulus.
 * @returns modular power.
 */
long long modular_power(long long base, long long exp, long long mod) {
    long long result = 1 % mod;
    base %= mod;
    if (base < 0) {
        base += mod;
    }
    while (exp > 0) {
        if (exp & 1LL) {
            result = static_cast<long long>((__int128)result * base % mod);
        }
        base = static_cast<long long>((__int128)base * base % mod);
        exp >>= 1;
    }
    return result;
}

/**
 * @brief Computes inverse of a modulo prime mod using Fermat theorem.
 * @param a number to invert.
 * @param mod prime modulus.
 * @returns inverse if exists, otherwise -1.
 */
long long mod_inverse_fermat(long long a, long long mod) {
    a %= mod;
    if (a < 0) {
        a += mod;
    }
    if (a == 0) {
        return -1;
    }
    return modular_power(a, mod - 2, mod);
}

/**
 * @brief Computes inverse of a modulo mod with extended Euclid.
 * @param a number to invert.
 * @param mod modulus.
 * @returns inverse if gcd(a,mod)=1, else -1.
 */
long long mod_inverse_extended_gcd(long long a, long long mod) {
    a %= mod;
    if (a < 0) {
        a += mod;
    }
    long long x = 0, y = 0;
    long long g = extended_gcd(a, mod, x, y);
    if (g != 1) {
        return -1;
    }
    x %= mod;
    if (x < 0) {
        x += mod;
    }
    return x;
}

/**
 * @brief Self-tests for modular inverse methods.
 * @returns void.
 */
static void test() {
    assert(mod_inverse_fermat(3, 11) == 4);
    assert(mod_inverse_fermat(10, 17) == 12);
    assert(mod_inverse_extended_gcd(3, 11) == 4);
    assert(mod_inverse_extended_gcd(10, 17) == 12);
    assert(mod_inverse_extended_gcd(6, 9) == -1);
    assert(mod_inverse_extended_gcd(-3, 11) == 7);

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
