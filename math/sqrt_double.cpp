/**
 * @file
 * @brief Calculate square roots using the
 * [bisection method](https://en.wikipedia.org/wiki/Bisection_method).
 * @details Normalize the input as a mantissa times an even power of two.
 * Bisection then operates on a bounded interval, avoiding overflow when
 * squaring and avoiding reciprocals of very small numbers. Stop when the
 * midpoint equals an endpoint because floating-point numbers cannot represent
 * any further subdivision. The result approximates the nonnegative root to
 * floating-point precision; correct rounding is not guaranteed.
 * @see numerical_methods/newton_raphson_method.cpp
 * @see numerical_methods/false_position.cpp
 */
#include <cassert>  /// for assert
#include <cmath>    /// for floating-point decomposition and test comparisons
#include <initializer_list>  /// for the test input list
#include <iostream>          /// for std::cout
#include <limits>            /// for std::numeric_limits

/**
 * @namespace math
 * @brief Mathematical algorithms.
 */
namespace math {
/**
 * @brief Approximate the nonnegative square root by bisection.
 * @details For a positive finite input, write a = m * 2^e with even e and
 * 0.5 <= m < 2. Then sqrt(a) = sqrt(m) * 2^(e/2), and sqrt(m) lies in
 * [0.5, 2]. This also handles subnormal inputs without taking their reciprocal.
 * If the midpoint squared exceeds m, keep the lower half of the interval;
 * otherwise keep the upper half.
 * For example, 18 = 1.125 * 2^4, so bisect to approximate sqrt(1.125)
 * and scale the result by 2^2 to obtain approximately 4.242640687.
 * Time complexity is O(p), where p is the number of significand bits;
 * auxiliary space is O(1).
 * @param a Number whose square root is requested.
 * @returns Approximate square root for nonnegative finite inputs, preserving
 * signed zero. Positive infinity is returned unchanged; negative inputs and
 * NaN return NaN.
 */
double Sqrt(double a) {
    if (std::isnan(a) || a < 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    if (a == 0 || std::isinf(a)) {
        return a;
    }

    int exponent = 0;
    double mantissa = std::frexp(a, &exponent);
    if (exponent % 2 != 0) {
        mantissa *= 2;
        --exponent;
    }

    double low = 0.5;
    double high = 2;
    while (true) {
        const double mid = low + (high - low) / 2;
        if (mid == low || mid == high) {
            return std::ldexp(mid, exponent / 2);
        }
        const double square = mid * mid;
        if (square == mantissa) {
            return std::ldexp(mid, exponent / 2);
        }
        if (square > mantissa) {
            high = mid;
        } else {
            low = mid;
        }
    }
}
}  // namespace math

/**
 * @brief Self-tests including regressions for nontermination and extreme
 * inputs.
 * @returns void
 */
static void test() {
    assert(math::Sqrt(0) == 0);
    assert(std::signbit(math::Sqrt(-0.0)));
    assert(math::Sqrt(1) == 1);
    assert(math::Sqrt(4) == 2);
    assert(math::Sqrt(0.25) == 0.5);
    assert(std::isnan(math::Sqrt(-1)));
    assert(std::isnan(math::Sqrt(-std::numeric_limits<double>::infinity())));
    assert(std::isnan(math::Sqrt(std::numeric_limits<double>::quiet_NaN())));
    assert(math::Sqrt(std::numeric_limits<double>::infinity()) ==
           std::numeric_limits<double>::infinity());

    // Compare relative error because the input spans many orders of magnitude.
    const auto check = [](double value) {
        const double expected = std::sqrt(value);
        const double actual = math::Sqrt(value);
        assert(std::isfinite(actual));
        assert(std::abs(actual - expected) / expected <=
               2 * std::numeric_limits<double>::epsilon());
    };
    for (double value : {2.0, 3.0, 0.1, 10000000001.0,
                         std::numeric_limits<double>::denorm_min(),
                         std::numeric_limits<double>::min(),
                         std::numeric_limits<double>::max(),
                         std::nextafter(1.0, 0.0), std::nextafter(1.0, 2.0)}) {
        check(value);
    }

    // Exercise both exponent parities across the normal double range.
    for (int exponent = std::numeric_limits<double>::min_exponent;
         exponent <= std::numeric_limits<double>::max_exponent; ++exponent) {
        check(std::ldexp(0.5, exponent));
        check(std::ldexp(0.75, exponent));
    }
    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Run the self-tests without interactive input.
 * @returns 0 on successful completion.
 */
int main() {
    test();
    return 0;
}
