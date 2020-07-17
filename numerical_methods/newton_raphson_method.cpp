/**
 * \file
 * \brief Solve the equation \f$f(x)=0\f$ using [Newton-Raphson
 * method](https://en.wikipedia.org/wiki/Newton%27s_method) for both real and
 * complex solutions
 *
 * The \f$(i+1)^\text{th}\f$ approximation is given by:
 * \f[
 * x_{i+1} = x_i - \frac{f(x_i)}{f'(x_i)}
 * \f]
 *
 * \author [Krishna Vedala](https://github.com/kvedala)
 * \see bisection_method.cpp, false_position.cpp
 */
#include <cmath>
#include <ctime>
#include <iostream>
#include <limits>

constexpr double EPSILON = 1e-10;              ///< system accuracy limit
constexpr int16_t MAX_ITERATIONS = INT16_MAX;  ///< Maximum number of iterations

/** define \f$f(x)\f$ to find root for.
 * Currently defined as:
 * \f[
 * f(x) = x^3 - 4x - 9
 * \f]
 */
static double eq(double i) {
    return (std::pow(i, 3) - (4 * i) - 9);  // original equation
}

/** define the derivative function \f$f'(x)\f$
 * For the current problem, it is:
 * \f[
 * f'(x) = 3x^2 - 4
 * \f]
 */
static double eq_der(double i) {
    return ((3 * std::pow(i, 2)) - 4);  // derivative of equation
}

/** Main function */
int main() {
    std::srand(std::time(nullptr));  // initialize randomizer

    double z = NAN, c = std::rand() % 100, m = NAN, n = NAN;
    int i = 0;

    std::cout << "\nInitial approximation: " << c;

    // start iterations
    for (i = 0; i < MAX_ITERATIONS; i++) {
        m = eq(c);
        n = eq_der(c);

        z = c - (m / n);
        c = z;

        if (std::abs(m) < EPSILON) {  // stoping criteria
            break;
        }
    }

    std::cout << "\n\nRoot: " << z << "\t\tSteps: " << i << std::endl;
    return 0;
}
