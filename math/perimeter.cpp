/**
 * @file
 * @brief Implementations for the
 * [perimeter](https://en.wikipedia.org/wiki/Perimeter) of various shapes
 * @details The perimeter of a shape is the sum of the lengths of its sides
 * or edges. All shapes have a formula for their perimeter.
 * These implementations support multiple return types.
 *
 * @author [OGscorpion](https://github.com/OGscorpion)
 */
#define _USE_MATH_DEFINES
#include <cassert>   /// for assert
#include <cmath>     /// for M_PI definition and pow()
#include <cstdint>   /// for uint16_t datatype
#include <iostream>  /// for IO operations

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief perimeter of a [square](https://en.wikipedia.org/wiki/Square) (4 * l)
 * @param length is the length of the square
 * @returns perimeter of square
 */
template <typename T>
T square_perimeter(T length) {
    return 4 * length;
}

/**
 * @brief perimeter of a [rectangle](https://en.wikipedia.org/wiki/Rectangle) ( 2*(l + w) )
 * @param length is the length of the rectangle
 * @param width is the width of the rectangle
 * @returns perimeter of the rectangle
 */
template <typename T>
T rect_perimeter(T length, T width) {
    return 2 * (length + width);
}

/**
 * @brief perimeter of a [triangle](https://en.wikipedia.org/wiki/Triangle) (a + b + c)
 * @param side1 is one side of the triangle
 * @param side2 is the second side of the triangle
 * @param side3 is the third side of the triangle
 * @returns perimeter of the triangle
 */
template <typename T>
T triangle_perimeter(T side1, T side2, T side3) {
    return side1 + side2 + side3;
}

/**
 * @brief perimeter of a
 * [circle](https://en.wikipedia.org/wiki/perimeter_of_a_circle) (2 * pi * r)
 * @param radius is the radius of the circle
 * @returns perimeter of the circle
 */
template <typename T>
T circle_perimeter(T radius) {
    return 2 * M_PI * radius;
}

/**
 * @brief perimeter of a
 * [parallelogram](https://en.wikipedia.org/wiki/Parallelogram) 2(s1 + s2)
 * @param side1 is the base side of the parallelogram
 * @param side2 is the other side of the parallelogram
 * @returns perimeter of the parallelogram
 */
template <typename T>
T parallelogram_perimeter(T side1, T side2) {
    return 2 * (side1 + side2);
}

/**
 * @brief perimeter of an
 * [n-sided_regular_polygon](https://www.cuemath.com/measurement/perimeter-of-polygon/) (n * l)
 * @param sides is the number of sides of the polygon
 * @param length is the length of each side
 * @returns perimeter of the regular polygon
 */
template <typename T>
T n_sides_regular_polygon_perimeter(T sides, T length) {
    return sides * length;
}

}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::cout << "Running Tests..." << std::endl;
    
    // Test square perimeter
    assert(math::square_perimeter(5) == 20);
    assert(math::square_perimeter(2.5f) == 10.0f);

    // Test rectangle perimeter
    assert(math::rect_perimeter(4, 7) == 22);
    assert(std::abs(math::rect_perimeter(2.5, 5.7) - 16.4) < 1e-4);

    // Test triangle perimeter
    assert(math::triangle_perimeter(10, 3, 5) == 18);

    // Test circle perimeter
    assert(std::abs(math::circle_perimeter(6.0) - 37.6991) < 1e-4);

    // Test parallelogram perimeter
    assert(math::parallelogram_perimeter(6, 7) == 26);

    // Test N-sides regular polygon perimeter
    assert(math::n_sides_regular_polygon_perimeter(7, 10) == 70);

    std::cout << "All Tests Passed!" << std::endl;
}

/**
 * @brief Main function to run the test cases
 * @returns 0 on successful execution
 */
int main() {
    test();  // Run the test cases
    return 0;
}
