/**
 * @file
 * @brief Calculate quadratic equation with complex roots, i.e. b^2 - 4ac < 0.
 *
 * @author [Renjian-buchai](https://github.com/Renjian-buchai)
 *
 * @description Calculates any quadratic equation in form ax^2 + bx + c.
 *
 * Quadratic equation:
 * x = (-b +/- sqrt(b^2 - 4ac)) / 2a
 *
 * @example
 * int main() {
 *   using std::array;
 *   using std::complex;
 *   using std::cout;
 *
 *   array<complex<long double, 2> solutions = quadraticEquation(1, 2, 1);
 *   cout << solutions[0] << " " << solutions[1] << "\n";
 *
 *   solutions = quadraticEquation(1, 1, 1);  // Reusing solutions.
 *   cout << solutions[0] << " " << solutions[1] << "\n";
 *   return 0;
 * }
 *
 * Output:
 * (-1, 0) (-1, 0)
 * (-0.5,0.866025) (-0.5,0.866025)
 */

#include <array>      /// std::array
#include <cassert>    /// assert
#include <cmath>      /// std::sqrt, std::trunc, std::pow
#include <complex>    /// std::complex
#include <exception>  /// std::invalid_argument
#include <iomanip>    /// std::setprecision
#include <iostream>   /// std::cout

/**
 * @namespace
 * @brief Mathematical algorithms
 */
namespace math {

/**
 * @brief Quadratic equation calculator.
 * @param a quadratic coefficient.
 * @param b linear coefficient.
 * @param c constant
 * @return Array containing the roots of quadratic equation, incl. complex
 * root.
 */
std::array<std::complex<long double>, 2> quadraticEquation(long double a,
                                                           long double b,
                                                           long double c) {
    if (a == 0) {
        throw std::invalid_argument("quadratic coefficient cannot be 0");
    }

    long double discriminant = b * b - 4 * a * c;
    std::array<std::complex<long double>, 2> solutions{0, 0};

    if (discriminant == 0) {
        solutions[0] = -b * 0.5 / a;
        solutions[1] = -b * 0.5 / a;
        return solutions;
    }
    
    // Complex root (discriminant < 0)
    // Note that the left term (-b / 2a) is always real. The imaginary part
    // appears when b^2 - 4ac < 0, so sqrt(b^2 - 4ac) has no real roots. So,
    // the imaginary component is i * (+/-)sqrt(abs(b^2 - 4ac)) / 2a.
    if (discriminant > 0) {
        // Since discriminant > 0, there are only real roots. Therefore,
        // imaginary component = 0.
        solutions[0] = std::complex<long double>{
            (-b - std::sqrt(discriminant)) * 0.5 / a, 0};
        solutions[1] = std::complex<long double>{
            (-b + std::sqrt(discriminant)) * 0.5 / a, 0};
        return solutions;
    }
    // Since b^2 - 4ac is < 0, for faster computation, -discriminant is
    // enough to make it positive.
    solutions[0] = std::complex<long double>{
        -b * 0.5 / a, -std::sqrt(-discriminant) * 0.5 / a};
    solutions[1] = std::complex<long double>{
        -b * 0.5 / a, std::sqrt(-discriminant) * 0.5 / a};

    return solutions;
}

}  // namespace math

/**
 * @brief Asserts an array of complex numbers.
 * @param input Input array of complex numbers. .
 * @param expected Expected array of complex numbers.
 * @param precision Precision to be asserted. Default=10
 */
void assertArray(std::array<std::complex<long double>, 2> input,
                 std::array<std::complex<long double>, 2> expected,
                 size_t precision = 10) {
    long double exponent = std::pow(10, precision);
    input[0].real(std::round(input[0].real() * exponent));
    input[1].real(std::round(input[1].real() * exponent));
    input[0].imag(std::round(input[0].imag() * exponent));
    input[1].imag(std::round(input[1].imag() * exponent));

    expected[0].real(std::round(expected[0].real() * exponent));
    expected[1].real(std::round(expected[1].real() * exponent));
    expected[0].imag(std::round(expected[0].imag() * exponent));
    expected[1].imag(std::round(expected[1].imag() * exponent));

    assert(input == expected);
}

/**
 * @brief Self-test implementations to test quadraticEquation function.
 * @note There are 4 different types of solutions: Real and equal, real,
 * complex, complex and equal.
 */
static void test() {
    // Values are equal and real.
    std::cout << "Input: \n"
                 "a=1 \n"
                 "b=-2 \n"
                 "c=1 \n"
                 "Expected output: \n"
                 "(1, 0), (1, 0)\n\n";
    std::array<std::complex<long double>, 2> equalCase{
        std::complex<long double>{1, 0}, std::complex<long double>{1, 0}};
    assert(math::quadraticEquation(1, -2, 1) == equalCase);

    // Values are equal and complex.
    std::cout << "Input: \n"
                 "a=1 \n"
                 "b=4 \n"
                 "c=5 \n"
                 "Expected output: \n"
                 "(-2, -1), (-2, 1)\n\n";
    std::array<std::complex<long double>, 2> complexCase{
        std::complex<long double>{-2, -1}, std::complex<long double>{-2, 1}};
    assert(math::quadraticEquation(1, 4, 5) == complexCase);

    // Values are real.
    std::cout << "Input: \n"
                 "a=1 \n"
                 "b=5 \n"
                 "c=1 \n"
                 "Expected output: \n"
                 "(-4.7912878475, 0), (-0.2087121525, 0)\n\n";
    std::array<std::complex<long double>, 2> floatCase{
        std::complex<long double>{-4.7912878475, 0},
        std::complex<long double>{-0.2087121525, 0}};
    assertArray(math::quadraticEquation(1, 5, 1), floatCase);

    // Values are complex.
    std::cout << "Input: \n"
                 "a=1 \n"
                 "b=1 \n"
                 "c=1 \n"
                 "Expected output: \n"
                 "(-0.5, -0.8660254038), (-0.5, 0.8660254038)\n\n";
    std::array<std::complex<long double>, 2> ifloatCase{
        std::complex<long double>{-0.5, -0.8660254038},
        std::complex<long double>{-0.5, 0.8660254038}};
    assertArray(math::quadraticEquation(1, 1, 1), ifloatCase);

    std::cout << "Exception test: \n"
                 "Input: \n"
                 "a=0 \n"
                 "b=0 \n"
                 "c=0\n"
                 "Expected output: Exception thrown \n";
    try {
        math::quadraticEquation(0, 0, 0);
    } catch (std::invalid_argument& e) {
        std::cout << "Exception thrown successfully \n";
    }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // Run self-test implementation.
    return 0;
}
