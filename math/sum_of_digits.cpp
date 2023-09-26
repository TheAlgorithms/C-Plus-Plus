/**
 * @file
 * @brief
 * A C++ Program to find the [Digit
 * Sum](https://en.wikipedia.org/wiki/Digit_sum) of any given number.
 * @details A Digit Sum is found by adding the digits of a number.
 * @author [iamnambiar](https://github.com/iamnambiar)
 * @author [Dylan Cusson](https://github.com/dylancusson)
 */
#include <cassert>   //Include for asserts
#include <iostream>  //Include for IO operations

/**
 * @brief Mathematical algorithms
 * @namespace
 */
namespace math {
/**
 * @brief Function to find the sum of the digits of an integer.
 * @param num The integer.
 * @return Sum of the digits of the integer.
 */
int sum_of_digits(int num) {
    /*
     * First the algorithm checks whether the number is negative or positive,
     * and sets the sign accordingly.
     * Performing a modulo operation % 10 gives us the value of the last digit,
     * which we add to our running sum total.
     * The number is then divided by 10 to remove the last digit.
     * This loop continues until all digits have been processed.
     */

    int sign = 1;  // Start with a positive sign

    if (num < 0) {
        sign = -1;       // If num is negative we adjust our sign
        num = -1 * num;  // and convert to positive for further use
    }
    int sum = 0;
    while (num != 0) {
        sum = sum +
              (num %
               10);  // Modulo gives us the last digit and we add it to our sum
        num = num / 10;  // Divide our number by 10 to remove the last digit
    }
    return sum * sign;  // We multiply our sum by the sign to reflect the
                        // original signed value
}
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    assert(math::sum_of_digits(123) == 6);
    assert(math::sum_of_digits(84001) == 13);
    assert(math::sum_of_digits(1000001) == 2);
    assert(math::sum_of_digits(1234567890) == 45);
    assert(math::sum_of_digits(-1234567890) == -45);
    assert(math::sum_of_digits(-1000001) == -2);
    assert(math::sum_of_digits(-84001) == -13);
    assert(math::sum_of_digits(-123) == -6);
    std::cout << "All tests passed!" << std::endl;
}

/**
 * @brief Main Function
 * @returns 0 on exit
 */
int main() {
    tests();  // Perform self-tests
    return 0;
}
