/**
 * @file
 * @brief Fast approximation of atan2 using a low-degree polynomial.
 * [Wikipedia](https://en.wikipedia.org/wiki/Atan2)
 * [StackExchange]
 * (https://math.stackexchange.com/questions/1098487/atan2-faster-approximation)
 * @details
 * This implementation approximates atan2(y, x) by reducing the inputs to the
 * first octant via a ratio of min(|x|, |y|) / max(|x|, |y|), evaluating a small
 * polynomial, and then restoring the correct quadrant. The coefficients are
 * tuned for speed and reasonable accuracy in single-precision workloads.
 * @author [Bill](https://github.com/yluoc)
 * @see complex_numbers.cpp
 */

#include <algorithm>    /// for std::min, std::max
#include <cassert>      /// for assert
#include <cmath>        /// for std::abs, std::atan2, std::fabs
#include <iostream>     /// for IO operations
#include <type_traits>  /// for std::is_floating_point

/**
 * @namespace math
 * @brief Math algorithms and approximations.
 */
namespace math {

constexpr double Pi = 3.1415926535897932384626433832795;
constexpr double HalfPi = 1.5707963267948966192313216916398;

/**
 * @brief Polynomial approximation for atan in the range [0, 1].
 * @tparam T floating-point type
 * @param a ratio of min(|x|, |y|) / max(|x|, |y|)
 * @returns approximate atan(a) in radians
 */
template <class T>
inline T atan_polynomial(T a) {
    const T s = a * a;
    const T c0 = static_cast<T>(-0.0464964749);
    const T c1 = static_cast<T>(0.15931422);
    const T c2 = static_cast<T>(-0.327622764);
    return ((c0 * s + c1) * s + c2) * s * a + a;
}

/**
 * @brief Fast approximation of atan2(y, x).
 * @tparam T floating-point type
 * @param y y-coordinate
 * @param x x-coordinate
 * @returns angle in radians in the range [-pi, pi]
 */
template <class T>
T fast_atan2(T y, T x) {
    static_assert(std::is_floating_point<T>::value,
                  "fast_atan2 requires a floating-point type");
    const T ax = std::abs(x);
    const T ay = std::abs(y);
    const T mn = std::min(ax, ay);
    const T mx = std::max(ax, ay);
    const T a = mn / (mx + static_cast<T>(1e-10));

    T r = atan_polynomial(a);

    if (ay > ax)
        r = static_cast<T>(HalfPi) - r;
    if (x < static_cast<T>(0))
        r = static_cast<T>(Pi) - r;
    if (y < static_cast<T>(0))
        r = -r;
    return r;
}

/**
 * @brief Backward-compatible wrapper for float inputs.
 * @param y y-coordinate
 * @param x x-coordinate
 * @returns angle in radians
 */
inline float fastAtan2(float y, float x) { return fast_atan2(y, x); }

}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    const double epsilon = 0.02;

    /* Basic axis and quadrant checks against std::atan2 */
    auto check = [&](double y, double x) {
        const double approx = math::fast_atan2(y, x);
        const double exact = std::atan2(y, x);
        assert(std::fabs(approx - exact) < epsilon);
    };

    check(0.0, 1.0);
    check(1.0, 0.0);
    check(-1.0, 0.0);
    check(1.0, 1.0);
    check(-1.0, 1.0);
    check(1.0, -1.0);
    check(-1.0, -1.0);
    check(0.5, 2.0);
    check(2.0, 0.5);
    check(-0.25, 3.0);
    check(3.0, -0.25);

    // this lets the user know that the tests have passed
    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    std::cout << "fast_atan2(1, 1) ~ " << math::fast_atan2(1.0f, 1.0f)
              << std::endl;
    std::cout << "std::atan2(1, 1) = " << std::atan2(1.0, 1.0) << std::endl;
    return 0;
}
