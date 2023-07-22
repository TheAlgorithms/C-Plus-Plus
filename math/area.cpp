/**
 * @file
 * @brief Basic function implementations for working out the
 * [area](https://en.wikipedia.org/wiki/Area) of various shapes.
 *
 * @details
 * The area of a shape is the amount of 2D space it takes up.
 * All shapes have a formula to get the area of any given shape.
 * These implementations support multiple return types.
 *
 * @author [Focusucof](https://github.com/Focusucof)
 */

#define _USE_MATH_DEFINES  /// This definition is required to use M_PI.

#include <cassert>   /// for assert
#include <cmath>     /// for M_PI definition and pow()
#include <cstdint>   /// for uint16_t datatype
#include <iostream>  /// for IO operations

/**
 * @brief Mathematical algorithms
 * @namespace math
 */
namespace math {

/**
 * @brief area of a [square](https://en.wikipedia.org/wiki/Square) (l * l)
 * @param length is the length of the square
 * @returns area of square.
 */
uint64_t square_area(uint32_t length) {
    /*
       The parameter type of this function replaces the template type T because
       it is safer. If we use the same parameter type as the return type then
       there is a potential for the calculated value to roll over and give an
       incorrect calculation.

       e.g. (UINT8_T_MAX * UINT8_T_MAX) == 65025
       To store this calculation we would need to specify a return type of
       uint16_t

       This is important to know for the following functions because it dictates
       what data type we decide upon when setting up the function parameters and
       the value returned by the function.
    */
    uint64_t area_of_square = length * length;
    return area_of_square;
}

/**
 * @brief area of a [rectangle](https://en.wikipedia.org/wiki/Rectangle) (l * w)
 * @param length is the length of the rectangle
 * @param width is the width of the rectangle
 * @returns area of the rectangle
 */
uint64_t rect_area(uint32_t length, uint32_t width) {
    uint64_t area_of_rectangle = length * width;
    return area_of_rectangle;
}

/**
 * @brief area of a [triangle](https://en.wikipedia.org/wiki/Triangle) (b * h)/2
 * @param base is the length of the bottom side of the triangle
 * @param height is the length of the tallest point in the triangle
 * @returns area of the triangle
 */
template <typename T>
double triangle_area(uint32_t base, uint32_t height) {
    uint64_t area_of_triangle = (base * height) / 2;
    return area_of_triangle;
}

/**
 * @brief area of a [circle](https://en.wikipedia.org/wiki/Area_of_a_circle)
 * (pi * r^2)
 * @param radius is the radius of the circle
 * @returns area of the circle
 */
double circle_area(uint32_t radius) {
    double area_of_circle = M_PI * pow(radius, 2);
    return area_of_circle;
}

/**
 * @brief area of a [parallelogram](https://en.wikipedia.org/wiki/Parallelogram)
 * (b * h)
 * @param base is the length of the bottom side of the parallelogram
 * @param height is the length of the tallest point in the parallelogram
 * @returns area of the parallelogram
 */
uint64_t parallelogram_area(uint32_t base, uint32_t height) {
    uint64_t area_of_parallelogram = base * height;
    return area_of_parallelogram;
}

/**
 * @brief surface area of a [cube](https://en.wikipedia.org/wiki/Cube)
 * ( 6 * (l * l))
 * @param length is the length of the cube
 * @returns surface area of the cube
 */
uint64_t cube_surface_area(uint16_t length) {
    uint64_t surface_area_of_cube = 6 * length * length;
    return surface_area_of_cube;
}

/**
 * @brief surface area of a [sphere](https://en.wikipedia.org/wiki/Sphere) ( 4 *
 * pi * r^2)
 * @param radius is the radius of the sphere
 * @returns surface area of the sphere
 */
double sphere_surface_area(uint16_t radius) {
    double surface_area_of_sphere = 4 * M_PI * pow(radius, 2);
    return surface_area_of_sphere;
}

/**
 * @brief surface area of a [cylinder](https://en.wikipedia.org/wiki/Cylinder)
 * (2 * pi * r * h + 2 * pi * r^2)
 * @tparam T the type of the input parameters and return value (e.g., `int`,
 * `float`, etc.)
 * @param radius is the radius of the cylinder
 * @param height is the height of the cylinder
 * @returns surface area of the cylinder
 */
template <typename T>
T cylinder_surface_area(T radius, T height) {
    return 2 * M_PI * radius * height + 2 * M_PI * pow(radius, 2);
}
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // I/O variables for testing
    uint16_t int_length = 0;    // 16 bit integer length input
    uint16_t int_width = 0;     // 16 bit integer width input
    uint16_t int_base = 0;      // 16 bit integer base input
    uint16_t int_height = 0;    // 16 bit integer height input
    uint16_t int_expected = 0;  // 16 bit integer expected output
    uint16_t int_area = 0;      // 16 bit integer output

    float float_length = NAN;    // float length input
    float float_expected = NAN;  // float expected output
    float float_area = NAN;      // float output

    double double_length = NAN;    // double length input
    double double_width = NAN;     // double width input
    double double_radius = NAN;    // double radius input
    double double_height = NAN;    // double height input
    double double_expected = NAN;  // double expected output
    double double_area = NAN;      // double output

