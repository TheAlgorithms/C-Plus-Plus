/**
 * \file
 * \brief Find real extrema of a univariate real function in a given interval
 * using [Brent's method](https://en.wikipedia.org/wiki/Brent%27s_method).
 *
 * Refer the algorithm discoverer's publication
 * [online](https://maths-people.anu.edu.au/~brent/pd/rpb011i.pdf) and also
 * associated book:
 * > R. P. Brent, Algorithms for Minimization without
 * > Derivatives, Prentice-Hall, Englewood Cliffs, New Jersey, 1973
 *
 * \see golden_search_extrema.cpp
 *
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#define _USE_MATH_DEFINES  ///< required for MS Visual C++
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>

#define EPSILON \
    std::sqrt(  \
        std::numeric_limits<double>::epsilon())  ///< system accuracy limit

/**
 * @brief Get the real root of a function in the given interval.
 *
 * @param f function to get root for
 * @param lim_a lower limit of search window
 * @param lim_b upper limit of search window
 * @return root found in the interval
 */
double get_minima(const std::function<double(double)> &f, double lim_a,
                  double lim_b) {
    uint32_t iters = 0;

    if (lim_a > lim_b) {
        std::swap(lim_a, lim_b);
    } else if (std::abs(lim_a - lim_b) <= EPSILON) {
        std::cerr << "Search range must be greater than " << EPSILON << "\n";
        return lim_a;
    }

    // golden ratio value
    const double M_GOLDEN_RATIO = (3.f - std::sqrt(5.f)) / 2.f;

    double v = lim_a + M_GOLDEN_RATIO * (lim_b - lim_a);
    double u, w = v, x = v;
    double fu, fv = f(v);
    double fw = fv, fx = fv;

    double mid_point = (lim_a + lim_b) / 2.f;
    double p = 0, q = 0, r = 0;

    double d, e = 0;
    double tolerance, tolerance2;

    do {
        mid_point = (lim_a + lim_b) / 2.f;
        tolerance = EPSILON * std::abs(x);
        tolerance2 = 2 * tolerance;

        if (std::abs(e) > tolerance2) {
            // fit parabola
            r = (x - w) * (fx - fv);
            q = (x - v) * (fx - fw);
            p = (x - v) * q - (x - w) * r;
            q = 2.f * (q - r);
            if (q > 0)
                p = -p;
            else
                q = -q;
            r = e;
            e = d;
        }

        if (std::abs(p) < std::abs(0.5 * q * r) && p < q * (lim_b - x)) {
            // parabolic interpolation step
            d = p / q;
            u = x + d;
            if (u - lim_a < tolerance2 || lim_b - u < tolerance2)
                d = x < mid_point ? tolerance : -tolerance;
        } else {
            // golden section interpolation step
            e = (x < mid_point ? lim_b : lim_a) - x;
            d = M_GOLDEN_RATIO * e;
        }

        // evaluate not too close to x
        if (std::abs(d) >= tolerance)
            u = d;
        else if (d > 0)
            u = tolerance;
        else
            u = -tolerance;
        u += x;
        fu = f(u);

        // update variables
        if (fu <= fx) {
            if (u < x)
                lim_b = x;
            else
                lim_a = x;
            v = w;
            fv = fw;
            w = x;
            fw = fx;
            x = u;
            fx = fu;
        } else {
            if (u < x)
                lim_a = u;
            else
                lim_b = u;
            if (fu <= fw || x == w) {
                v = w;
                fv = fw;
                w = u;
                fw = fu;
            } else if (fu <= fv || v == x || v == w) {
                v = u;
                fv = fu;
            }
        }

        iters++;
    } while (std::abs(x - mid_point) > (tolerance - (lim_b - lim_a) / 2.f));

    std::cout << " (iters: " << iters << ") ";

    return x;
}

/**
 * @brief Test function to find root for the function
 * \f$f(x)= (x-2)^2\f$
 * in the interval \f$[1,5]\f$
 * \n Expected result = 2
 */
void test1() {
    // define the function to minimize as a lambda function
    std::function<double(double)> f1 = [](double x) {
        return (x - 2) * (x - 2);
    };

    std::cout << "Test 1.... ";

    double minima = get_minima(f1, -1, 5);

    std::cout << minima << "...";

    assert(std::abs(minima - 2) < EPSILON);
    std::cout << "passed\n";
}

/**
 * @brief Test function to find root for the function
 * \f$f(x)= x^{\frac{1}{x}}\f$
 * in the interval \f$[-2,10]\f$
 * \n Expected result: \f$e\approx 2.71828182845904509\f$
 */
void test2() {
    // define the function to maximize as a lambda function
    // since we are maximixing, we negated the function return value
    std::function<double(double)> func = [](double x) {
        return -std::pow(x, 1.f / x);
    };

    std::cout << "Test 2.... ";

    double minima = get_minima(func, -2, 5);

    std::cout << minima << " (" << M_E << ")...";

    assert(std::abs(minima - M_E) < EPSILON);
    std::cout << "passed\n";
}

/**
 * @brief Test function to find *maxima* for the function
 * \f$f(x)= \cos x\f$
 * in the interval \f$[0,12]\f$
 * \n Expected result: \f$\pi\approx 3.14159265358979312\f$
 */
void test3() {
    // define the function to maximize as a lambda function
    // since we are maximixing, we negated the function return value
    std::function<double(double)> func = [](double x) { return std::cos(x); };

    std::cout << "Test 3.... ";

    double minima = get_minima(func, -4, 12);

    std::cout << minima << " (" << M_PI << ")...";

    assert(std::abs(minima - M_PI) < EPSILON);
    std::cout << "passed\n";
}

/** Main function */
int main() {
    std::cout.precision(18);

    std::cout << "Computations performed with machine epsilon: " << EPSILON
              << "\n";

    test1();
    test2();
    test3();

    return 0;
}
