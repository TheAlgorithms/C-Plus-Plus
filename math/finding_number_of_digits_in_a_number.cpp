/**
 * @author [aminos 🇮🇳](https://github.com/amino19)
 * @file
 *
 * @brief [Program to count digits
 * in an
 * integer](https://www.geeksforgeeks.org/program-count-digits-integer-3-different-methods)
 * @details It is a very basic math of finding number of digits in a given
 * number i.e, we can use it by inputting values whether it can be a
 * positive/negative value, let's say: an integer. There is also a second
 * method: by using "K = floor(log10(N) + 1)", but it's only applicable for
 * numbers (not integers). The code for that is also included (count_digits).
 * For more details, refer to the
 * [Algorithms-Explanation](https://github.com/TheAlgorithms/Algorithms-Explanation/blob/master/en/Basic%20Math/Finding
 * the number of digits in a number.md) repository.
 */

#include <cassert>   /// for assert
#include <cmath>     /// for log calculation
#include <iostream>  /// for IO operations

/**
 * @brief The main function that checks
 * the number of digits in a number.
 * TC : O(number of digits)
 * @param n the number to check its digits
 * @returns the digits count
 */
uint64_t finding_number_of_digits_in_a_number(uint64_t n) {
    uint64_t count = 0;  ///< the variable used for the digits count

    // iterate until `n` becomes 0
    // remove last digit from `n` in each iteration
    // increase `count` by 1 in each iteration
    while (n != 0) {
        // we can also use `n = n / 10`
        n /= 10;
        // each time the loop is running, `count` will be incremented by 1.
        ++count;
    }

    return count;
}

/**
 * @brief This function finds the number of digits
 * in constant time
 * TC :O(1)
 * @param n the number to check its digits
 * @returns the digits count
 */
uint64_t count_digits(uint64_t n) {
    // to handle the negative numbers
    if (n < 0) {
        n = -n;
    }
    // log(0) is undefined
    else if (n == 0) {
        // handling the value 0
        return 0;
    }
    uint64_t count = floor(log10(n) + 1);

    return count;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    assert(finding_number_of_digits_in_a_number(5492) == 4);
    assert(finding_number_of_digits_in_a_number(-0) == 0);
    assert(finding_number_of_digits_in_a_number(10000) == 5);
    assert(finding_number_of_digits_in_a_number(9) == 1);
    assert(finding_number_of_digits_in_a_number(100000) == 6);
    assert(finding_number_of_digits_in_a_number(13) == 2);
    assert(finding_number_of_digits_in_a_number(564) == 3);
}

static void test_count_digits() {
    assert(count_digits(5492) == 4);
    assert(count_digits(-0) == 0);
    assert(count_digits(10000) == 5);
    assert(count_digits(9) == 1);
    assert(count_digits(100000) == 6);
    assert(count_digits(13) == 2);
    assert(count_digits(564) == 3);
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // run self-test implementations
    test();  
    test_count_digits();
    std::cout << "All tests have successfully passed!\n";
    return 0;
}