    // 1st test
    int_length = 5;
    int_expected = 25;
    int_area = math::square_area(int_length);

    std::cout << "AREA OF A SQUARE (int)" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_area << std::endl;
    assert(int_area == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 2nd test
    float_length = 2.5;
    float_expected = 6.25;
    float_area = math::square_area(float_length);

    std::cout << "AREA OF A SQUARE (float)" << std::endl;
    std::cout << "Input Length: " << float_length << std::endl;
    std::cout << "Expected Output: " << float_expected << std::endl;
    std::cout << "Output: " << float_area << std::endl;
    assert(float_area == float_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 3rd test
    int_length = 4;
    int_width = 7;
    int_expected = 28;
    int_area = math::rect_area(int_length, int_width);

    std::cout << "AREA OF A RECTANGLE (int)" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Input Width: " << int_width << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_area << std::endl;
    assert(int_area == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 4th test
    double_length = 2.5;
    double_width = 5.7;
    double_expected = 14.25;
    double_area = math::rect_area(double_length, double_width);

    std::cout << "AREA OF A RECTANGLE (double)" << std::endl;
    std::cout << "Input Length: " << double_length << std::endl;
    std::cout << "Input Width: " << double_width << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_area << std::endl;
    assert(double_area == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 5th test
    int_base = 10;
    int_height = 3;
    int_expected = 15;
    int_area = math::triangle_area(int_base, int_height);

    std::cout << "AREA OF A TRIANGLE" << std::endl;
    std::cout << "Input Base: " << int_base << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_area << std::endl;
    assert(int_area == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 6th test
    double_radius = 6;
    double_expected =
        113.09733552923255;  // rounded down because the double datatype
                             // truncates after 14 decimal places
    double_area = math::circle_area(double_radius);

    std::cout << "AREA OF A CIRCLE" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_area << std::endl;
    assert(double_area == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 7th test
    int_base = 6;
    int_height = 7;
    int_expected = 42;
    int_area = math::parallelogram_area(int_base, int_height);

    std::cout << "AREA OF A PARALLELOGRAM" << std::endl;
    std::cout << "Input Base: " << int_base << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_area << std::endl;
    assert(int_area == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 8th test
    double_length = 5.5;
    double_expected = 181.5;
    double_area = math::cube_surface_area(double_length);

    std::cout << "SURFACE AREA OF A CUBE" << std::endl;
    std::cout << "Input Length: " << double_length << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_area << std::endl;
    assert(double_area == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 9th test
    double_radius = 10.0;
    double_expected = 1256.6370614359172;  // rounded down because the whole
                                           // value gets truncated
    double_area = math::sphere_surface_area(double_radius);

    std::cout << "SURFACE AREA OF A SPHERE" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_area << std::endl;
    assert(double_area == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 10th test
    double_radius = 4.0;
    double_height = 7.0;
    double_expected = 276.46015351590177;
    double_area = math::cylinder_surface_area(double_radius, double_height);

    std::cout << "SURFACE AREA OF A CYLINDER" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Input Height: " << double_height << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_area << std::endl;
    assert(double_area == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;
}

/**
 * @brief This self test is used to test the basic functionality of the
 * square_area function to see if it behaves as expected.
 * @returns void
 */
static void test_square_area_functionality() {
    // Given we the lengths of different squares.
    uint8_t square_a_side_length = 20u;
    uint16_t square_b_side_length = 1024u;
    uint32_t square_c_side_length = 35233030u;
    int8_t square_d_side_length = -15;
    int16_t square_e_side_length = -512;
    int32_t square_f_side_length = -1234567;
    float square_g_side_length = 500.1f;

    // When we calculate the area of the different squares
    uint8_t actual_area_square_a =
        math::square_area<uint8_t>(square_a_side_length);
    uint16_t actual_area_square_b =
        math::square_area<uint16_t>(square_b_side_length);
    uint32_t actual_area_square_c =
        math::square_area<uint32_t>(square_c_side_length);
    int8_t actual_area_square_d =
        math::square_area<int8_t>(square_d_side_length);
    int16_t actual_area_square_e =
        math::square_area<int16_t>(square_e_side_length);
    int32_t actual_area_square_f =
        math::square_area<int32_t>(square_f_side_length);
    float actual_area_square_g = math::square_area<float>(square_g_side_length);

    // Then we should get the area calculated as we expect.
    // is the expected == actual?
    assert(400u == actual_area_square_a);
    assert(400u == actual_area_square_b);
    assert(400u == actual_area_square_c);
    assert(400u == actual_area_square_d);
    assert(400u == actual_area_square_e);
    assert(400u == actual_area_square_f);
    assert(400u == actual_area_square_g);

    std::cout << "TEST PASSED" << std::endl << std::endl;

    // NOTE TO SELF: I started adding test for the square area. The use of the T
    // template is a really cool feature. I don't think it is useful here as I
    // have found out, calculating a uint16_t with a large area results a number
    // which is larger than the given type so in this case we would need to
    // possibly have integer types and float types. with specified data types
    // for the parameters.
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
