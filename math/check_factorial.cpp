/**
 * @file
 * @brief A simple program to check if the given number is a factorial of some
 * number or not.
 * @author [Divyajyoti Ukirde](https://github.com/divyajyotiuk)
 */
#include <cassert>
#include <iostream>

/**
 * Function to check if the given number is factorial of some number or not.
 * @param n number to be checked.
 * @return if number is a factorial, returns true, else false.
 */

bool is_factorial(uint64_t n) {
    if (n <= 0) {
        return false;
    }
    for (uint32_t i = 1;; i++) {
        if (n % i != 0) {
            break;
        }
        n = n / i;
    }
    if (n == 1) {
        return true;
    } else {
        return false;
    }
}

/** Test function
 * @returns void
 */
void tests() {
    std::cout << "Test 1:\t n=50\n";
    assert(is_factorial(50) == false);
    std::cout << "passed\n";

    std::cout << "Test 2:\t n=720\n";
    assert(is_factorial(720) == true);
    std::cout << "passed\n";

    std::cout << "Test 3:\t n=0\n";
    assert(is_factorial(0) == false);
    std::cout << "passed\n";

    std::cout << "Test 4:\t n=479001600\n";
    assert(is_factorial(479001600) == true);
    std::cout << "passed\n";

    std::cout << "Test 5:\t n=-24\n";
    assert(is_factorial(-24) == false);
    std::cout << "passed\n";
}

/** Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
