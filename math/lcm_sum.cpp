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
#include <cstdint>
#include <iostream>  /// for std::cin and std::cout
#include <vector>    /// for std::vector

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief Computes the sum of Least Common Multiples from 1 to n.
 *
 * Calculates:
 * \f[
 * \sum_{i=1}^{n} \mathrm{LCM}(i,n)
 * \f]
 *
 * using Euler's Totient Function.
 *
 * @param num Positive integer n.
 * @return Sum of LCM(i,n) for all 1 ≤ i ≤ n.
 *  * @note
 * Time Complexity: O(n log log n + n log n)
 * Space Complexity: O(n)
 */
uint64_t lcmSum(uint16_t num) {
    uint64_t divisor = 0;
    uint64_t multiple = 0;
    std::vector<uint64_t> eulerTotient(num + 1);
    std::vector<uint64_t> sumOfEulerTotient(num + 1);

    // Initialize Euler Totient values.
    for (divisor = 1; divisor <= num; divisor++) {
        eulerTotient[divisor] = divisor;
    }

    // Compute Euler's Totient values using the sieve method.
    for (divisor = 2; divisor <= num; divisor++) {
        if (eulerTotient[divisor] == divisor) {
            for (multiple = divisor; multiple <= num; multiple += divisor) {
                eulerTotient[multiple] = eulerTotient[multiple] / divisor;
                eulerTotient[multiple] = eulerTotient[multiple] * (divisor - 1);
            }
        }
    }

    // Compute Σ(d × φ(d)) for every divisor.
    for (divisor = 1; divisor <= num; divisor++) {
        for (multiple = divisor; multiple <= num; multiple += divisor) {
            sumOfEulerTotient[multiple] += eulerTotient[divisor] * divisor;
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
    uint64_t n = 1;
    uint64_t test_0 = math::lcmSum(n);
    assert(test_0 == 1);
    std::cout << "Passed Test 0!" << std::endl;
    
    n = 2;
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
