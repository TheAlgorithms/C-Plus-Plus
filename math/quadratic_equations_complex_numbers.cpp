/**
 * @file
 * @brief Calculate quadratic equation with complex roots, i.e. b^2 - 4ac < 0.
 * @see https://en.wikipedia.org/wiki/Quadratic_equation,
 * https://en.wikipedia.org/wiki/Quadratic_equation#discriminant
 *
 * @author [Renjian-buchai](https://github.com/Renjian-buchai)
 */

#include <array>
#include <cassert>
#include <cmath>
#include <complex>
#include <exception>
#include <iomanip>
#include <iostream>

/// @brief Quadratic equation calculator.
/// @param a quadratic coefficient.
/// @param b linear coefficient.
/// @param c constant
/// @return Array containing the roots of quadratic equation, incl. complex
/// root.
std::array<std::complex<long double>, 2> quadraticEquation(long double a,
                                                           long double b,
                                                           long double c) {
    /**
     * Calculates any quadratic equation in form ax^2 + bx + c.
     *
     * Quadratic equation:
     * x = (-b +/- sqrt(b^2 - 4ac)) / 2a
     *
     * e.g.
     * using namespace std;
     * int main() {
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

    if (a == 0)
        throw std::invalid_argument("quadratic coefficient cannot be 0");

    long double discriminant = b * b - 4 * a * c;
    std::array<std::complex<long double>, 2> solutions{0, 0};

    /// Complex root (discriminant < 0)
    /// Note that the left term (-b / 2a) is always real. The imaginary part
    /// appears when b^2 - 4ac < 0, so sqrt(b^2 - 4ac) has no real roots. So,
    /// the imaginary component is i * (+/-)sqrt(abs(b^2 - 4ac)) / 2a.
    if (discriminant < 0) {
        /// Since b^2 - 4ac is < 0, for faster computation, -discriminant is
        /// enough to make it positive.
        solutions[0] = std::complex<long double>{
            -b * 0.5 / a, -std::sqrt(-discriminant) * 0.5 / a};
        solutions[1] = std::complex<long double>{
            -b * 0.5 / a, std::sqrt(-discriminant) * 0.5 / a};
    } else {
        /// Since discriminant > 0, there are only real roots. Therefore,
        /// imaginary component = 0.
        solutions[0] = std::complex<long double>{
            (-b - std::sqrt(discriminant)) * 0.5 / a, 0};
        solutions[1] = std::complex<long double>{
            (-b + std::sqrt(discriminant)) * 0.5 / a, 0};
    }

    return solutions;
}

int main() {
    std::array<std::complex<long double>, 2> aaa = quadraticEquation(1, 1, 1);
    std::cout << "The complex roots of x^2 + x + 1 are " << aaa[0] << " and "
              << aaa[1]
              << ".\nMore precisely, and with the inaccuracy of floating point "
                 "numbers, "
              << std::setprecision(100) << aaa[0] << " and " << aaa[1] << "\n";

    return 0;
}
