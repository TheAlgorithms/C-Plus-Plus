/**
 * @file
 * @brief GCD using [extended Euclid's algorithm]
 * (https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm)
 *
 * Finding coefficients of a and b ie x and y in Bézout's identity
 * \f[\text{gcd}(a, b) = a \times x + b \times y \f]
 * This is also used in finding Modular
 * multiplicative inverse of a number. (A * B)%M == 1 Here B is the MMI of A for
 * given M, so extendedEuclid (A, M) gives B.
 */
#include <algorithm>  // for swap function
#include <iostream>
#include <cstdint>
#include <cassert>    // Required for automated testing assertions

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
 * @brief Automated self-test cases matching repository CI standards
 * @return void
 */
/**
 * @brief Automated self-test cases matching repository CI standards
 * @return void
 */
static void test() {
    uint32_t gcd;
    int32_t x, y;

    // Test Case 1: Standard positive integers using recursive function
    extendedEuclid(uint32_t(35), uint32_t(15), &gcd, &x, &y);
    assert(gcd == 5);

    // Test Case 2: Standard positive integers using iterative function
    extendedEuclid_1(uint32_t(35), uint32_t(15), &gcd, &x, &y);
    assert(gcd == 5);

    // Test Case 3: Coprime numbers (GCD should be 1)
    extendedEuclid(uint32_t(13), uint32_t(7), &gcd, &x, &y);
    assert(gcd == 1);

    // Test Case 4: One input is zero
    extendedEuclid(uint32_t(0), uint32_t(5), &gcd, &x, &y);
    assert(gcd == 5);

    std::cout << "All automated tests passed successfully!" << std::endl;
}

/// Main function
int main() {
    test(); // Execute the non-interactive automated test suite
    return 0;
}