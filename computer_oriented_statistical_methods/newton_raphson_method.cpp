/**
 * \file
 * \brief Solve the equation \f$f(x)=0\f$ using [Newton-Raphson
 * method](https://en.wikipedia.org/wiki/Newton%27s_method)
 *
 * The \f$(i+1)^\text{th}\f$ approximation is given by:
 * \f[
 * x_{i+1} = x_i - \frac{f(x_i)}{f'(x_i)}
 * \f]
 *
 * \see bisection_method.cpp, false_position.cpp
 */
#include <cmath>
#include <ctime>
#include <iostream>
#include <limits>

#define EPSILON \
    1e-6  // std::numeric_limits<double>::epsilon()  ///< system accuracy limit
#define MAX_ITERATIONS 50000  ///< Maximum number of iterations to check

/** define \f$f(x)\f$ to find root for
 */
static double eq(double i) {
    return (std::pow(i, 3) - (4 * i) - 9);  // original equation
}

/** define the derivative function \f$f'(x)\f$
 */
static double eq_der(double i) {
    return ((3 * std::pow(i, 2)) - 4);  // derivative of equation
}

/** Main function */
int main() {
    std::srand(std::time(nullptr));  // initialize randomizer

    double z, c = std::rand() % 100, m, n;
    int i;

    std::cout << "\nInitial approximation: " << c;

    // start iterations
    for (i = 0; i < MAX_ITERATIONS; i++) {
        m = eq(c);
        n = eq_der(c);

        z = c - (m / n);
        c = z;

        if (std::abs(m) < EPSILON)  // stoping criteria
            break;
    }

    std::cout << "\n\nRoot: " << z << "\t\tSteps: " << i << std::endl;
    return 0;
}
