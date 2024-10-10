/**
 * @file
 * @brief [Exponential
 * Distribution](https://en.wikipedia.org/wiki/Exponential_distribution)
 *
 * The exponential distribution is used to model
 * events occuring between a Poisson process like radioactive decay.
 *
 * \f[P(x, \lambda) = \lambda e^{-\lambda x}\f]
 *
 * Summary of variables used:
 * \f$\lambda\f$ : rate parameter
 */

#include <cassert>   // For asserting the test cases
#include <cmath>     // For power function
#include <iostream>  // For I/O operation

/**
 * @brief the expected value of the exponential distribution
 * @returns \f[\mu = \frac{1}{\lambda}\f]
 */
double exponential_expected(double lambda) {
    if (lambda <= 0) {
        std::cout << "Error: Lambda must be greater than 0." << '\n';
        assert(lambda > 0);
    }
    return 1 / lambda;
}

/**
 * @brief the variance of the exponential distribution
 * @returns \f[\sigma^2 = \frac{1}{\lambda^2}\f]
 */
double exponential_var(double lambda) {
    if (lambda <= 0) {
        std::cout << "Error: Lambda must be greater than 0." << '\n';
        assert(lambda > 0);
    }
    return 1 / pow(lambda, 2);
}

/**
 * @brief the standard deviation of the exponential distribution
 * @returns \f[\sigma = \frac{1}{\lambda}\f]
 */
double exponential_std(double lambda) {
    if (lambda <= 0) {
        std::cout << "Error: Lambda must be greater than 0." << '\n';
        assert(lambda > 0);
    }
    return 1 / lambda;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    double lambda_1 = 1;
    double expected_1 = 1;
    double var_1 = 1;
    double std_1 = 1;

    double lambda_2 = 2;
    double expected_2 = 0.5;
    double var_2 = 0.25;
    double std_2 = 0.5;

    double lambda_3 = 3;
    double expected_3 = 0.333333;
    double var_3 = 0.111111;
    double std_3 = 0.333333;

    const float threshold = 1e-3f;

    std::cout << "Test for lambda = 1 \n";
    assert(std::abs(expected_1 - exponential_expected(lambda_1)) < threshold);
    assert(std::abs(var_1 - exponential_var(lambda_1)) < threshold);
    assert(std::abs(std_1 - exponential_std(lambda_1)) < threshold);
    std::cout << "ALL TEST PASSED\n\n";

    std::cout << "Test for lambda = 2 \n";
    assert(std::abs(expected_2 - exponential_expected(lambda_2)) < threshold);
    assert(std::abs(var_2 - exponential_var(lambda_2)) < threshold);
    assert(std::abs(std_2 - exponential_std(lambda_2)) < threshold);
    std::cout << "ALL TEST PASSED\n\n";

    std::cout << "Test for lambda = 3 \n";
    assert(std::abs(expected_3 - exponential_expected(lambda_3)) < threshold);
    assert(std::abs(var_3 - exponential_var(lambda_3)) < threshold);
    assert(std::abs(std_3 - exponential_std(lambda_3)) < threshold);
    std::cout << "ALL TEST PASSED\n";
}

/**
 * @brief Main function
 * @return 0 on exit
 */
int main() {
    test();  // Self test implementation
    return 0;
}
