/**
 *
 * @file
 * \brief A C++ Program to check whether a pair of number is [amicable
 * pair](https://en.wikipedia.org/wiki/Amicable_numbers) or not.
 *
 * \details
 * Amicable Pair are two positive integers such that sum of the proper divisor
 * of each number is equal to the other number.
 * @author iamnambiar
 */
#include <cassert>
#include <iostream>

/**
 * Function to calculate the sum of all the proper divisor
 * of an integer.
 * @param num First number.
 * @return Sum of the proper divisor of the number.
 */
int sum_of_divisor(int num) {
    // Variable to store the sum of all proper divisors.
    int sum = 0;
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
    return sum + 1;
}

/**
 * Function to check whether the pair is amicable or not.
 * @param x First number.
 * @param y Second number.
 * @return `true` if the pair is amicable
 * @return `false` if the pair is not amicable
 */
bool are_amicable(int x, int y) {
    return (sum_of_divisor(x) == y) && (sum_of_divisor(y) == x);
}

/**
 * Function for testing the is_amicable() with
 * all the test cases.
 */
void test() {
    // are_amicable(220, 284) returns true.
    assert(are_amicable(220, 284) == true);
    // are_amicable(6232, 6368) returns true.
    assert(are_amicable(6368, 6232) == true);
    // are_amicable(458, 232) returns false.
    assert(are_amicable(458, 232) == false);
}

/**
 * Main Function
 */
int main() {
    test();
    std::cout << "Assertion Success." << std::endl;
    return 0;
}
