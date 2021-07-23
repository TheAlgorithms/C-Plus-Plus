/**
 * @file
 * @brief Program to count number of ciphers in `n!`(https://www.tutorialspoint.com/count-trailing-zeros-in-factorial-of-a-number-in-cplusplus).
 * @details
 * We are given a number. The algorithm finds all
 * the zeroes at the end of factorial of that number.
 * @author [Swastika Gupta](https://github.com/Swastyy)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace numberOfCiphersInFactorialN
 * @brief Program to count number of ciphers in `n!`(https://www.tutorialspoint.com/count-trailing-zeros-in-factorial-of-a-number-in-cplusplus).
 */
namespace numberOfCiphersInFactorialN {
 /**
 * @brief Function to count the number of trailing ciphers.
 * @param n, Number for which `n!` ciphers are returned
 * @return count, Number of ciphers in `n!`.
 */

uint64_t numberOfCiphersInFactorialN(uint64_t n) {
    // count is to store the number of 5's in factorial(n)
    uint64_t count = 0;

    // Keep dividing n by powers of
    // 5 and update count
    for (uint64_t i = 5; n / i >= 1; i *= 5) {
        count += static_cast<uint64_t>(n) / i;
    }

    return count;
}
}  // namespace numberOfCiphersInFactorialN
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // Test 1
    std::cout << "1st test ";
    assert(bit_manipulation::numberOfCiphersInFactorialN::numberOfCiphersInFactorialN(395) == 97);
    std::cout << "passed" << std::endl;

    // Test 2
    std::cout << "2nd test ";
    assert(bit_manipulation::numberOfCiphersInFactorialN::numberOfCiphersInFactorialN(977) == 242);
    std::cout << "passed" << std::endl;

    // Test 3
    std::cout << "3rd test ";
    assert(bit_manipulation::numberOfCiphersInFactorialN::numberOfCiphersInFactorialN(871) == 215);
    std::cout << "passed" << std::endl;

    // Test 4
    std::cout << "4th test ";
    assert(bit_manipulation::numberOfCiphersInFactorialN::numberOfCiphersInFactorialN(239) == 57);
    std::cout << "passed" << std::endl;

    // Test 5
    std::cout << "5th test ";
    assert(bit_manipulation::numberOfCiphersInFactorialN::numberOfCiphersInFactorialN(0) == 0);
    std::cout << "passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
