/*
 * @Author: chuanjun
 * @Date: 2024-11-02 14:13:24
 * @email: chuanjun1978@gmail.com
 * @website-github: https://github.com/Chuan1937
 * @LastEditTime: 2024-11-04 12:31:24
 */
/**
 * @{
 * \file montecarlo_pi.cpp
 * \brief [Monte Carlo](https://en.wikipedia.org/wiki/Monte_Carlo_method)
 * method for approximating PI.
 *
 * \author [chuanjun](https://github.com/Chuan1937)
 * \date 2024-11-02
 * \details
 * The Monte Carlo method is used to approximate the value of PI by randomly sampling points in a unit square and determining the ratio of points within a unit circle.
 */

#include <iostream>    /// for input and output
#include <cmath>       /// for mathematical functions like sqrt
#include <random>      /// for random number generation
#include <cassert>     /// for using assert


/**
 * @namespace numerical_methods
 * @brief Numerical methods and functions
 */
namespace numerical_methods {

/**
 * @namespace monte_carlo
 * @brief Functions for calculating approximations using the Monte Carlo method
 */
namespace monte_carlo {

/**
 * @brief Estimates the value of PI using the Monte Carlo method with high precision.
 * @param epochs Number of random points to generate (default is 1,000,000).
 * @returns Approximated value of PI as a long double.
 */
long double montecarlo_pi(int epochs = 1000000) {
    const double radius = 1.0;   // Radius of the unit circle

    // Initialize random engine and uniform distribution
    std::default_random_engine random_engine;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    int inside_circle_count = 0;
    for (int i = 0; i < epochs; ++i) {
        double x = distribution(random_engine);
        double y = distribution(random_engine);
        double distance = std::sqrt(x * x + y * y);
        if (distance <= radius) {
            ++inside_circle_count;
        }
    }

    long double pi_estimate = 4.0L * static_cast<long double>(inside_circle_count) / epochs;
    return pi_estimate;
}

}  // namespace monte_carlo
}  // namespace numerical_methods

/**
 * @brief Tests the Monte Carlo approximation function with assertions.
 * @returns void
 */
static void test() {
    std::cout << "Testing Monte Carlo PI approximation function...\n";

    long double pi_approximation = numerical_methods::monte_carlo::montecarlo_pi(1000000);
    std::cout << "Approximation of PI with 1,000,000 epochs: " << pi_approximation << "\n";
    std::cout << "Expected PI value: " << M_PI << "\n";

    // Assert that the approximation is within an acceptable error range
    long double tolerance = 0.01;  // Acceptable range of error
    assert(std::abs(pi_approximation - M_PI) < tolerance && "PI approximation is out of acceptable range.");
    std::cout << "Test passed. PI approximation is within tolerance.\n";
}

/**
 * @brief Main function to execute the test.
 * @returns 0 on exit success
 */
int main() {
    test();  // Execute the tests
    return 0;
}
