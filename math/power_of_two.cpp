/**
 * @file
 * @brief Implementation to check whether a number is a power of 2 or not.
 *
 * @details
 * This algorithm uses bit manipulation to check if a number is a power of 2 or
 * not.
 *
 * ### Algorithm
 * Let the input number be n, then the bitwise and between n and n-1 will let us
 * know whether the number is power of 2 or not
 *
 * For Example,
 * If N= 32 then N-1 is 31, if we perform bitwise and of these two numbers then
 * the result will be zero, which indicates that it is the power of 2
 * If N=23 then N-1 is 22, if we perform bitwise and of these two numbers then
 * the result will not be zero , which indicates that it is not the power of 2
 * \note This implementation is better than naive recursive or iterative
 * approach.
 *
 * @author [Neha Hasija](https://github.com/neha-hasija17)
 * @author [Rijul.S](https://github.com/Rijul24)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief This function finds whether a number is power of 2 or not
 * @param n value for which we want to check
 * prints the result, as "Yes, the number n is a power of 2" or
 * "No, the number is not a power of 2" without quotes
 * @returns 1 if `n` IS the power of 2
 * @returns 0 if n is NOT a power of 2
 */
int power_of_two(int n) {
    /// result stores the
    /// bitwise and of n and n-1
    int result = n & (n - 1);

    if (result == 0) {
        return 1;
    }

    return 0;
}
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::cout << "First case testing... \n";  // for n = 32 return 1
    assert(math::power_of_two(32) == 1);
    std::cout << "\nPassed!\n";

    std::cout << "Second case testing... \n";  // for n = 5 return 0
    assert(math::power_of_two(5) == 0);
    std::cout << "\nPassed!\n";

    std::cout << "Third case testing... \n";  // for n = 232 return 0
    assert(math::power_of_two(232) == 0);
    std::cout << "\nPassed!\n";

    std::cout << "\nAll test cases have successfully passed!\n";
}

/**
 * @brief Take user input in the test cases (optional; currently commented)
 * @returns void
 */
void user_input_test() {
    int n = 0;  // input from user

    std::cout << "Enter a number " << std::endl;
    std::cin >> n;

    /// function call with @param n
    int result = math::power_of_two(n);
    if (result == 1) {
        std::cout << "Yes, the number " << n << " is a power of 2\n";
    } else {
        std::cout << "No, the number " << n << " is not a power of 2\n";
    }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations

    // uncomment the line below to take user inputs
    // user_input_test();

    return 0;
}
