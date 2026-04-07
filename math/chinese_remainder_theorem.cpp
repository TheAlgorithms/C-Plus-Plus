/**
 * @file chinese_remainder_theorem.cpp
 * @brief Solves simultaneous congruences with CRT.
 * @details
 * Merges congruences x ≡ ai (mod mi) one by one. Works for both coprime and
 * non-coprime moduli; detects inconsistency when no solution exists.
 * Time complexity is O(k log M) for k equations with arithmetic on merged modulus.
 * @author OpenAI
 * @see https://en.wikipedia.org/wiki/Chinese_remainder_theorem
 */

#include <cassert>
#include <iostream>
#include <vector>

/**
 * @brief Stores one congruence equation.
 */
struct Congruence {
    long long remainder;
    long long modulus;
};

/**
 * @brief Stores solution of a CRT system.
 */
struct CtrResult {
    bool has_solution;
    long long value;
    long long modulus;
};

/**
 * @brief Extended gcd for coefficients in ax+by=gcd(a,b).
 * @param a first integer.
 * @param b second integer.
 * @param x coefficient for a.
 * @param y coefficient for b.
 * @returns gcd(a,b).
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
 * @brief Merges two congruences into one.
 * @param a first congruence.
 * @param b second congruence.
 * @returns merged congruence result and consistency flag.
 */
CtrResult merge(const CtrResult &a, const Congruence &b) {
    if (!a.has_solution) {
        return a;
    }
    long long x = 0, y = 0;
    long long g = extended_gcd(a.modulus, b.modulus, x, y);
    long long diff = b.remainder - a.value;
    if (diff % g != 0) {
        return {false, 0, 0};
    }

    __int128 lcm = (__int128)a.modulus / g * b.modulus;
    __int128 mul = (__int128)(diff / g) * x;
    long long mod2 = b.modulus / g;
    long long step = static_cast<long long>(mul % mod2);
    if (step < 0) {
        step += mod2;
    }

    __int128 merged = (__int128)a.value + (__int128)step * a.modulus;
    long long value = static_cast<long long>(merged % lcm);
    if (value < 0) {
        value += static_cast<long long>(lcm);
    }

    return {true, value, static_cast<long long>(lcm)};
}

/**
 * @brief Solves x ≡ ai (mod mi) for a system of congruences.
 * @param equations list of equations.
 * @returns solution x modulo M if one exists.
 */
CtrResult chinese_remainder_theorem(const std::vector<Congruence> &equations) {
    CtrResult current{true, 0, 1};
    for (const Congruence &eq : equations) {
        Congruence normalized = eq;
        normalized.remainder %= normalized.modulus;
        if (normalized.remainder < 0) {
            normalized.remainder += normalized.modulus;
        }
        current = merge(current, normalized);
        if (!current.has_solution) {
            break;
        }
    }
    return current;
}

/**
 * @brief Self-tests for CRT solver.
 * @returns void.
 */
static void test() {
    CtrResult r1 = chinese_remainder_theorem({{2, 3}, {3, 5}, {2, 7}});
    assert(r1.has_solution);
    assert(r1.value == 23 && r1.modulus == 105);

    CtrResult r2 = chinese_remainder_theorem({{1, 2}, {1, 4}});
    assert(r2.has_solution);
    assert(r2.value == 1 && r2.modulus == 4);

    CtrResult r3 = chinese_remainder_theorem({{1, 2}, {0, 4}});
    assert(!r3.has_solution);

    CtrResult r4 = chinese_remainder_theorem({{4, 6}, {10, 14}});
    assert(r4.has_solution);
    assert(r4.value % 6 == 4 && r4.value % 14 == 10);

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
