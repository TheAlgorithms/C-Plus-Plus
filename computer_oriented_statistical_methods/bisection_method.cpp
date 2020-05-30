/**
 * \file
 * \brief Solve the equation \f$f(x)=0\f$ using [bisection
 * method](https://en.wikipedia.org/wiki/Bisection_method)
 *
 * Given two points \f$a\f$ and \f$b\f$ such that \f$f(a)<0\f$ and
 * \f$f(b)>0\f$, then the \f$(i+1)^\text{th}\f$ approximation is given by: \f[
 * x_{i+1} = \frac{a_i+b_i}{2}
 * \f]
 * For the next iteration, the interval is selected
 * as: \f$[a,x]\f$ if \f$x>0\f$ or \f$[x,b]\f$ if \f$x<0\f$. The Process is
 * continued till a close enough approximation is achieved.
 *
 * \see newton_raphson_method.cpp, false_position.cpp, secant_method.cpp
 */
#include <cmath>
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

/** get the sign of any given number */
template <typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

/** main function */
int main() {
    double a = -1, b = 1, x, z;
    int i;

    // loop to find initial intervals a, b
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        z = eq(a);
        x = eq(b);
        if (sgn(z) == sgn(x)) {  // same signs, increase interval
            b++;
            a--;
        } else {  // if opposite signs, we got our interval
            break;
        }
    }

    std::cout << "\nFirst initial: " << a;
    std::cout << "\nSecond initial: " << b;

    // start iterations
    for (i = 0; i < MAX_ITERATIONS; i++) {
        x = (a + b) / 2;
        z = eq(x);
        std::cout << "\n\nz: " << z << "\t[" << a << " , " << b
                  << " | Bisect: " << x << "]";

        if (z < 0) {
            a = x;
        } else {
            b = x;
        }

        if (std::abs(z) < EPSILON)  // stoping criteria
            break;
    }

    std::cout << "\n\nRoot: " << x << "\t\tSteps: " << i << std::endl;
    return 0;
}
