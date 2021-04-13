/**
 * @file
 * @brief Compute integral approximation of function
 *
 * \author [Benjamin Walton](https://github.com/bwalton24)
 * \author [Shiqi Sheng](https://github.com/shiqisheng00)
 */
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>

/**
 * Computes Integral Approximation
 * @param lb lower bound
 * @param ub upper bound
 * @param func pass in function
 * @param delta delta
 * @returns
 */
double integral_approx(double lb, double ub,
                       const std::function<double(double)>& func,
                       double delta = .001) {
    assert(lb <= ub);
    double result = 0;
    for (double i = lb; i < ub; i += delta) {
        assert(!isnan(func(i)));
        assert(!isnan(func(i + delta)));
        result += 0.5 * delta * (func(i) + func(i + delta));
    }
    return result;
}

double test_func1(double x) {
    double y = x * x + cos(x) + exp(x) + log(x) * log(x);
    return y;
}

/**
 * Function for testing integral_approx function.
 * test cases and assert statement.
 * @returns `void`
 */
static void test() {
    // Design a couple of functions and calculate their Riemann sum by hand,
    // then assert that with the output
    std::cout << integral_approx(-1.24, 1.02, [](const double x) {
        return log(x) + exp(x) + x;
    }) << std::endl;

    std::cout << integral_approx(1.24, 10.25, test_func1) << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // execute the tests
    return 0;
}
