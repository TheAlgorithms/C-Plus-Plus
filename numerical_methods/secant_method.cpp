/**
 * \file
 * \brief Solve the equation \f$f(x)=0\f$ using
 * [Secant Method](https://en.wikipedia.org/wiki/Secant_method)
 *
 * The example function \f$f(x)\f$ looks like this:
 * \f[
 * x^4 - 29 = 0
 * \f]
 *
 * \author [Fatih Küçükkarakurt](https://github.com/fkkarakurt)
 */

// Secant Method for the root of f(x)
// Analytically the solution is x^4-29 = 0
// => x = 29^(1/4) = 2,3205957871060836757951626724362...
#include <cmath>
#include <iomanip>
#include <iostream>

double f(double x) { return x * x * x * x - 29.0; } // The Function f(x)

/** Main Function */
int main() {
    double x1 = 5, x0 = 4, tolerance = 1.0E-12; // Points and Tolerance Value
    std::cout << std::setprecision(20) << std::fixed; // Set Precision

    /** Start Secant Method */
    do {
        double error = (x1 - x0) / (f(x1) - f(x0)) * f(x1); // Estimate the error
        std::cout << "Root = " << x1 << std::setw(5) << " Error = " << error << std::endl;

        if (abs(error) < tolerance)
            break;         // Terminate if the tolerance is satisfied
        x0 = x1;         // Improve x0
        x1 = x1 - error; // Improve x1
    } while (1);
}
