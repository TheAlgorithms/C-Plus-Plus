/**
 * @file
 * @brief Implementations for the
 * [perimeter](https://en.wikipedia.org/wiki/Perimeter) of various shapes
 * @details The  of a shape is the amount of 2D space it takes up.
 * All shapes have a formula for their perimeter.
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
 * @brief perimeter of a [rectangle](https://en.wikipedia.org/wiki/Rectangle) (
 * 2(l + w) )
 * @param length is the length of the rectangle
 * @param width is the width of the rectangle
 * @returns perimeter of the rectangle
 */
template <typename T>
T rect_perimeter(T length, T width) {
    return 2 * (length + width);
}

/**
 * @brief perimeter of a [triangle](https://en.wikipedia.org/wiki/Triangle) (a +
 * b + c)
 * @param base is the length of the bottom side of the triangle
 * @param height is the length of the tallest point in the triangle
 * @returns perimeter of the triangle
 */
template <typename T>
T triangle_perimeter(T base, T height, T hypotenuse) {
    return base + height + hypotenuse;
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
 * [parallelogram](https://en.wikipedia.org/wiki/Parallelogram) 2(b + h)
 * @param base is the length of the bottom side of the parallelogram
 * @param height is the length of the tallest point in the parallelogram
 * @returns perimeter of the parallelogram
 */
template <typename T>
T parallelogram_perimeter(T base, T height) {
    return 2 * (base + height);
}

/**
 * @brief surface perimeter of a [cube](https://en.wikipedia.org/wiki/Cube) ( 12
 * * l)
 * @param length is the length of the cube
 * @returns surface perimeter of the cube
 */
template <typename T>
T cube_surface_perimeter(T length) {
    return 12 * length;
}

/**
 * @brief surface perimeter of a
 * [n-polygon](https://www.cuemath.com/measurement/perimeter-of-polygon/) ( n *
 * l)
 * @param length is the length of the polygon
 * @param sides is the number of sides of the polygon
 * @returns surface perimeter of the polygon
 */
template <typename T>
T n_polygon_surface_perimeter(T sides, T length) {
    return sides * length;
}

/**
 * @brief surface perimeter of a
 * [cylinder](https://en.wikipedia.org/wiki/Cylinder) (2 * radius + 2 * height)
 * @param radius is the radius of the cylinder
 * @param height is the height of the cylinder
 * @returns surface perimeter of the cylinder
 */
template <typename T>
T cylinder_surface_perimeter(T radius, T height) {
    return (2 * radius) + (2 * height);
}
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // I/O variables for testing
    uint16_t int_length = 0;      // 16 bit integer length input
    uint16_t int_width = 0;       // 16 bit integer width input
    uint16_t int_base = 0;        // 16 bit integer base input
    uint16_t int_height = 0;      // 16 bit integer height input
    uint16_t int_hypotenuse = 0;  // 16 bit integer hypotenuse input
    uint16_t int_sides = 0;       // 16 bit integer sides input
    uint16_t int_expected = 0;    // 16 bit integer expected output
    uint16_t int_perimeter = 0;   // 16 bit integer output

    float float_length = NAN;     // float length input
    float float_expected = NAN;   // float expected output
    float float_perimeter = NAN;  // float output

    double double_length = NAN;     // double length input
    double double_width = NAN;      // double width input
    double double_radius = NAN;     // double radius input
    double double_height = NAN;     // double height input
    double double_expected = NAN;   // double expected output
    double double_perimeter = NAN;  // double output

    // 1st test
    int_length = 5;
    int_expected = 20;
    int_perimeter = math::square_perimeter(int_length);

    std::cout << "perimeter OF A SQUARE (int)" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 2nd test
    float_length = 2.5;
    float_expected = 10;
    float_perimeter = math::square_perimeter(float_length);

    std::cout << "perimeter OF A SQUARE (float)" << std::endl;
    std::cout << "Input Length: " << float_length << std::endl;
    std::cout << "Expected Output: " << float_expected << std::endl;
    std::cout << "Output: " << float_perimeter << std::endl;
    assert(float_perimeter == float_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 3rd test
    int_length = 4;
    int_width = 7;
    int_expected = 22;
    int_perimeter = math::rect_perimeter(int_length, int_width);

    std::cout << "perimeter OF A RECTANGLE (int)" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Input Width: " << int_width << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 4th test
    double_length = 2.5;
    double_width = 5.7;
    double_expected = 16.4;
    double_perimeter = math::rect_perimeter(double_length, double_width);

    std::cout << "perimeter OF A RECTANGLE (double)" << std::endl;
    std::cout << "Input Length: " << double_length << std::endl;
    std::cout << "Input Width: " << double_width << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_perimeter << std::endl;
    assert(double_perimeter == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 5th test
    int_base = 10;
    int_height = 3;
    int_hypotenuse = 5;
    int_expected = 18;
    int_perimeter =
        math::triangle_perimeter(int_base, int_height, int_hypotenuse);

    std::cout << "perimeter OF A TRIANGLE" << std::endl;
    std::cout << "Input Base: " << int_base << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 6th test
    double_radius = 6;
    double_expected =
        37.69911184307752;  // rounded down because the double datatype
                            // truncates after 14 decimal places
    double_perimeter = math::circle_perimeter(double_radius);

    std::cout << "perimeter OF A CIRCLE" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_perimeter << std::endl;
    assert(double_perimeter == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 7th test
    int_base = 6;
    int_height = 7;
    int_expected = 26;
    int_perimeter = math::parallelogram_perimeter(int_base, int_height);

    std::cout << "perimeter OF A PARALLELOGRAM" << std::endl;
    std::cout << "Input Base: " << int_base << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 8th test
    double_length = 5.5;
    double_expected = 66.0;
    double_perimeter = math::cube_surface_perimeter(double_length);

    std::cout << "SURFACE perimeter OF A CUBE" << std::endl;
    std::cout << "Input Length: " << double_length << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_perimeter << std::endl;
    assert(double_perimeter == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 9th test
    int_sides = 7;
    int_length = 10;
    int_expected = 70;
    int_perimeter = math::n_polygon_surface_perimeter(int_sides, int_length);

    std::cout << "SURFACE perimeter OF A N-POLYGON" << std::endl;
    std::cout << "Input Sides: " << int_sides << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 10th test
    double_radius = 4.0;
    double_height = 7.0;
    double_expected = 22.0;
    double_perimeter =
        math::cylinder_surface_perimeter(double_radius, double_height);

    std::cout << "SURFACE perimeter OF A CYLINDER" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Input Height: " << double_height << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_perimeter << std::endl;
    assert(double_perimeter == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
