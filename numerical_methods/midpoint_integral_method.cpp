#include <iostream> /// for IO operations
#include <cmath> /// for math functions
#include <cassert> /// for assert
#include <cstdlib> /// for std::atof
#include <functional> /// for std::function
#include <map> /// for std::map container

/*!
 * @file
 * \brief A numerical method for easy approximation of integrals
 * \details The idea is to split the interval into N of intervals and use as interpolation points the xi
 * for which it applies that xi = x0 + i*h, where h is a step defined as h = (b-a)/N where a and b are the
 * first and last points of the interval of the integration [a, b].
 *
 * We create a table of the xi and their corresponding f(xi) values and we evaluate the integral by the formula:
 * I = h * {f(x0+h/2) + f(x1+h/2) + ... + f(xN-1+h/2)}
 *
 * Arguments can be passed as parameters from the command line argv[1] = N, argv[2] = a, argv[3] = b.
 * In this case if the default values N=16, a=1, b=3 are changed then the tests/assert are disabled.
 *
 * More info: [Link to wikipedia](https://en.wikipedia.org/wiki/Midpoint_method)
 *
 * @author [ggkogkou](https://github.com/ggkogkou)
*/

/**
 * @namespace numerical_methods
 * @brief Numerical algorithms/methods
 */
namespace numerical_methods {
/**
 * @namespace midpoint_rule
 * \brief Contains the function of the midpoint method implementation
*/
    namespace midpoint_rule {
        /*!
         * @fn double midpoint(const int N, const double h, const double a, const std::function<double (double)>& func)
         * \brief Implement midpoint method
         * @param N is the number of intervals
         * @param h is the step
         * @param a is x0
         * @param func is the function that will be integrated
         * @returns the result of the integration
        */
        double midpoint(const int N, const double h, const double a, const std::function<double(double)> &func) {
            std::map<int, double> data_table; // Contains the data points, key: i, value: f(xi)
            double xi = a; // Initialize xi to the starting point x0 = a

            // Create the data table
            // Loop from x0 to xN-1
            double temp;
            for (int i = 0; i < N; i++) {
                temp = func(xi + h / 2); // find f(xi+h/2)
                data_table.insert(std::pair<int, double>(i, temp)); // add i and f(xi)
                xi += h; // Get the next point xi for the next iteration
            }

            // Evaluate the integral.
            // Remember: {f(x0+h/2) + f(x1+h/2) + ... + f(xN-1+h/2)}
            double evaluate_integral = 0;
            for (int i = 0; i < N; i++) evaluate_integral += data_table.at(i);

            // Multiply by the coefficient h
            evaluate_integral *= h;

            // If the result calculated is nan, then the user has given wrong input interval.
            assert(!std::isnan(evaluate_integral) &&
                   "The definite integral can't be evaluated. Check the validity of your input.\n");
            // Else return
            return evaluate_integral;
        }

    } // namespace midpoint_rule
} // namespace numerical_methods

/**
 * \brief A function f(x) that will be used to test the method
 * @param x The independent variable xi
 * @returns the value of the dependent variable yi = f(xi)
*/
double f(double x){
    return std::sqrt(x) + std::log(x);
}
/** @brief Another test function */
double g(double x){
    return std::exp(-x) * (4 - std::pow(x, 2));
}
/** @brief Another test function */
double k(double x){
    return std::sqrt(2*std::pow(x, 3)+3);
}
/** @brief Another test function */
double l(double x){
    return x + std::log(2*x+1);
}

/**
 * \brief Self-test implementations
 * @param N is the number of intervals
 * @param h is the step
 * @param a is x0
 * @param b is the end of the interval
 * @param used_argv_parameters is 'true' if argv parameters are given and 'false' if not
*/
static void test(int N, double h, double a,double b, bool used_argv_parameters){
    // Call midpoint() for each of the test functions f, g, k, l
    // Assert with two decimal point precision
    double result_f = numerical_methods::midpoint_rule::midpoint(N, h, a, f);
    assert((used_argv_parameters || (result_f >= 4.09 && result_f <= 4.10)) && "The result of f(x) is wrong");
    std::cout << "The result of integral f(x) on interval [" << a << ", " << b << "] is equal to: " << result_f << std::endl;

    double result_g = numerical_methods::midpoint_rule::midpoint(N, h, a, g);
    assert((used_argv_parameters || (result_g >= 0.27 && result_g <= 0.28)) && "The result of g(x) is wrong");
    std::cout << "The result of integral g(x) on interval [" << a << ", " << b << "] is equal to: " << result_g << std::endl;

    double result_k = numerical_methods::midpoint_rule::midpoint(N, h, a, k);
    assert((used_argv_parameters || (result_k >= 9.06 && result_k <= 9.07)) && "The result of k(x) is wrong");
    std::cout << "The result of integral k(x) on interval [" << a << ", " << b << "] is equal to: " << result_k << std::endl;

    double result_l = numerical_methods::midpoint_rule::midpoint(N, h, a, l);
    assert((used_argv_parameters || (result_l >= 7.16 && result_l <= 7.17)) && "The result of l(x) is wrong");
    std::cout << "The result of integral l(x) on interval [" << a << ", " << b << "] is equal to: " << result_l << std::endl;

}

/** main function */
int main(int argc, char** argv){
    int N = 16; /// Number of intervals to divide the integration interval. MUST BE EVEN
    double a = 1, b = 3; /// Starting and ending point of the integration in the real axis
    double h; /// Step, calculated by a, b and N

    bool used_argv_parameters = false; // If argv parameters are used then the assert must be omitted for the tst cases

    // Get user input (by the command line parameters or the console after displaying messages)
    if(argc == 4){
        N = std::atoi(argv[1]);
        a = (double) std::atof(argv[2]);
        b = (double) std::atof(argv[3]);
        // Check if a<b else abort
        assert(a < b && "a has to be less than b");
        assert(N > 0 && "N has to be > 0");
        if(N<4 || a!=1 || b!=3) used_argv_parameters = true;
        std::cout << "You selected N=" << N << ", a=" << a << ", b=" << b << std::endl;
    }
    else
        std::cout << "Default N=" << N << ", a=" << a << ", b=" << b << std::endl;

    // Find the step
    h = (b-a)/N;

    test(N, h, a, b, used_argv_parameters); /// run self-test implementations

    return 0;
}
