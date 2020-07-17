/**
 * \file
 * \brief Find extrema of a univariate real function in a given interval using
 * [golden section search
 * algorithm](https://en.wikipedia.org/wiki/Golden-section_search).
 *
 * \see brent_method_extrema.cpp
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#define _USE_MATH_DEFINES  //< required for MS Visual C++
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>

#define EPSILON 1e-7  ///< solution accuracy limit

/**
 * @brief Get the minima of a function in the given interval. To get the maxima,
 * simply negate the function. The golden ratio used here is:\f[
 * k=\frac{3-\sqrt{5}}{2} \approx 0.381966\ldots\f]
 *
 * @param f function to get minima for
 * @param lim_a lower limit of search window
 * @param lim_b upper limit of search window
 * @return local minima found in the interval
 */
double get_minima(const std::function<double(double)> &f, double lim_a,
                  double lim_b) {
    uint32_t iters = 0;
    double c, d;
    double prev_mean, mean = std::numeric_limits<double>::infinity();

    // golden ratio value
    const double M_GOLDEN_RATIO = (1.f + std::sqrt(5.f)) / 2.f;

    // ensure that lim_a < lim_b
    if (lim_a > lim_b) {
        std::swap(lim_a, lim_b);
    } else if (std::abs(lim_a - lim_b) <= EPSILON) {
        std::cerr << "Search range must be greater than " << EPSILON << "\n";
        return lim_a;
    }

    do {
        prev_mean = mean;

        // compute the section ratio width
        double ratio = (lim_b - lim_a) / M_GOLDEN_RATIO;
        c = lim_b - ratio;  // right-side section start
        d = lim_a + ratio;  // left-side section end

        if (f(c) < f(d)) {
            // select left section
            lim_b = d;
        } else {
            // selct right section
            lim_a = c;
        }

        mean = (lim_a + lim_b) / 2.f;
        iters++;

        // continue till the interval width is greater than sqrt(system epsilon)
    } while (std::abs(lim_a - lim_b) > EPSILON);

    std::cout << " (iters: " << iters << ") ";
    return prev_mean;
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

    double minima = get_minima(func, -4, 12);

    std::cout << minima << " (" << M_PI << ")...";

    assert(std::abs(minima - M_PI) < EPSILON);
    std::cout << "passed\n";
}

/** Main function */
int main() {
    std::cout.precision(9);

    std::cout << "Computations performed with machine epsilon: " << EPSILON
              << "\n";

    test1();
    test2();
    test3();

    return 0;
}
