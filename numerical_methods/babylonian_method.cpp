/**
 * @file
 * @brief [A babylonian method
 * (BM)](https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Babylonian_method)
 * is an algorithm that computes the square root.
 * @details
 * This algorithm has an application in use case scenario where a user wants
 * find accurate square roots of large numbers
 * @author [Ameya Chawla](https://github.com/ameyachawlaggsipu)
 */

#include <cassert>  /// for assert
#include <cmath>
#include <iostream>  /// for IO operations

/**
 * @namespace numerical_methods
 * @brief Numerical algorithms/methods
 */

namespace numerical_methods {

/**
 * @brief Babylonian methods is an iterative function which returns
 * square root of radicand
 * @param radicand is the radicand
 * @returns x1 the square root of radicand
 */

double babylonian_method(double radicand) {
    int i = 1;  /// To find initial root or rough approximation

    while (i * i <= radicand) {
        i++;
    }

    i--;  /// Real Initial value will be i-1 as loop stops on +1 value

    double x0 = i;  /// Storing previous value for comparison
    double x1 =
        (radicand / x0 + x0) / 2;  /// Storing calculated value for comparison
    double temp = NAN;             /// Temp variable to x0 and x1

    while (std::max(x0, x1) - std::min(x0, x1) < 0.0001) {
        temp = (radicand / x1 + x1) / 2;  /// Newly calculated root
        x0 = x1;
        x1 = temp;
    }

    return x1;  /// Returning final root
}

}  // namespace numerical_methods

/**
 * @brief Self-test implementations
 * @details
 * Declaring two test cases and checking for the error
 * in predicted and true value is less than 0.0001.
 * @returns void
 */
static void test() {
    /* descriptions of the following test */

    auto testcase1 = 125348;  /// Testcase 1
    auto testcase2 = 752080;  /// Testcase 2

    auto real_output1 = 354.045194855;  /// Real Output 1
    auto real_output2 = 867.225460881;  /// Real Output 2

    auto test_result1 = numerical_methods::babylonian_method(testcase1);
    /// Test result for testcase 1
    auto test_result2 = numerical_methods::babylonian_method(testcase2);
    /// Test result for testcase 2

    assert(std::max(test_result1, real_output1) -
               std::min(test_result1, real_output1) <
           0.0001);
    /// Testing for test Case 1
    assert(std::max(test_result2, real_output2) -
               std::min(test_result2, real_output2) <
           0.0001);
    /// Testing for test Case 2

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * calls automated test function to test the working of fast fourier transform.
 * @returns 0 on exit
 */

int main(int argc, char const *argv[]) {
    test();  //  run self-test implementations
             //  with 2 defined test cases
    return 0;
}
