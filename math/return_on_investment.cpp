/**
 * @file
 * @brief Calculate [Return on Investment (ROI)](https://www.investopedia.com/terms/r/returnoninvestment.asp)
 *
 * @details
 * Return on Investment (ROI) is a financial metric that measures the
 * profitability of an investment relative to its cost.
 *
 * Formula:
 * \f[
 *     ROI = \frac{Gain - Cost}{Cost} \times 100
 * \f]
 *
 * @author [InukaWijerathna](https://github.com/InukaWijerathna)
 */

#include <cassert>    /// for assert
#include <iostream>   /// for IO operations
#include <stdexcept>  /// for std::invalid_argument

/**
 * @brief Mathematical algorithms
 * @namespace math
 */
namespace math {

/**
 * @brief Calculates return on investment as a percentage
 * @param gain_from_investment total value gained from the investment
 * @param cost_of_investment total cost of the investment
 * @return ROI as a percentage
 * @throws std::invalid_argument if cost_of_investment is not positive
 */
double return_on_investment(double gain_from_investment,
                            double cost_of_investment) {
    if (cost_of_investment <= 0) {
        throw std::invalid_argument(
            "cost_of_investment must be greater than 0");
    }
    return (gain_from_investment - cost_of_investment) / cost_of_investment *
           100.0;
}

}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    assert(math::return_on_investment(1000.0, 500.0) == 100.0);
    assert(math::return_on_investment(500.0, 500.0) == 0.0);
    assert(math::return_on_investment(200.0, 500.0) == -60.0);
    assert(math::return_on_investment(0.0, 500.0) == -100.0);
    std::cout << "All tests passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
