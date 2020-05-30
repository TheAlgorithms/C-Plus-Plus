/**
 * @file
 * @brief Faster computation for \f$a^b\f$
 *
 * Program that computes \f$a^b\f$ in \f$O(logN)\f$ time.
 * It is based on formula that:
 * 1. if \f$b\f$ is even:
 *  \f$a^b = a^\frac{b}{2} \cdot a^\frac{b}{2} = {a^\frac{b}{2}}^2\f$
 * 2. if \f$b\f$ is odd: \f$a^b = a^\frac{b-1}{2}
 *  \cdot a^\frac{b-1}{2} \cdot a = {a^\frac{b-1}{2}}^2 \cdot a\f$
 *
 * We can compute \f$a^b\f$ recursively using above algorithm.
 */

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>

/**
 * algorithm implementation for \f$a^b\f$
 */
template <typename T>
double fast_power_recursive(T a, T b) {
    // negative power. a^b = 1 / (a^-b)
    if (b < 0)
        return 1.0 / fast_power_recursive(a, -b);

    if (b == 0)
        return 1;
    T bottom = fast_power_recursive(a, b >> 1);
    // Since it is integer division b/2 = (b-1)/2 where b is odd.
    // Therefore, case2 is easily solved by integer division.

    double result;
    if ((b & 1) == 0)  // case1
        result = bottom * bottom;
    else  // case2
        result = bottom * bottom * a;
    return result;
}

/**
    Same algorithm with little different formula.
    It still calculates in \f$O(\log N)\f$
*/
template <typename T>
double fast_power_linear(T a, T b) {
    // negative power. a^b = 1 / (a^-b)
    if (b < 0)
        return 1.0 / fast_power_linear(a, -b);

    double result = 1;
    while (b) {
        if (b & 1)
            result = result * a;
        a = a * a;
        b = b >> 1;
    }
    return result;
}

/**
 * Main function
 */
int main() {
    std::srand(std::time(nullptr));
    std::ios_base::sync_with_stdio(false);

    std::cout << "Testing..." << std::endl;
    for (int i = 0; i < 20; i++) {
        int a = std::rand() % 20 - 10;
        int b = std::rand() % 20 - 10;
        std::cout << std::endl << "Calculating " << a << "^" << b << std::endl;
        assert(fast_power_recursive(a, b) == std::pow(a, b));
        assert(fast_power_linear(a, b) == std::pow(a, b));

        std::cout << "------ " << a << "^" << b << " = "
                  << fast_power_recursive(a, b) << std::endl;
    }

    int64_t a, b;
    std::cin >> a >> b;

    std::cout << a << "^" << b << " = " << fast_power_recursive(a, b)
              << std::endl;

    std::cout << a << "^" << b << " = " << fast_power_linear(a, b) << std::endl;

    return 0;
}
