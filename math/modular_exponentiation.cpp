/**
 * @file
 * @brief C++ Program for Modular Exponentiation Iteratively.
 * @details The task is to calculate the value of an integer a raised to an
 * integer exponent b under modulo c.
 * @note The time complexity of this approach is O(log b).
 *
 * Example:
 * (4^3) % 5 (where ^ stands for exponentiation and % for modulo)
 * (4*4*4) % 5
 * (4 % 5) * ( (4*4) % 5 )
 * 4 * (16 % 5)
 * 4 * 1
 * 4
 * We can also verify the result as 4^3 is 64 and 64 modulo 5 is 4
 *
 * @author [Shri2206](https://github.com/Shri2206)
 */
#include <cassert>   /// for assert
#include <iostream>  /// for io operations

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief This function calculates a raised to exponent b under modulo c using
 * modular exponentiation.
 * @param a integer base
 * @param b unsigned integer exponent
 * @param c integer modulo
 * @return a raised to power b modulo c
 */
uint64_t power(uint64_t a, uint64_t b, uint64_t c) {
    uint64_t ans = 1;  /// Initialize the answer to be returned
    a = a % c;         /// Update a if it is more than or equal to c
    if (a == 0) {
        return 0;  /// In case a is divisible by c;
    }
    while (b > 0) {
        /// If b is odd, multiply a with answer
        if (b & 1) {
            ans = ((ans % c) * (a % c)) % c;
        }
        /// b must be even now
        b = b >> 1;  /// b = b/2
        a = ((a % c) * (a % c)) % c;
    }
    return ans;
}

}  // namespace math

/**
 * Function for testing power function.
 * test cases and assert statement.
 * @returns `void`
 */
static void test() {
    uint32_t test_case_1 = math::power(2, 5, 13);
    assert(test_case_1 == 6);
    std::cout << "Test 1 Passed!" << std::endl;

    uint32_t test_case_2 = math::power(14, 7, 15);
    assert(test_case_2 == 14);
    std::cout << "Test 2 Passed!" << std::endl;

    uint64_t test_case_3 = math::power(8, 15, 41);
    assert(test_case_3 == 32);
    std::cout << "Test 3 Passed!" << std::endl;

    uint64_t test_case_4 = math::power(27, 2, 5);
    assert(test_case_4 == 4);
    std::cout << "Test 4 Passed!" << std::endl;

    uint16_t test_case_5 = math::power(7, 3, 6);
    assert(test_case_5 == 1);
    std::cout << "Test 5 Passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // execute the tests
    return 0;
}
