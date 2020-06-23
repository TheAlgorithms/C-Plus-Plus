/**
 * @file
 * @brief Calculate the square root of any positive real number in \f$O(\log
 * N)\f$ time, with precision fixed using [bisection
 * method](https://en.wikipedia.org/wiki/Bisection_method) of root-finding.
 *
 * @see Can be implemented using faster and better algorithms like
 * newton_raphson_method.cpp and false_position.cpp
 */
#include <cassert>
#include <iostream>

/** Bisection method implemented for the function \f$x^2-a=0\f$
 * whose roots are \f$\pm\sqrt{a}\f$ and only the positive root is returned.
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
        } else {
            if (a - mid * mid < epsilon) {
                return mid;
            }
            l = mid;
        }
    }
    return -1;
}

/** main function */
int main() {
    double n{};
    std::cin >> n;
    assert(n >= 0);
    // Change this line for a better precision
    std::cout.precision(12);
    std::cout << std::fixed << Sqrt(n);
}
