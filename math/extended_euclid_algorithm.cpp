/**
 * @file
 * @brief GCD using [extended Euclid's algorithm]
 * (https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm)
 *
 * Finding coefficients of a and b ie x and y in  Bézout's identity
 * \f[\text{gcd}(a, b) = a \times x + b \times y \f]
 * This is also used in finding Modular
 * multiplicative inverse of a number. (A * B)%M == 1 Here B is the MMI of A for
 * given M, so extendedEuclid (A, M) gives B.
 */
#include <algorithm>  // for swap function
#include <cassert>  /// for assert
#include <iostream>  /// for IO operations
#include <cstdint>

/**
 * function to update the coefficients per iteration
 * \f[r_0,\,r = r,\, r_0 - \text{quotient}\times r\f]
 *
 * @param[in,out] r signed or unsigned
 * @param[in,out] r0 signed or unsigned
 * @param[in] quotient  unsigned
 */
template <typename T, typename T2>
inline void update_step(T *r, T *r0, const T2 quotient) {
    T temp = *r;
    *r = *r0 - (quotient * temp);
    *r0 = temp;
}

/**
 * Implementation using iterative algorithm from
 * [Wikipedia](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Pseudocode)
 *
 * @param[in] A unsigned
 * @param[in] B unsigned
 * @param[out] GCD unsigned
 * @param[out] x signed
 * @param[out] y signed
 */
template <typename T1, typename T2>
void extendedEuclid_1(T1 A, T1 B, T1 *GCD, T2 *x, T2 *y) {
    if (B > A)
        std::swap(A, B);  // Ensure that A >= B

    T2 s = 0, s0 = 1;
    T2 t = 1, t0 = 0;
    T1 r = B, r0 = A;

    while (r != 0) {
        T1 quotient = r0 / r;
        update_step(&r, &r0, quotient);
        update_step(&s, &s0, quotient);
        update_step(&t, &t0, quotient);
    }
    *GCD = r0;
    *x = s0;
    *y = t0;
}

/**
 * Implementation using recursive algorithm
 *
 * @param[in] A unsigned
 * @param[in] B unsigned
 * @param[out] GCD unsigned
 * @param[in,out] x signed
 * @param[in,out] y signed
 */
template <typename T, typename T2>
void extendedEuclid(T A, T B, T *GCD, T2 *x, T2 *y) {
    if (B > A)
        std::swap(A, B);  // Ensure that A >= B

    if (B == 0) {
        *GCD = A;
        *x = 1;
        *y = 0;
    } else {
        extendedEuclid(B, A % B, GCD, x, y);
        T2 temp = *x;
        *x = *y;
        *y = temp - (A / B) * (*y);
    }
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    uint32_t gcd = 0;
    int32_t x = 0;
    int32_t y = 0;

    // 240 * (-9) + 46 * 47 = 2
    extendedEuclid(240u, 46u, &gcd, &x, &y);
    assert(gcd == 2);
    assert(static_cast<int32_t>(240) * x + static_cast<int32_t>(46) * y == static_cast<int32_t>(gcd));

    gcd = 0;
    x = 0;
    y = 0;
    extendedEuclid_1(240u, 46u, &gcd, &x, &y);
    assert(gcd == 2);
    assert(static_cast<int32_t>(240) * x + static_cast<int32_t>(46) * y == static_cast<int32_t>(gcd));

    // gcd(35, 15) = 5
    gcd = 0;
    x = 0;
    y = 0;
    extendedEuclid(35u, 15u, &gcd, &x, &y);
    assert(gcd == 5);
    assert(static_cast<int32_t>(35) * x + static_cast<int32_t>(15) * y == static_cast<int32_t>(gcd));

    gcd = 0;
    x = 0;
    y = 0;
    extendedEuclid_1(35u, 15u, &gcd, &x, &y);
    assert(gcd == 5);

    // coprime pair
    gcd = 0;
    x = 0;
    y = 0;
    extendedEuclid(17u, 13u, &gcd, &x, &y);
    assert(gcd == 1);

    std::cout << "All tests have successfully passed!\n";
}

/// Main function
int main() {
    test();  // run self-test implementations
    return 0;
}
