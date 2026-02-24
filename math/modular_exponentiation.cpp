/**
 * @file modular_exponentiation.cpp
 * @brief Fast modular exponentiation using binary method.
 * @details
 * Repeated squaring computes (base^exp) % mod in O(log exp) time.
 * This is a foundational operation in modular arithmetic tasks in
 * competitive programming.
 * @author OpenAI
 * @see https://en.wikipedia.org/wiki/Modular_exponentiation
 */

#include <cassert>
#include <iostream>

/**
 * @brief Computes (base^exp) % mod efficiently.
 * @param base base value.
 * @param exp non-negative exponent.
 * @param mod positive modulus.
 * @returns value of (base^exp) modulo mod.
 */
long long modular_power(long long base, long long exp, long long mod) {
    if (mod == 1) {
        return 0;
    }
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
 * @brief Self-test implementation.
 * @returns void.
 */
static void test() {
    assert(modular_power(2, 10, 1000) == 24);
    assert(modular_power(2, 0, 100) == 1);
    assert(modular_power(0, 0, 1) == 0);
    assert(modular_power(3, 100, 1000000007) == 886041711);
    assert(modular_power(-2, 5, 13) == 7);

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
