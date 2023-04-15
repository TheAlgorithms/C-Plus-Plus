/**
 * @file
 * @brief Implementation of [Euler's Totient](https://en.wikipedia.org/wiki/Euler%27s_totient_function)
 * @description
 * Euler's Totient is also known as the phi function hence the name in the code.
 * Equation:
 * φ(n) = Πp|n (1 - 1/p)
 * @author [Mann Mehta](https://github.com/mann2108)
 */

#include <iostream> // for io operations
#include <cassert> // for assert

/**
 * @brief Mathematical algorithms
 * @namespace
 */
namespace math {
/**
 * @brief Function to calculate Euler's Totient
 * @param n is the number to find the Euler's Totient of.
 */
uint64_t phiFunction(uint64_t n) {
    uint64_t result = n;
    for (uint64_t i = 2; i * i <= n; i++) {
        if (n % i != 0) continue;
        while (n % i == 0) n /= i;

        result -= result / i;
    }
    if (n > 1) result -= result / n;

    return result;
}
} // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    assert(math::phiFunction(1) == 1);
    assert(math::phiFunction(2) == 1);
    assert(math::phiFunction(10) == 4);
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();
    return 0;
}
