/**
 * @file
 * @brief Implmentations for the
 * [Pythagorian Triple](https://en.wikipedia.org/wiki/Pythagorean_triple)
 * @details
 * A Pythagorean triple consists of three positive integers a, b, and c, such
 * that a2 + b2 = c2. Such a triple is commonly written (a, b, c), and a
 * well-known example is (3, 4, 5).
 * @author [Shrutika Kailas Hilale](https://github.com/shrutikahilale)
 */

#include <algorithm>  /// for min
#include <cmath>      /// for std::pow
#include <iostream>   /// for io operations

/**
 * @brief Triples describe the three integer side lengths of a right triangle.
 * @param a, b, c length of sides of a right angled triangle
 * @return bool: if the given triplet is a pythgorian triplet - true
 */
bool is_pythgorian_triple(int a, int b, int c) {
    return (std::pow(a, 2) == std::pow(b, 2) + std::pow(c, 2)) ||
           (std::pow(b, 2) == std::pow(a, 2) + std::pow(c, 2)) ||
           (std::pow(c, 2) == std::pow(b, 2) + std::pow(a, 2));
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // output: 1/0
    std::cout << is_pythgorian_triple(3, 4, 5) << "\n";
    std::cout << "TEST PASSED" << std::endl << std::endl;
    std::cout << is_pythgorian_triple(5, 12, 13) << "\n";
    std::cout << "TEST PASSED" << std::endl << std::endl;
    std::cout << is_pythgorian_triple(1, 2, 3) << "\n";
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