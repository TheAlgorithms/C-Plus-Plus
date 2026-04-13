/**
 * @file
 * @brief Compute pi using Machin-like arctan formula.
 * @details
 * Implements Machin formula:
 * pi/4 = 4 arctan(1/5) - arctan(1/239)
 *
 * Uses the power series of arctan(x).
 * @see https://en.wikipedia.org/wiki/Machin-like_formula
 */

#include <cmath>
#include <limits>
#include <cassert>
#include <iostream>
#include <iomanip>

/**
 * @namespace math
 * @brief Math algorithms
 */
namespace math {
/**
 * @namespace pi_approximation
 * @brief Functions for approximating pi
 */
namespace pi_approximation {
/**
 * @brief Computes pi using Machin's forumla
 *
 * @details
 * Approximates pi as a long double. The approximation
 * ends either after the precision of a long double is no
 * long sufficient, or after computing the 100th term of
 * power series of arctan.
 *
 * @returns an approximation of pi
 */
long double pi_machin() {
    bool coeff_sign{false}; // false: -1, true: 1
    // Coefficient in the power series
    long double coeff{0.0};

    // Values of the first and second arctans
    // in the Machin formula. Calculate these first
    // and then combine everything
    long double arctan1{0.0};
    long double arctan2{0.0};

    // Constants for the machin-formula. Squares are used
    // as power series of arctan has uneven powers.
    constexpr long double one_fifth_sq{0.2L * 0.2L};
    constexpr long double one_239_sq{1.0L / (239.0L * 239.0L)};

    // Record uneven powers of x.
    // Avoids having to compute powers from scratch
    // with a std::pow style function each iteration.
    long double pow1{0.2L};
    long double pow2{1.0L / 239.0L};

    // Use for checking whether or not
    // calculations are still relevant.
    constexpr long double eps = std::numeric_limits<long double>::epsilon();

    // Upper-bound: power of 10 rules.
    // With long double precision, convergence is much
    // faster than 100 iterations.
    for (unsigned int i = 0; i < 100; ++i) {
        coeff_sign = !coeff_sign;

        coeff = 1.0 / (2*i + 1);
        coeff = coeff_sign ? coeff : -coeff;

        long double term1 = coeff * pow1;
        long double term2 = coeff * pow2;

        if (
            std::abs(term1) < eps * std::abs(arctan1)
            && std::abs(term2) < eps * std::abs(arctan2)
        ) { break; }

        arctan1 += term1;
        arctan2 += term2;

        pow1 *= one_fifth_sq;
        pow2 *= one_239_sq;
    }

    return 4.0 * (4.0 * arctan1 - arctan2);
}
}
}

/**
 * @brief Self-test implementation
 * @returns `void`
 */
static void test() {
    constexpr long double pi_ref{
        3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647L
    };

    long double tolerance{
        1000 * std::numeric_limits<long double>::epsilon()
        * pi_ref
    };

    long double computed_pi = math::pi_approximation::pi_machin();
    assert(std::abs(computed_pi - pi_ref) < tolerance);

    std::cout << "Successfully computed pi!\n";
    std::cout << "Pi is approximately: ";
    std::cout << std::setprecision(std::numeric_limits<long double>::digits10);
    std::cout << computed_pi << '\n';
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}
