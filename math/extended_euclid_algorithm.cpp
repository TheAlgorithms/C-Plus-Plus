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
#include <array>    // for std::array
#include <cassert>  // for assert
#include <cstdint>
#include <iostream>

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
    const std::array<std::array<uint32_t, 3>, 8> test_cases = {
        {{240, 46, 2}, {46, 240, 2}, {35, 64, 1}, {64, 35, 1},
         {42, 0, 42}, {0, 42, 42},  {0, 0, 0},   {42, 42, 42}}};

    for (const auto& test_case : test_cases) {
        const uint32_t a = test_case[0];
        const uint32_t b = test_case[1];
        const uint32_t expected_gcd = test_case[2];
        uint32_t gcd = 0;
        int32_t x = 0, y = 0;

        extendedEuclid(a, b, &gcd, &x, &y);
        assert(gcd == expected_gcd);
        assert(static_cast<int64_t>(a) * x + static_cast<int64_t>(b) * y == gcd);

        extendedEuclid_1(a, b, &gcd, &x, &y);
        assert(gcd == expected_gcd);
        assert(static_cast<int64_t>(a) * x + static_cast<int64_t>(b) * y == gcd);
    }
}

/// Main function
int main() {
    test();
    uint32_t a, b, gcd;
    int32_t x, y;
    std::cin >> a >> b;
    extendedEuclid(a, b, &gcd, &x, &y);
    std::cout << gcd << " " << x << " " << y << std::endl;
    extendedEuclid_1(a, b, &gcd, &x, &y);
    std::cout << gcd << " " << x << " " << y << std::endl;
    return 0;
}
