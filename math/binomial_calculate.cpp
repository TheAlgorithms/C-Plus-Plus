/**
 * @file
 * @brief Program to calculate [Binomial
 * coefficients](https://en.wikipedia.org/wiki/Binomial_coefficient)
 *
 * @author [astronmax](https://github.com/astronmax)
 */

#include <cassert>   /// for assert
#include <cstdint>   /// for int32_t type
#include <cstdlib>   /// for atoi
#include <iostream>  /// for IO operations

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @namespace binomial
 * @brief Functions for [Binomial
 * coefficients](https://en.wikipedia.org/wiki/Binomial_coefficient)
 * implementation
 */
namespace binomial {
/**
 * @brief Function to calculate binomial coefficients
 * @param n first value
 * @param k second value
 * @return binomial coefficient for n and k
 */
size_t calculate(int32_t n, int32_t k) {
    // basic cases
    if (k > (n / 2))
        k = n - k;
    if (k == 1)
        return n;
    if (k == 0)
        return 1;

    size_t result = 1;
    for (int32_t i = 1; i <= k; ++i) {
        result *= n - k + i;
        result /= i;
    }

    return result;
}
}  // namespace binomial
}  // namespace math

/**
 * @brief Test implementations
 * @returns void
 */
static void tests() {
    // tests for calculate function
    assert(math::binomial::calculate(1, 1) == 1);
    assert(math::binomial::calculate(57, 57) == 1);
    assert(math::binomial::calculate(6, 3) == 20);
    assert(math::binomial::calculate(10, 5) == 252);
    assert(math::binomial::calculate(20, 10) == 184756);
    assert(math::binomial::calculate(30, 15) == 155117520);
    assert(math::binomial::calculate(40, 20) == 137846528820);
    assert(math::binomial::calculate(50, 25) == 126410606437752);
    assert(math::binomial::calculate(60, 30) == 118264581564861424);
    assert(math::binomial::calculate(62, 31) == 465428353255261088);

    std::cout << "[+] Binomial coefficients calculate test completed"
              << std::endl;
}

/**
 * @brief Main function
 * @param argc commandline argument count
 * @param argv commandline array of arguments
 * @returns 0 on exit
 */
int main(int argc, const char* argv[]) {
    tests();  // run self-test implementations

    if (argc < 3) {
        std::cout << "Usage ./binomial_calculate {n} {k}" << std::endl;
        return 0;
    }

    int32_t n = atoi(argv[1]);
    int32_t k = atoi(argv[2]);

    std::cout << math::binomial::calculate(n, k) << std::endl;
    return 0;
}
