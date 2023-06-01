/**
 * @file
 * @brief A C++ Program to check whether a pair of numbers is an [amicable
 * pair](https://en.wikipedia.org/wiki/Amicable_numbers) or not.
 *
 * @details
 * An Amicable Pair is two positive integers such that the sum of the proper
 * divisor for each number is equal to the other number.
 *
 * @note Remember that a proper divisor is any positive whole number that
 * divides into a selected number, apart from the selected number itself, and
 * returns a positive integer. for example 1, 2 and  5 are all proper divisors
 * of 10.
 *
 * @author [iamnambiar](https://github.com/iamnambiar)
 */
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @brief Mathematical algorithms
 * @namespace
 */
namespace math {
/**
 * @brief Function to calculate the sum of all the proper divisor
 * of an integer.
 * @param num selected number.
 * @return Sum of the proper divisor of the number.
 */
int sum_of_divisor(int num) {
    // Variable to store the sum of all proper divisors.
    int sum = 1;
    // Below loop condition helps to reduce Time complexity by a factor of
    // square root of the number.
    for (int div = 2; div * div <= num; ++div) {
        // Check 'div' is divisor of 'num'.
        if (num % div == 0) {
            // If both divisor are same, add once to 'sum'
            if (div == (num / div)) {
                sum += div;
            } else {
                // If both divisor are not the same, add both to 'sum'.
                sum += (div + (num / div));
            }
        }
    }
    return sum;
}

/**
 * @brief Function to check whether the pair is amicable or not.
 * @param x First number.
 * @param y Second number.
 * @return `true` if the pair is amicable
 * @return `false` if the pair is not amicable
 */
bool are_amicable(int x, int y) {
    return (sum_of_divisor(x) == y) && (sum_of_divisor(y) == x);
}
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    assert(math::are_amicable(220, 284) == true);
    assert(math::are_amicable(6368, 6232) == true);
    assert(math::are_amicable(458, 232) == false);
    assert(math::are_amicable(17296, 18416) == true);
    assert(math::are_amicable(18416, 17296) == true);

    std::cout << "All tests have successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // perform self-tests implementations
    return 0;
}
