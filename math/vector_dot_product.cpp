/**
 * @file
 *
 * @brief Calculates the [dot
 * product](https://en.wikipedia.org/wiki/Dot_product) of two 3D mathematical
 * vectors.
 *
 *
 * @details The dot product of two mathematical vectors is a scalar.
 * Components of a vector are parts of a vector that determine its direction and
 * magnitude. A scalar is a quantity with only magnitude (no direction). The dot
 * product of two vectors can be found by getting the sum of the products of
 * their respective x, y, and z components.
 *
 * e.g.: dot product of <1, 2, 3> and <4, 5, 6> = (1 * 4) + (2 * 5) + (3 * 6) =
 *32 32 would be the result from the above operation.
 *
 *
 *
 * ### Example:
 * Example execution:
 *	* Enter components for first vector: -4 1 2
 *	* Enter components for the second vector: 0 -2 3
 *  The dot product of your vectors is: 4
 *
 *
 * @author [Benjamin Tran](https://github.com/benhtran)
 */

#include <array>     /// for std::array
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {

/**
 * @brief Function to calculate the scalar dot product of two mathematical
 * vectors.
 * @param vec1 is an array containing the components of the first mathematical
 * vector in the form {x,y,z}.
 * @param vec2 is an array containing the components of the second mathematical
 * vector in the form {x,y,z}.
 * @returns A double representing the scalar output.
 */
double dot(const std::array<double, 3> vec1, const std::array<double, 3> vec2) {
    return ((vec1[0] * vec2[0]) + (vec1[1] * vec2[1]) + (vec1[2] * vec2[2]));
}
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /// Performs a couple tests for the dot() function.

    double dot0 = math::dot({1, 2, 3}, {4, 5, 6});
    assert(dot0 == 32);

    double dot1 = math::dot({-3, -5, -4}, {1, 2, 6});
    assert(dot1 == -37);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations

    /// Stores two vector representations for input.
    std::array<double, 3> vec1{};
    std::array<double, 3> vec2{};

    /// Get components for the first vector.
    std::cout << "Enter components for first vector: ";
    std::cin >> vec1[0] >> vec1[1] >> vec1[2];

    /// Get components for the second vector.
    std::cout << "Enter components for second vector: ";
    std::cin >> vec2[0] >> vec2[1] >> vec2[2];

    /// Displays the result of the dot product operation.
    double result = math::dot(vec1, vec2);
    std::cout << "The dot product of your vectors is: " << result << "."
              << std::endl;

    return 0;
}
