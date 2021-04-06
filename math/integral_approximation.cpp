/**
 * @file
 * @brief Compute integral approximation of function
 *
 * \author [Benjamin Walton](https://github.com/bwalton24)
 * \author [Shiqi Sheng](https://github.com/shiqisheng00)
 */
#include <iostream>
#include <cassert>
#include <math.h>
 
double f(double x) {
    double y = x*x + cos(x) + exp(x) + log(x)*log(x);
    return y;
}
 
/**
 * Computes Integral Approximation
 * @param lb lower bound
 * @param ub upper bound
 * @param delta delta
 * @returns 
 */
double integral_approx(double lb, double ub, double delta) {
    assert(lb <= ub);
    double result = 0;
    for(double i = lb; i < ub; i += delta) {
        result += 0.5*delta*(f(i) + f(i + delta));
    }
    return result;
}
 
/**
 * Function for testing integral_approx function.
 * test cases and assert statement.
 * @returns `void`
 */
static void test() {
    std::cout << integral_approx(.05, 2.55, .03) << std::endl;
}
 
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // execute the tests
    return 0;
}
 
 

