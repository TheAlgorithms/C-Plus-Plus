/**
 * @file
 * @brief Implementation of the Composite Simpson Rule for the approximation
 *
 * @details The following is an implementation of the Composite Simpson Rule for
 * the approximation of definite integrals. More info -> wiki:
 * https://en.wikipedia.org/wiki/Simpson%27s_rule#Composite_Simpson's_rule
 *
 * The idea is to split the interval in an EVEN number N of intervals and use as
 * interpolation points the xi for which it applies that xi = x0 + i*h, where h
 * is a step defined as h = (b-a)/N where a and b are the first and last points
 * of the interval of the integration [a, b].
 *
 * We create a table of the xi and their corresponding f(xi) values and we
 * evaluate the integral by the formula: I = h/3 * {f(x0) + 4*f(x1) + 2*f(x2) +
 * ... + 2*f(xN-2) + 4*f(xN-1) + f(xN)}
 *
 * That means that the first and last indexed i f(xi) are multiplied by 1,
 * the odd indexed f(xi) by 4 and the even by 2.
 *
 * In this program there are 4 sample test functions f, g, k, l that are
 * evaluated in the same interval.
 *
 * Arguments can be passed as parameters from the command line argv[1] = N,
 * argv[2] = a, argv[3] = b
 *
 * N must be even number and a<b.
 *
 * In the end of the main() i compare the program's result with the one from
 * mathematical software with 2 decimal points margin.
 *
 * Add sample function by replacing one of the f, g, k, l and the assert
 *
 * @author [ggkogkou](https://github.com/ggkogkou)
 *
 */

#include <cassert>  /// for assert
#include <cmath>    /// for math functions
#include <cmath>
#include <cstdint>     /// for integer allocation
#include <cstdlib>     /// for std::atof
#include <functional>  /// for std::function
#include <iostream>    /// for IO operations
#include <map>         /// for std::map container

/**
 * @namespace numerical_methods
 * @brief Numerical algorithms/methods
 */
namespace numerical_methods {
/**
 * @namespace simpson_method
 * @brief Contains the Simpson's method implementation
 */
namespace simpson_method {
/**
 * @fn double evaluate_by_simpson(int N, double h, double a,
 * std::function<double (double)> func)
 * @brief Calculate integral or assert if integral is not a number (Nan)
 * @param N number of intervals
 * @param h step
 * @param a x0
 * @param func: choose the function that will be evaluated
 * @returns the result of the integration
 */
double evaluate_by_simpson(std::int32_t N, double h, double a,
                           const std::function<double(double)>& func) {
    std::map<std::int32_t, double>
        data_table;  // Contains the data points. key: i, value: f(xi)
    double xi = a;   // Initialize xi to the starting point x0 = a

    // Create the data table
    double temp = NAN;
    for (std::int32_t i = 0; i <= N; i++) {
        temp = func(xi);
        data_table.insert(
            std::pair<std::int32_t, double>(i, temp));  // add i and f(xi)
        xi += h;  // Get the next point xi for the next iteration
    }

    // Evaluate the integral.
    // Remember: f(x0) + 4*f(x1) + 2*f(x2) + ... + 2*f(xN-2) + 4*f(xN-1) + f(xN)
    double evaluate_integral = 0;
    for (std::int32_t i = 0; i <= N; i++) {
        if (i == 0 || i == N) {
            evaluate_integral += data_table.at(i);
        } else if (i % 2 == 1) {
            evaluate_integral += 4 * data_table.at(i);
        } else {
            evaluate_integral += 2 * data_table.at(i);
        }
    }

    // Multiply by the coefficient h/3
    evaluate_integral *= h / 3;

    // If the result calculated is nan, then the user has given wrong input
    // interval.
    assert(!std::isnan(evaluate_integral) &&
           "The definite integral can't be evaluated. Check the validity of "
           "your input.\n");
    // Else return
    return evaluate_integral;
}

/**
 * @fn double f(double x)
 * @brief A function f(x) that will be used to test the method
 * @param x The independent variable xi
 * @returns the value of the dependent variable yi = f(xi)
 */
double f(double x) { return std::sqrt(x) + std::log(x); }
/** @brief Another test function */
double g(double x) { return std::exp(-x) * (4 - std::pow(x, 2)); }
/** @brief Another test function */
double k(double x) { return std::sqrt(2 * std::pow(x, 3) + 3); }
/** @brief Another test function*/
double l(double x) { return x + std::log(2 * x + 1); }
}  // namespace simpson_method
}  // namespace numerical_methods

/**
 * \brief Self-test implementations
 * @param N is the number of intervals
 * @param h is the step
 * @param a is x0
 * @param b is the end of the interval
 * @param used_argv_parameters is 'true' if argv parameters are given and
 * 'false' if not
 */
static void test(std::int32_t N, double h, double a, double b,
                 bool used_argv_parameters) {
    // Call the functions and find the integral of each function
    double result_f = numerical_methods::simpson_method::evaluate_by_simpson(
        N, h, a, numerical_methods::simpson_method::f);
    assert((used_argv_parameters || (result_f >= 4.09 && result_f <= 4.10)) &&
           "The result of f(x) is wrong");
    std::cout << "The result of integral f(x) on interval [" << a << ", " << b
              << "] is equal to: " << result_f << std::endl;

    double result_g = numerical_methods::simpson_method::evaluate_by_simpson(
        N, h, a, numerical_methods::simpson_method::g);
    assert((used_argv_parameters || (result_g >= 0.27 && result_g <= 0.28)) &&
           "The result of g(x) is wrong");
    std::cout << "The result of integral g(x) on interval [" << a << ", " << b
              << "] is equal to: " << result_g << std::endl;

    double result_k = numerical_methods::simpson_method::evaluate_by_simpson(
        N, h, a, numerical_methods::simpson_method::k);
    assert((used_argv_parameters || (result_k >= 9.06 && result_k <= 9.07)) &&
           "The result of k(x) is wrong");
    std::cout << "The result of integral k(x) on interval [" << a << ", " << b
              << "] is equal to: " << result_k << std::endl;

    double result_l = numerical_methods::simpson_method::evaluate_by_simpson(
        N, h, a, numerical_methods::simpson_method::l);
    assert((used_argv_parameters || (result_l >= 7.16 && result_l <= 7.17)) &&
           "The result of l(x) is wrong");
    std::cout << "The result of integral l(x) on interval [" << a << ", " << b
              << "] is equal to: " << result_l << std::endl;
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char** argv) {
    std::int32_t N = 16;  /// Number of intervals to divide the integration
                          /// interval. MUST BE EVEN
    double a = 1, b = 3;  /// Starting and ending point of the integration in
                          /// the real axis
    double h = NAN;       /// Step, calculated by a, b and N

    bool used_argv_parameters =
        false;  // If argv parameters are used then the assert must be omitted
                // for the tst cases

    // Get user input (by the command line parameters or the console after
    // displaying messages)
    if (argc == 4) {
        N = std::atoi(argv[1]);
        a = std::atof(argv[2]);
        b = std::atof(argv[3]);
        // Check if a<b else abort
        assert(a < b && "a has to be less than b");
        assert(N > 0 && "N has to be > 0");
        if (N < 16 || a != 1 || b != 3) {
            used_argv_parameters = true;
        }
        std::cout << "You selected N=" << N << ", a=" << a << ", b=" << b
                  << std::endl;
    } else {
        std::cout << "Default N=" << N << ", a=" << a << ", b=" << b
                  << std::endl;
    }

    // Find the step
    h = (b - a) / N;

    test(N, h, a, b, used_argv_parameters);  // run self-test implementations

    return 0;
}
