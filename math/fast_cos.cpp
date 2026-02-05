/**
 * @file
 * @brief Fast approximation of cosine via phase-shifted sine.
 * [Wikipedia](https://en.wikipedia.org/wiki/Cosine)
 * @details
 * Uses the identity cos(x) = sin(x + pi/2) and a truncated Taylor polynomial
 * for sine after range reduction to [-pi/2, pi/2]. This favors speed over
 * precision for single-precision workloads.
 * @author [Bill](https://github.com/yluoc)
 * @see fast_sin.cpp
 */

#include <cassert>      /// for assert
#include <cmath>        /// for std::floor, std::sin, std::cos, std::fabs
#include <iostream>     /// for IO operations
#include <type_traits>  /// for std::is_floating_point

/**
 * @namespace math
 * @brief Math algorithms and approximations.
 */
namespace math {

constexpr double InvPi = 0.31830988618379067154;
constexpr double TwoPi = 6.28318530717958647692;
constexpr double HalfPi = 1.57079632679489661923;
constexpr double Pi = 3.14159265358979323846;

/**
 * @brief Fast approximation of sine.
 * @tparam T floating-point type
 * @param x angle in radians
 * @returns approximate sin(x)
 */
template <class T>
T fast_sin(T x) {
    static_assert(std::is_floating_point<T>::value,
                  "fast_sin requires a floating-point type");

    // Normalize to [-pi, pi].
    x = x - static_cast<T>(kTwoPi) *
                std::floor((x + static_cast<T>(kPi)) * static_cast<T>(kInvPi) *
                           static_cast<T>(0.5));

    // Fold to [-pi/2, pi/2] for better accuracy.
    if (x > static_cast<T>(kHalfPi)) {
        x = static_cast<T>(kPi) - x;
    } else if (x < -static_cast<T>(kHalfPi)) {
        x = -static_cast<T>(kPi) - x;
    }

    const T x2 = x * x;
    return x * (static_cast<T>(1.0) -
                x2 * (static_cast<T>(0.16666667) -
                      x2 * (static_cast<T>(0.0083333337) -
                            x2 * (static_cast<T>(0.00019841270) -
                                  x2 * static_cast<T>(0.0000027557319)))));
}

/**
 * @brief Backward-compatible wrapper for float inputs.
 * @param x angle in radians
 * @returns approximate sin(x)
 */
inline float fastSin(float x) { return fast_sin(x); }

/**
 * @brief Fast approximation of cosine.
 * @tparam T floating-point type
 * @param x angle in radians
 * @returns approximate cos(x)
 */
template <class T>
T fast_cos(T x) {
    static_assert(std::is_floating_point<T>::value,
                  "fast_cos requires a floating-point type");
    return fast_sin(x + static_cast<T>(kHalfPi));
}

/**
 * @brief Backward-compatible wrapper for float inputs.
 * @param x angle in radians
 * @returns approximate cos(x)
 */
inline float fastCos(float x) {
    return fastSin(x + static_cast<float>(HalfPi));
}

}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    const double epsilon = 0.002;

    /* Compare with std::cos for representative values */
    auto check = [&](double x) {
        const double approx = math::fast_cos(x);
        const double exact = std::cos(x);
        assert(std::fabs(approx - exact) < epsilon);
    };

    check(0.0);
    check(0.1);
    check(0.5);
    check(1.0);
    check(1.5);
    check(-0.5);
    check(-1.5);
    check(math::Pi / 6.0);
    check(math::Pi / 4.0);
    check(math::Pi / 2.0);
    check(math::TwoPi);
    check(12.345);

    // this lets the user know that the tests have passed
    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    std::cout << "fast_cos(1) ~ " << math::fast_cos(1.0f) << std::endl;
    std::cout << "std::cos(1) = " << std::cos(1.0) << std::endl;
    return 0;
}
