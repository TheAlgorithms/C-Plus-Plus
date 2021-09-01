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
 * numbers (not integers).
 * For more details, refer to the
 * [Algorithms-Explanation](https://github.com/TheAlgorithms/Algorithms-Explanation/blob/master/en/Basic%20Math/Finding
 * the number of digits in a number.md) repository.
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @brief Main function
 * @returns 0 on exit
 */
uint64_t finding_number_of_digits_in_a_number(uint64_t n) {
    // Initialize `count` by 0

    uint64_t count = 0;

    std::cout << "Enter an integer: ";
    std::cin >> n;

    // iterate until `n` becomes 0
    // remove last digit from `n` in each iteration
    // increase `count` by 1 in each iteration
    while (n != 0) {
        // we can also use `n = n / 10`
        n /= 10;
        // each time the loop is running, `count` will be incremented by 1.
        ++count;
    }
    std::cout << "Number of digits: " << count;

    return 0;
}

void test(uint64_t count, uint64_t expected) {
    assert(finding_number_of_digits_in_a_number(count) == expected);
}

void tests() {
    std::cout << "Test 1:\t n=5\t...";
    test(5, 1);
    std::cout << "passed\n";

    std::cout << "Test 2:\t n=15\t...";
    test(15, 2);
    std::cout << "passed\n";

    std::cout << "Test 3:\t n=0\t...";
    test(0, 1);
    std::cout << "passed\n";

    std::cout << "Test 3:\t n=0\t...";
    test(-10, 2);
    std::cout << "passed\n";
}

/**
 * Main function
 */
int main() {
    tests();
    return 0;
}
