/**
 * @file
 * @brief Implementation of [the inverse square root
 * Root](https://medium.com/hard-mode/the-legendary-fast-inverse-square-root-e51fee3b49d9).
 * @details
 * Two implementation to calculate inverse inverse root,
 * from Quake III Arena (C++ version) and with a standard library (`cmath`).
 * This algorithm is used to calculate shadows in Quake III Arena.
 */

#include <cassert>   /// for assert
#include <cmath>     /// for `std::sqrt`
#include <iostream>  /// for IO operations
#include <limits>    /// for numeric_limits

/**
 * @brief This is the function that calculates the fast inverse square root.
 * The following code is the fast inverse square root implementation from
 * Quake III Arena (Adapted for C++). More information can be found at
 * [Wikipedia](https://en.wikipedia.org/wiki/Fast_inverse_square_root)
 * @tparam T floating type
 * @tparam iterations inverse square root, the greater the number of
 * iterations, the more exact the result will be (1 or 2).
 * @param x value to calculate
 * @return the inverse square root
 */
template <typename T = double, char iterations = 2>
inline T Fast_InvSqrt(T x) {
    using Tint = typename std::conditional<sizeof(T) == 8, std::int64_t,
                                           std::int32_t>::type;
    T y = x;
    T x2 = y * 0.5;

    Tint i =
        *reinterpret_cast<Tint *>(&y);  // Store floating-point bits in integer

    i = (sizeof(T) == 8 ? 0x5fe6eb50c7b537a9 : 0x5f3759df) -
        (i >> 1);  // Initial guess for Newton's method

    y = *reinterpret_cast<T *>(&i);  // Convert new bits into float

    y = y * (1.5 - (x2 * y * y));  // 1st iteration Newton's method
    if (iterations == 2) {
        y = y * (1.5 - (x2 * y * y));  // 2nd iteration, the more exact result
    }
    return y;
}

/**
 * @brief This is the function that calculates the fast inverse square root.
 * The following code is the fast inverse square root with standard lib (cmath)
 * More information can be found at
 * [LinkedIn](https://www.linkedin.com/pulse/fast-inverse-square-root-still-armin-kassemi-langroodi)
 * @tparam T floating type
 * @param number value to calculate
 * @return the inverse square root
 */
template <typename T = double>
T Standard_InvSqrt(T number) {
    T squareRoot = sqrt(number);
    return 1.0f / squareRoot;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    const float epsilon = 1e-3f;

    /* Tests with multiple values */
    assert(std::fabs(Standard_InvSqrt<float>(100.0f) - 0.0998449f) < epsilon);
    assert(std::fabs(Standard_InvSqrt<double>(36.0f) - 0.166667f) < epsilon);
    assert(std::fabs(Standard_InvSqrt(12.0f) - 0.288423f) < epsilon);
    assert(std::fabs(Standard_InvSqrt<double>(5.0f) - 0.447141f) < epsilon);

    assert(std::fabs(Fast_InvSqrt<float, 1>(100.0f) - 0.0998449f) < epsilon);
    assert(std::fabs(Fast_InvSqrt<double, 1>(36.0f) - 0.166667f) < epsilon);
    assert(std::fabs(Fast_InvSqrt(12.0f) - 0.288423) < epsilon);
    assert(std::fabs(Fast_InvSqrt<double>(5.0f) - 0.447141) < epsilon);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    std::cout << "The Fast inverse square root of 36 is: "
              << Fast_InvSqrt<float, 1>(36.0f) << std::endl;
    std::cout << "The Fast inverse square root of 36 is: "
              << Fast_InvSqrt<double, 2>(36.0f) << " (2 iterations)"
              << std::endl;
    std::cout << "The Fast inverse square root of 100 is: "
              << Fast_InvSqrt(100.0f)
              << " (With default template type and iterations: double, 2)"
              << std::endl;
    std::cout << "The Standard inverse square root of 36 is: "
              << Standard_InvSqrt<float>(36.0f) << std::endl;
    std::cout << "The Standard inverse square root of 100 is: "
              << Standard_InvSqrt(100.0f)
              << " (With default template type: double)" << std::endl;
}
