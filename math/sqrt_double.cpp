/**
 * @file
 * @brief Calculate the square root of any positive real number in \f$O(\log
 * N)\f$ time, with precision fixed using [bisection
 * method](https://en.wikipedia.org/wiki/Bisection_method) of root-finding.
 * @author DarkWarrior703
 * @see Can be implemented using faster and better algorithms like
 * newton_raphson_method.cpp and false_position.cpp
 */
#include <cassert> /// For assert
#include <iostream> /// For IO operations
#include <cmath> /// For std::abs, std::sqrt

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
    /**
     * @brief Bisection method implemented for the function \f$x^2-a=0\f$
     * whose roots are \f$\pm\sqrt{a}\f$ and only the positive root is returned.
     * @param a number to find the square root of
     * @returns positive square root of `a`, or `-1` if `a < 0`
     */
    double Sqrt(double a) {
        if (a > 0 && a < 1) {
            return 1 / Sqrt(1 / a);
        }
        double l = 0, r = a;
        /* Epsilon is the precision.
        A great precision is
        between 1e-7 and 1e-12.
        double epsilon = 1e-12;
        */
        double epsilon = 1e-12;
        while (l <= r) {
            double mid = (l + r) / 2;
            if (mid * mid > a) {
                r = mid;
            }
            else {
                if (a - mid * mid < epsilon) {
                    return mid;
                }
                l = mid;
            }
        }
        return -1;
    }
}

/**
 * @brief Self-test implementations
 * @returns void
*/
static void test() {
    const double eps = 1e-9;

    assert(std::abs(std::sqrt(123) - math::Sqrt(123)) < eps);
    assert(std::abs(std::sqrt(25) - math::Sqrt(25)) < eps);
    assert(std::abs(std::sqrt(0.25) - math::Sqrt(0.25)) < eps);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}
