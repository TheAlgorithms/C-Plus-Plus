/**
 * @file
 * @brief Demonstration of 1D optimization using the Armijo backtracking
 * line search method (adaptive step size gradient descent).
 *
 * @author [Frinad Kandoriya](https://github.com/frinad8555)
 * @see https://en.wikipedia.org/wiki/Backtracking_line_search
 */

#include <cassert>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>

#define EPSILON 1e-7 // convergence tolerance

/**
 * @brief Perform Armijo backtracking line search for a 1D function
 *
 * The method adaptively reduces the step size until the Armijo condition is satisfied:
 * \f[
 * f(x + \alpha d) \le f(x) + c \alpha f'(x)d
 * \f]
 *
 * @param f the function to minimize
 * @param df first derivative of f
 * @param xk current position
 * @param dk descent direction
 * @param c Armijo constant (usually 1e-4)
 * @param tau backtracking reduction factor (usually 0.5)
 * @param alpha_init initial trial step size
 * @return acceptable step length satisfying Armijo condition
 */

double armijo_backtrack(const std::function<double(double)> &f,
                        const std::function<double(double)> &df, double xk,
                        double dk, double c = 1e-4, double tau = 0.5,
                        double alpha_init = 1.0) {
    double alpha = alpha_init;
    double fxk = f(xk);
    double grad_fxk = df(xk);

    while (f(xk + alpha * dk) > fxk + c * alpha * grad_fxk * dk) {
        alpha *= tau;  // reduce step size
    }

    return alpha;
}

/**
 * @brief Perform gradient descent using Armijo line search on a 1D function.
 *
 * @param f target function
 * @param df first derivative of f
 * @param x0 initial guess
 * @param max_iter maximum number of iterations
 * @return estimated minimum point
 */

double gradient_descent_armijo(const std::function<double(double)> &f,
                               const std::function<double(double)> &df,
                               double x0, uint32_t max_iter = 50) {
    double x = x0;
    double grad = df(x);
    double d = -grad;
    int iter = 0;

    while (std::abs(grad) > EPSILON && iter < max_iter) {
        double alpha = armijo_backtrack(f, df, x, d);
        x += alpha * d;
        grad = df(x);
        d = -grad;
        std::cout << "Iter " << iter << ": x = " << x << ", f(x) = " << f(x)
                  << ", alpha = " << alpha << "\n";
        iter++;
    }

    std::cout << "Converged in " << iter << " iterations.\n";
    return x;
}

/**
 * @brief Test case 1: minimize f(x) = (x - 2)^2
 * \n Expected minimum at x = 2
 */

void test1() {
    std::cout << "Test 1... ";

    std::function<double(double)> f = [](double x) { return pow(x - 2.0, 2); };
    std::function<double(double)> df = [](double x) { return 2.0 * (x - 2.0); };

    double xmin = gradient_descent_armijo(f, df, 0.0);

    std::cout << "Result = " << xmin << "\n";
    assert(std::abs(xmin - 2.0) < 1e-5);
    std::cout << "Passed.\n";
    std::cout << "\n";
}

/**
 * @brief Test case 2: minimize f(x) = (x + 3)^2 + 1
 * \n Expected minimum at x = -3
 */

void test2() {
    std::cout << "Test 2... ";

    std::function<double(double)> f = [](double x) { return pow(x + 3.0, 2) + 1; };
    std::function<double(double)> df = [](double x) { return 2.0 * (x + 3.0); };

    double xmin = gradient_descent_armijo(f, df, 5.0);

    std::cout << "Result = " << xmin << "\n";
    assert(std::abs(xmin + 3.0) < 1e-5);
    std::cout << "Passed.\n";
    std::cout << "\n";
}

/**
 * @brief Test case 3: minimize non-convex f(x) = x^4 - 3x^3 + 2
 * \n Expected local minimum near x ≈ 2.25
 */

void test3() {
    std::cout << "Test 3... ";

    std::function<double(double)> f = [](double x) {
        return pow(x, 4) - 3 * pow(x, 3) + 2;
    };
    std::function<double(double)> df = [](double x) {
        return 4 * pow(x, 3) - 9 * pow(x, 2);
    };

    double xmin = gradient_descent_armijo(f, df, 1.0);

    std::cout << "Result = " << xmin << "\n";
    std::cout << "Passed.\n";
    std::cout << "\n";
}

/** @brief Main function */
int main() {
    std::cout.precision(9);
    std::cout << "Armijo Backtracking Line Search Example\n";
    std::cout << "Machine epsilon: " << EPSILON << "\n\n";

    test1();
    test2();
    test3();

    return 0;
}
