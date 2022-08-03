/**
 * @author [jasonchee816](https://github.com/jasonchee816)
 * @file
 *
 * @brief [Program to count iterations needed to reach Kaprekar's Constant, 6174
 * via Kaprekar's Routine](https://en.wikipedia.org/wiki/Kaprekar%27s_routine)
 */

#include <algorithm>
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <string>    /// for string

/**
 * @brief The main function that checks
 * the number of digits in a number.
 * @param n the number to check its digits
 * @returns the digits count
 */
int find_number_of_iteration_to_kaprekar_constant(int n) {
    int iterate_count = 0;  //< the variable used for the iteration counts

    /// Convert negative value to positive
    if (n < 0) {
        n = -1 * n;
    }

    /// Kaprekar only works on 4 digits value (allows leading 0s)
    if (n > 9999) {
        return -1;
    }

    /// The number needs to has at least 2 distinct value
    if (n / 1111 == 0) {
        return -1;
    }

    /// iterate until `n` becomes 6174
    while (n != 6174) {
        std::string str = std::to_string(n);

        while (str.length() < 4) {
            str.insert(0, "0");
        }

        /// get largest and smallest combination
        std::sort(str.begin(), str.end());
        int smallest = std::stoi(str);
        std::sort(str.begin(), str.end(), std::greater<char>());
        int largest = std::stoi(str);

        n = (largest - smallest);
        /// each time the loop is running, `count` will be incremented by 1.
        ++iterate_count;
    }

    return iterate_count;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    assert(find_number_of_iteration_to_kaprekar_constant(9981) == 3);
    assert(find_number_of_iteration_to_kaprekar_constant(3524) == 3);
    assert(find_number_of_iteration_to_kaprekar_constant(10000) == -1);
    assert(find_number_of_iteration_to_kaprekar_constant(9998) == 5);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  /// run self-test
    return 0;
}