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
 */

#include <iostream>  /// for std::cout

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief Function to test above algorithm
 * @param n description
 * @returns void
 */
void power_of_two(int n) {
    /**
     * This function finds whether a number is power of 2 or not
     * @param n value for which we want to check
     * prints the result, as "Yes, the number n is a power of 2" or
     * "No, the number is not a power of 2" without quotes
     */
    /// result stores the
    /// bitwise and of n and n-1
    int result = n & (n - 1);
    if (result == 0) {
        std::cout << "Yes, the number " << n << " is a power of 2";
    } else {
        std::cout << "No, the number " << n << " is not a power of 2";
    }
}
}  // namespace math

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    int n = 0;
    /// n stores the input from the user
    std::cout << "enter a number " << std::endl;
    std::cin >> n;
    /// function call with @param n
    math::power_of_two(n);
    return 0;
}
