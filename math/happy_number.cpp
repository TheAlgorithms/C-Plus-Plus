/**
 * @file
 * @brief Check whether a number is a "happy number".
 *
 * Repeatedly replace a number with the sum of the squares of its digits.
 * If the process reaches 1, the number is happy. If it falls into a
 * cycle that never reaches 1, the number is not happy.
 *
 * Example: 19 -> 82 -> 68 -> 100 -> 1  (happy)
 */

#include <cassert>
#include <iostream>
#include <unordered_set>

/** @brief Math algorithms */
namespace math {

/**
 * @brief Sum of the squares of the digits of a number.
 * @param n non-negative integer
 * @return sum of squares of the digits (e.g. 82 -> 8*8 + 2*2 = 68)
 */
int sum_of_digit_squares(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

/**
 * @brief Check whether a number is happy.
 * @param n positive integer
 * @return true if n is a happy number, false otherwise
 */
bool is_happy_number(int n) {
    assert(n > 0);
    std::unordered_set<int> seen;  // numbers we've already visited

    while (n != 1) {
        if (seen.count(n)) {
            return false;  // we're in a loop, so it will never reach 1
        }
        seen.insert(n);
        n = sum_of_digit_squares(n);
    }
    return true;
}

}  // namespace math

/** @brief Self-test implementations */
static void test() {
    assert(math::sum_of_digit_squares(82) == 68);
    assert(math::is_happy_number(1) == true);
    assert(math::is_happy_number(7) == true);
    assert(math::is_happy_number(19) == true);
    assert(math::is_happy_number(100) == true);
    assert(math::is_happy_number(2) == false);
    assert(math::is_happy_number(4) == false);
    assert(math::is_happy_number(20) == false);
    std::cout << "All tests passed!\n";
}

/** @brief Main function */
int main() {
    test();
    return 0;
}