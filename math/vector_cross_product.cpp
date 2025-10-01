/**
 * @file
 *
 * @brief Calculates the [Cross
 *Product](https://en.wikipedia.org/wiki/Cross_product) and the magnitude of two
 *mathematical 3D vectors.
 *
 *
 * @details Cross Product of two vectors gives a vector.
 * Direction Ratios of a vector are the numeric parts of the given vector. They
 *are the tree parts of the vector which determine the magnitude (value) of the
 *vector. The method of finding a cross product is the same as finding the
 *determinant of an order 3 matrix consisting of the first row with unit vectors
 *of magnitude 1, the second row with the direction ratios of the first vector
 *and the third row with the direction ratios of the second vector. The
 *magnitude of a vector is it's value expressed as a number. Let the direction
 *ratios of the first vector, P be: a, b, c Let the direction ratios of the
 *second vector, Q be: x, y, z Therefore the calculation for the cross product
 *can be arranged as:
 *
 * ```
 * P x Q:
 *  	1	1	1
 *  	a	b	c
 *  	x	y	z
 * ```
 *
 * The direction ratios (DR) are calculated as follows:
 *  	1st DR, J:  (b * z) - (c * y)
 *  	2nd DR, A: -((a * z) - (c * x))
 *  	3rd DR, N:  (a * y) - (b * x)
 *
 * Therefore, the direction ratios of the cross product are: J, A, N
 * The following C++ Program calculates the direction ratios of the cross
 *products of two vector. The program uses a function, cross() for doing so. The
 *direction ratios for the first and the second vector has to be passed one by
 *one seperated by a space character.
 *
 * Magnitude of a vector is the square root of the sum of the squares of the
 *direction ratios.
 *
 * ### Example:
 * An example of a running instance of the executable program:
 *
 * 	Pass the first Vector: 1 2 3
 *	Pass the second Vector: 4 5 6
 *	The cross product is: -3 6 -3
 *	Magnitude: 7.34847
 *
 * @author [Shreyas Sable](https://github.com/Shreyas-OwO)
 */

#include <array>
#include <cassert>
#include <cmath>

/**
 * @namespace math
 * @brief Math algorithms
 */
namespace math {
/**
 * @namespace vector_cross
 * @brief Functions for Vector Cross Product algorithms
 */
namespace vector_cross {
/**
 * @brief Function to calculate the cross product of the passed arrays
 * containing the direction ratios of the two mathematical vectors.
 * @param A contains the direction ratios of the first mathematical vector.
 * @param B contains the direction ration of the second mathematical vector.
 * @returns the direction ratios of the cross product.
 */
std::array<double, 3> cross(const std::array<double, 3> &A,
                            const std::array<double, 3> &B) {
    std::array<double, 3> product;
    /// Performs the cross product as shown in @algorithm.
    product[0] = (A[1] * B[2]) - (A[2] * B[1]);
    product[1] = -((A[0] * B[2]) - (A[2] * B[0]));
    product[2] = (A[0] * B[1]) - (A[1] * B[0]);
    return product;
}

/**
 * @brief Calculates the magnitude of the mathematical vector from it's
 * direction ratios.
 * @param vec an array containing the direction ratios of a mathematical vector.
 * @returns type: double description: the magnitude of the mathematical vector
 * from the given direction ratios.
 */
double mag(const std::array<double, 3> &vec) {
    double magnitude =
        sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]));
    return magnitude;
}
}  // namespace vector_cross
}  // namespace math

/**
 * @brief test function.
 * @details test the cross() and the mag() functions.
 */
static void test() {
    /// Tests the cross() function.
    std::array<double, 3> t_vec =
        math::vector_cross::cross({1, 2, 3}, {4, 5, 6});
    assert(t_vec[0] == -3 && t_vec[1] == 6 && t_vec[2] == -3);

    /// Tests the mag() function.
    double t_mag = math::vector_cross::mag({6, 8, 0});
    assert(t_mag == 10);

    /// Tests A ⨯ A = 0
    std::array<double, 3> t_vec2 =
        math::vector_cross::cross({1, 2, 3}, {1, 2, 3});
    assert(t_vec2[0] == 0 && t_vec2[1] == 0 &&
           t_vec2[2] == 0);  // checking each element
    assert(math::vector_cross::mag(t_vec2) ==
           0);  // checking the magnitude is also zero
}

/**
 * @brief Main Function
 * @details Asks the user to enter the direction ratios for each of the two
 * mathematical vectors using std::cin
 * @returns 0 on exit
 */
int main() {
    /// Tests the functions with sample input before asking for user input.
    test();
    return 0;
}
