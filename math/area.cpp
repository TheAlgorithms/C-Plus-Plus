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
    uint64_t area_of_square = (uint64_t)length * (uint64_t)length;
    return area_of_square;
}

/**
 * @brief area of a [rectangle](https://en.wikipedia.org/wiki/Rectangle) (l * w)
 * @param length is the length of the rectangle
 * @param width is the width of the rectangle
 * @returns area of the rectangle
 */
uint64_t rect_area(uint32_t length, uint32_t width) {
    /*
        You may notice that these variables are prepended with (uint64_t)
        This is because when doing the multiplication we need to give these data
        types a wider area of memory when doing this calculation so we need a 64
       bit variable.

        We could make the parameters 64 bit but that would require adding checks
       to make sure out calculation doesn't exceed 64 bits. So this is easier.
    */
    uint64_t area_of_rectangle = (uint64_t)length * (uint64_t)width;
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
 * @param radius is the radius of the cylinder
 * @param height is the height of the cylinder
 * @returns surface area of the cylinder
 */
double cylinder_surface_area(uint16_t radius, uint16_t height) {
    double surface_area_of_cylinder =
        2 * M_PI * radius * height + 2 * M_PI * pow(radius, 2);
    return surface_area_of_cylinder;
}

}  // namespace math

/**
 * @brief This self test is used to test the basic functionality of the
 * square_area function to see if it behaves as expected.
 * @returns void
 */
static void test_square_area_functionality() {
    // Given we the lengths of different squares.
    uint32_t square_a_side_length = 20u;
    uint32_t square_b_side_length = 1024u;
    uint32_t square_c_side_length = 35233030u;
    uint32_t square_d_side_length = 0u;

    // When we calculate the area of the different squares
    uint64_t actual_area_square_a = math::square_area(square_a_side_length);
    uint64_t actual_area_square_b = math::square_area(square_b_side_length);
    uint64_t actual_area_square_c = math::square_area(square_c_side_length);
    uint64_t actual_area_square_d = math::square_area(square_d_side_length);

    // Then we should get the area calculated as we expect.
    // is the expected == actual?
    assert(400u == actual_area_square_a);
    assert(1048576u == actual_area_square_b);
    assert(1241366402980900u == actual_area_square_c);
    assert(0u == actual_area_square_d);

    std::cout << "TEST PASSED" << std::endl << std::endl;
}

/**
 * @brief This self test is used to test the basic functionality of the
 * square_area function to see if it behaves as expected.
 * @returns void
 */
static void test_square_area_functionality() {
    // Given we the lengths of different squares.
    uint32_t square_a_side_length = 0u;
    uint32_t square_b_side_length = 1024u;
    uint32_t square_c_side_length = 35233030u;

    // When we calculate the area of the different squares
    uint64_t actual_area_square_a = math::square_area(square_a_side_length);
    uint64_t actual_area_square_b = math::square_area(square_b_side_length);
    uint64_t actual_area_square_c = math::square_area(square_c_side_length);

    // Then we should get the area calculated as we expect.
    // is the expected == actual?
    assert(400u == actual_area_square_a);
    assert(1048576u == actual_area_square_b);
    assert(1241366402980900u == actual_area_square_c);

    std::cout << "TEST PASSED" << std::endl << std::endl;
}

/**
 * @brief This self test is used to test the basic functionality of the
 * rect_area function to see if it behaves as expected.
 * @returns void
 */
static void test_rectangle_area_functionality() {
    // Given we the lengths of different squares.
    uint32_t rectangle_side_length = 1024u;
    uint32_t rectangle_side_width = 35233030u;

    // When we calculate the area of the different squares
    uint64_t actual_area_rectangle =
        math::rect_area(rectangle_side_length, rectangle_side_width);
    uint64_t actual_area_square_b = math::square_area(square_b_side_length);
    uint64_t actual_area_square_c = math::square_area(square_c_side_length);

    // Then we should get the area calculated as we expect.
    // is the expected == actual?
    assert(400u == actual_area_rectangle);

    std::cout << "TEST PASSED" << std::endl << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test_square_area_functionality();  // run self-test implementations
    return 0;
}
