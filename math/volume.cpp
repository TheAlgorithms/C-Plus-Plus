/**
 * @file
 * @brief Implmentations for the [volume](https://en.wikipedia.org/wiki/Volume)
 * of various 3D shapes.
 * @details The volume of a 3D shape is the amount of 3D space that the shape
 * takes up. All shapes have a formula to get the volume of any given shape.
 * These implementations support multiple return types.
 *
 * @author [Focusucof](https://github.com/Focusucof)
 */

#include <cassert>   /// for assert
#include <cmath>     /// for std::pow
#include <cstdint>   /// for std::uint32_t
#include <iostream>  /// for IO operations

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief The volume of a [cube](https://en.wikipedia.org/wiki/Cube)
 * @param length The length of the cube
 * @returns The volume of the cube
 */
template <typename T>
T cube_volume(T length) {
    return std::pow(length, 3);
}

/**
 * @brief The volume of a
 * [rectangular](https://en.wikipedia.org/wiki/Cuboid) prism
 * @param length The length of the base rectangle
 * @param width The width of the base rectangle
 * @param height The height of the rectangular prism
 * @returns The volume of the rectangular prism
 */
template <typename T>
T rect_prism_volume(T length, T width, T height) {
    return length * width * height;
}

/**
 * @brief The volume of a [cone](https://en.wikipedia.org/wiki/Cone)
 * @param radius The radius of the base circle
 * @param height The height of the cone
 * @param PI The definition of the constant PI
 * @returns The volume of the cone
 */
template <typename T>
T cone_volume(T radius, T height, double PI = 3.14) {
    return std::pow(radius, 2) * PI * height / 3;
}

/**
 * @brief The volume of a
 * [triangular](https://en.wikipedia.org/wiki/Triangular_prism) prism
 * @param base The length of the base triangle
 * @param height The height of the base triangles
 * @param depth The depth of the triangular prism (the height of the whole
 * prism)
 * @returns The volume of the triangular prism
 */
template <typename T>
T triangle_prism_volume(T base, T height, T depth) {
    return base * height * depth / 2;
}

/**
 * @brief The volume of a
 * [pyramid](https://en.wikipedia.org/wiki/Pyramid_(geometry))
 * @param length The length of the base shape (or base for triangles)
 * @param width The width of the base shape (or height for triangles)
 * @param height The height of the pyramid
 * @returns The volume of the pyramid
 */
template <typename T>
T pyramid_volume(T length, T width, T height) {
    return length * width * height / 3;
}

/**
 * @brief The volume of a [sphere](https://en.wikipedia.org/wiki/Sphere)
 * @param radius The radius of the sphere
 * @param PI The definition of the constant PI
 * @returns The volume of the sphere
 */
template <typename T>
T sphere_volume(T radius, double PI = 3.14) {
    return PI * std::pow(radius, 3) * 4 / 3;
}

/**
 * @brief The volume of a [cylinder](https://en.wikipedia.org/wiki/Cylinder)
 * @param radius The radius of the base circle
 * @param height The height of the cylinder
 * @param PI The definition of the constant PI
 * @returns The volume of the cylinder
 */
template <typename T>
T cylinder_volume(T radius, T height, double PI = 3.14) {
    return PI * std::pow(radius, 2) * height;
}
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // Input variables
    uint32_t int_length = 0; // 32 bit integer length input
    uint32_t int_width = 0;  // 32 bit integer width input
    uint32_t int_base = 0;   // 32 bit integer base input
    uint32_t int_height = 0; // 32 bit integer height input
    uint32_t int_depth = 0;  // 32 bit integer depth input

    double double_radius = NAN; // double radius input
    double double_height = NAN; // double height input

    // Output variables
    uint32_t int_expected = 0; // 32 bit integer expected output
    uint32_t int_volume = 0;   // 32 bit integer output

    double double_expected = NAN; // double expected output
    double double_volume = NAN;   // double output

    // 1st test
    int_length = 5;
    int_expected = 125;
    int_volume = math::cube_volume(int_length);

    std::cout << "VOLUME OF A CUBE" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_volume << std::endl;
    assert(int_volume == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 2nd test
    int_length = 4;
    int_width = 3;
    int_height = 5;
    int_expected = 60;
    int_volume = math::rect_prism_volume(int_length, int_width, int_height);

    std::cout << "VOLUME OF A RECTANGULAR PRISM" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Input Width: " << int_width << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_volume << std::endl;
    assert(int_volume == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 3rd test
    double_radius = 5;
    double_height = 7;
    double_expected = 183.16666666666666;  // truncated to 14 decimal places
    double_volume = math::cone_volume(double_radius, double_height);

    std::cout << "VOLUME OF A CONE" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Input Height: " << double_height << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_volume << std::endl;
    assert(double_volume == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 4th test
    int_base = 3;
    int_height = 4;
    int_depth = 5;
    int_expected = 30;
    int_volume = math::triangle_prism_volume(int_base, int_height, int_depth);

    std::cout << "VOLUME OF A TRIANGULAR PRISM" << std::endl;
    std::cout << "Input Base: " << int_base << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Input Depth: " << int_depth << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_volume << std::endl;
    assert(int_volume == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 5th test
    int_length = 10;
    int_width = 3;
    int_height = 5;
    int_expected = 50;
    int_volume = math::pyramid_volume(int_length, int_width, int_height);

    std::cout << "VOLUME OF A PYRAMID" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Input Width: " << int_width << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_volume << std::endl;
    assert(int_volume == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 6th test
    double_radius = 3;
    double_expected = 113.04;
    double_volume = math::sphere_volume(double_radius);

    std::cout << "VOLUME OF A SPHERE" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_volume << std::endl;
    assert(double_volume == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;

    // 7th test
    double_radius = 5;
    double_height = 2;
    double_expected = 157;
    double_volume = math::cylinder_volume(double_radius, double_height);

    std::cout << "VOLUME OF A CYLINDER" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Input Height: " << double_height << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_volume << std::endl;
    assert(double_volume == double_expected);
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
