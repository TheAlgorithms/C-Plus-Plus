/**
 * @file
 * @brief Conversion from [Kelvin to
 * Celsius](https://byjus.com/chemistry/kelvin-to-celsius/) degrees.
 * @details
 * The algorithm consists on converting a Kelvin degree value to a Celsius
 * value.
 * The formula to convert a Kelvin to a Celsius value is:
 * @f[ C = K - 273.15 @f] where:
 * - C is the Celsius temperature
 * - K is the Kelvin temperature
 *
 * Check out [Kelvin](https://en.wikipedia.org/wiki/Kelvin) and
 * [Celsius](https://en.wikipedia.org/wiki/Celsius) on Wikipedia for more
 * information about their story, how do they work, when and why they should be
 * used, etc..
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <cassert>   /// for assert
#include <cmath>     /// for std::abs
#include <iostream>  /// for IO operations

/**
 * @namespace
 * @brief Other algorithms
 */
namespace others {
/**
 * @brief Compare two floating point numbers with a certain tolerance.
 * This is needed as with some values, the result (e.g.: -196.15) might be a bit
 * lower (in this case, -196.499999...).
 * @param a the first number to compare
 * @param b the second number to compare
 * @param tolerance the tolerance to use when comparing the numbers
 * @returns true if the numbers ARE equal within the given tolerance
 * @returns false if the numbers are NOT equal within the given tolerance
 * otherwise
 */
bool are_almost_equal(double a, double b, double absolute_tolerance = 0.0001) {
    return std::abs(a - b) < absolute_tolerance;
}

/**
 * @brief Conversion from Kelvin to Celsius algorithm.
 * @param number the Celsius number that will be used to convert
 * @returns the Kelvin number converted to Celsius
 */
double kelvin_to_celsius(double temperature_in_k) {
    const double absolute_zero_in_c = -273.15;
    if (temperature_in_k < absolute_zero_in_c) {
        throw std::invalid_argument("input temperature below absolute zero");
    }
    return temperature_in_k + absolute_zero_in_c;
}
}  // namespace others

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    assert(others::are_almost_equal(others::kelvin_to_celsius(230), -43.15));
    assert(others::are_almost_equal(others::kelvin_to_celsius(512), 238.85));
    assert(others::are_almost_equal(others::kelvin_to_celsius(55), -218.15));
    assert(others::are_almost_equal(others::kelvin_to_celsius(77), -196.15));
    assert(others::are_almost_equal(others::kelvin_to_celsius(9.78), -263.37));
    assert(others::are_almost_equal(others::kelvin_to_celsius(15), -258.15));
    assert(others::are_almost_equal(others::kelvin_to_celsius(273.15), 0));

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
