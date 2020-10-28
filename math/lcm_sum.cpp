/**
 * @file
 * @brief An algorithm to calculate the sum of LCM: \f$\mathrm{LCM}(1,n) +
 * \mathrm{LCM}(2,n) + \ldots + \mathrm{LCM}(n,n)\f$
 * @details An algorithm to calculate the sum of LCM: \f$\mathrm{LCM}(1,n) +
 * \mathrm{LCM}(2,n) + \ldots + \mathrm{LCM}(n,n)\f$ where
 * \f$\mathrm{LCM}(i,n)\f$ denotes the Least Common Multiple of the integers i
 * and n. For n greater than or equal to 1. The value of the sum is calculated
 * by formula: \f[ \sum\mathrm{LCM}(i, n) = \frac{1}{2} \left[\left(\sum (d *
 * \mathrm{ETF}(d)) + 1\right) * n\right] \f] where \mathrm{ETF}(i) represents
 * Euler totient function of i.
 * @author [Chesta Mittal](https://github.com/chestamittal)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for std::cin and std::cout
#include <vector>    /// for std::vector

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * Function to compute sum of euler totients in sumOfEulerTotient vector
 * @param num input number
 * @returns int Sum of LCMs, i.e. ∑LCM(i, num) from i = 1 to num
 */
uint64_t lcmSum(const uint16_t& num) {
    uint64_t i = 0, j = 0;
    std::vector<uint64_t> eulerTotient(num + 1);
    std::vector<uint64_t> sumOfEulerTotient(num + 1);

    // storing initial values in eulerTotient vector
    for (i = 1; i <= num; i++) {
        eulerTotient[i] = i;
    }

    // applying totient sieve
    for (i = 2; i <= num; i++) {
        if (eulerTotient[i] == i) {
            for (j = i; j <= num; j += i) {
                eulerTotient[j] = eulerTotient[j] / i;
                eulerTotient[j] = eulerTotient[j] * (i - 1);
            }
        }
    }

    // computing sum of euler totients
    for (i = 1; i <= num; i++) {
        for (j = i; j <= num; j += i) {
            sumOfEulerTotient[j] += eulerTotient[i] * i;
        }
    }

    return ((sumOfEulerTotient[num] + 1) * num) / 2;
}
}  // namespace math

/**
 * Function for testing lcmSum function.
 * test cases and assert statement.
 * @returns `void`
 */
static void test() {
    uint64_t n = 2;
    uint64_t test_1 = math::lcmSum(n);
    assert(test_1 == 4);
    std::cout << "Passed Test 1!" << std::endl;

    n = 5;
    uint64_t test_2 = math::lcmSum(n);
    assert(test_2 == 55);
    std::cout << "Passed Test 2!" << std::endl;

    n = 10;
    uint64_t test_3 = math::lcmSum(n);
    assert(test_3 == 320);
    std::cout << "Passed Test 3!" << std::endl;

    n = 11;
    uint64_t test_4 = math::lcmSum(n);
    assert(test_4 == 616);
    std::cout << "Passed Test 4!" << std::endl;

    n = 15;
    uint64_t test_5 = math::lcmSum(n);
    assert(test_5 == 1110);
    std::cout << "Passed Test 5!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // execute the tests
    return 0;
}
