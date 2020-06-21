/**
 * \file
 * \brief Find extrema of a univariate real function in a given interval using
 * [golden section search
 * algorithm](https://en.wikipedia.org/wiki/Golden-section_search).
 *
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#define _USE_MATH_DEFINES  //< required for MS Visual C++
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>

#define EPSILON 1e-7  ///< solution accuracy limit
#define M_GOLDEN_RATIO \
    static_cast<double>(1.618033988749894848204586834)  ///< golden ratio value

/**
 * @brief Get the minima of a function in the given interval. To get the maxima,
 * simply negate the function.
 *
 * @param f function to get minima for
 * @param lim_a lower limit of search window
 * @param lim_b upper limit of search window
 * @return local minima found in the interval
 */
double get_minima(const std::function<double(double)> &f, double lim_a,
                  double lim_b) {
    double c, d;
    double prev_mean, mean = std::numeric_limits<double>::infinity();

    // ensure that lim_a < lim_b
    if (lim_a > lim_b) {
        std::swap(lim_a, lim_b);
    } else if (std::abs(lim_a - lim_b) <= EPSILON) {
        std::cerr << "Search range must be greater than " << EPSILON << "\n";
        return lim_a;
    }

    do {
        prev_mean = mean;

        c = lim_b - (lim_b - lim_a) / M_GOLDEN_RATIO;
        d = lim_a + (lim_b - lim_a) / M_GOLDEN_RATIO;

        if (f(c) < f(d)) {
            lim_b = d;
        } else {
            lim_a = c;
        }

        mean = (lim_a + lim_b) * 0.5f;
    } while (std::abs(mean - prev_mean) > EPSILON);

    return mean;
}

/**
 * @brief Test function to find minima for the function
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

    double minima = get_minima(f1, 1, 5);

    std::cout << minima << "...";

    assert(std::abs(minima - 2) < EPSILON);
    std::cout << "passed\n";
}

/**
 * @brief Test function to find *maxima* for the function
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

    double minima = get_minima(func, -2, 10);

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

    double minima = get_minima(func, 0, 12);

    std::cout << minima << " (" << M_PI << ")...";

    assert(std::abs(minima - M_PI) < EPSILON);
    std::cout << "passed\n";
}

/** Main function */
int main() {
    std::cout.precision(18);

    test1();
    test2();
    test3();

    return 0;
}
