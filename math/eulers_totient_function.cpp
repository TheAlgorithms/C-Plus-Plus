/**
 * @file
 * @brief Implementation of [Euler's Totient](https://en.wikipedia.org/wiki/Euler%27s_totient_function)
 * @description
 * Euler Totient Function is also known as phi function.
 * \f[\phi(n) =
 * \phi\left({p_1}^{a_1}\right)\cdot\phi\left({p_2}^{a_2}\right)\ldots\f] where
 * \f$p_1\f$, \f$p_2\f$, \f$\ldots\f$ are prime factors of n.
 * <br/>3 Euler's properties:
 * 1. \f$\phi(n) = n-1\f$
 * 2. \f$\phi(n^k) = n^k - n^{k-1}\f$
 * 3. \f$\phi(a,b) = \phi(a)\cdot\phi(b)\f$ where a and b are relative primes.
 *
 * Applying this 3 properties on the first equation.
 * \f[\phi(n) =
 * n\cdot\left(1-\frac{1}{p_1}\right)\cdot\left(1-\frac{1}{p_2}\right)\cdots\f]
 * where \f$p_1\f$,\f$p_2\f$... are prime factors.
 * Hence Implementation in \f$O\left(\sqrt{n}\right)\f$.
 * <br/>Some known values are:
 * * \f$\phi(100) = 40\f$
 * * \f$\phi(1) = 1\f$
 * * \f$\phi(17501) = 15120\f$
 * * \f$\phi(1420) = 560\f$
 * @author [Mann Mehta](https://github.com/mann2108)
 */

#include <iostream> /// for IO operations
#include <cassert> /// for assert

/**
 * @brief Mathematical algorithms
 * @namespace
 */
namespace math {
/**
 * @brief Function to calculate Euler's Totient
 * @param n the number to find the Euler's Totient of
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
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    assert(math::phiFunction(1) == 1);
    assert(math::phiFunction(2) == 1);
    assert(math::phiFunction(10) == 4);
    assert(math::phiFunction(123456) == 41088);
    assert(math::phiFunction(808017424794) == 263582333856);
    assert(math::phiFunction(3141592) == 1570792);
    assert(math::phiFunction(27182818) == 12545904);

    std::cout << "All tests have successfully passed!\n";
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
