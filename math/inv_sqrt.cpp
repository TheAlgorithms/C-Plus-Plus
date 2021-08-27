/**
 * @file
 * @brief Calculate the inverse inverse root.
 * @details
 * Two implementation to calculate inverse inverse root,
 * from Quake III Arena (C++ version) and with standard lib (cmath)
 */

#include <cmath>        /// for `std::sqrt`
#include <iostream>     /// for IO operations
#include <type_traits>  /// for `static_assert`

#define MagicNBR_32 0x5f3759df
#define MagicNBR_64 0x5fe6eb50c7b537a9

/**
 * @brief This is the function that calculates the fast inverse square root.
 * The following code is the fast inverse square root implementation from Quake
 * III Arena (Adapted for C++)
 * More information can be found at [Wikipedia](https://en.wikipedia.org/wiki/Fast_inverse_square_root)
 * @tparam T floating type
 * @tparam iterations inverse square root, the greater the number of iterations,
 * the more exact the result will be (1 or 2).
 * @param x value to calculate
 * @return T return inverse square root
 */
template <typename T, char iterations = 2>
inline T Fast_InvSqrt(T x) {
    static_assert(std::is_floating_point<T>::value,
                  "T must be floating point type");
    static_assert(iterations == 1 or iterations == 2,
                  "itarations must equal 1 or 2");
    typedef typename std::conditional<sizeof(T) == 8, std::int64_t,
                                      std::int32_t>::type Tint;
    T y = x;
    T x2 = y * 0.5;
    Tint i = *(Tint *)&y;
    i = (sizeof(T) == 8 ? MagicNBR_64 : MagicNBR_32) - (i >> 1);
    y = *(T *)&i;
    y = y * (1.5 - (x2 * y * y));
    if (iterations == 2)
        y = y * (1.5 - (x2 * y * y));
    return y;
}

/**
 * @brief This is the function that calculates the fast inverse square root.
 * The following code is the fast inverse square root with standard lib (cmath)
 * More info:
 * https://www.linkedin.com/pulse/fast-inverse-square-root-still-armin-kassemi-langroodi
 * @tparam T floating type
 * @param x value to calculate
 * @return T return inverse square root
 */
template <typename T>
T Standard_InvSqrt(T number) {
    static_assert(std::is_floating_point<T>::value,
                  "T must be floating point type");
    T squareRoot = sqrt(number);
    return 1.0f / squareRoot;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    std::cout << "The Fast inverse square root of 36 is: "
              << Fast_InvSqrt<float, 1>(36.0f) << std::endl;
    std::cout << "The Fast inverse square root of 36 is: "
              << Fast_InvSqrt<double, 2>(36.0f) << " (2 iterations)"
              << std::endl;
    std::cout << "The Standard inverse square root of 36 is: "
              << Standard_InvSqrt<float>(36.0f) << std::endl;
}
