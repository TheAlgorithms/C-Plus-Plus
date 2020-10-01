/**
 * \file
 * \brief Implementation of Discrete & Continuous Distributions
 * \author [Tuan Ho](https://github.com/ttuanho)
 * \note
 * <ul>
 * </ul>
 * \todo
 * <ul>
 *  <li>
 *       Adding Gaussian distribution
 *  </li>
 * </ul>
 */

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

using ll = int64_t;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

namespace Distribution {

/**
 * \brief [Binomial
 * distribution](https://en.wikipedia.org/wiki/Binomial_distribution) \details
 * \note improvised from binomial_dist.cpp
 */
namespace Binom {
double pmd(double p, double n, double k) { return 0; }
double cdf(double p, double n, double k) { return 0; }
}  // namespace Binom

/**
 * \brief [Uniform
 * distribution](https://en.wikipedia.org/wiki/Uniform_distribution_(continuous))
 * \details The distribution describes an experiment where there is an
 * arbitrary outcome that lies between certain bounds.
 */
namespace Uniform {

/**
 * \details A random variable \f$X\f$ is said to be ***uniformly distributed***
 * over an interval \f$[\alpha,\beta]\f$ if its probability density function is
 * given by
 *
 *
 * \f$
 * f(x)=\begin{cases}
 * \frac{1}{\beta - \alpha}\text{ if }x\in [\alpha,\beta] \\
 * 0\quad \text{otherwise}
 * \end{cases}
 * \f$
 * \param x the outcome
 * \param alpha min bound
 * \param beta max bound
 */
double pdf(double x, double alpha, double beta) {
    assert(beta > alpha);
    if (alpha <= x && x <= beta) {
        return 1 / (beta - alpha);
    } else {
        return 0;
    }
}

/**
 * \details The cdf for a uniform distribution is given by
 * \f$
 * F(x)=
 * \begin{cases}
 *   0 &\text{ if }x<\alpha\\
 *   \frac{x-\alpha}{\beta-\alpha} &\text{ if }\alpha \leq x\leq \beta\\
 *   1 &\text{ if }x>\beta
 * \end{cases}
 * \f$
 * \param x the outcome
 * \param alpha min bound
 * \param beta max bound
 */

double cdf(double x, double alpha, double beta) {
    assert(beta > alpha);
    if (x < alpha) {
        return 0;
    } else if (x > beta) {
        return 1;
    } else {
        return (x - alpha) / (beta - alpha);
    }
}
}  // namespace Uniform
/**
 * \brief [Normal
 * distribution](https://en.wikipedia.org/wiki/Normal_distribution) \details
 */
namespace Normal {}  // namespace Normal

/**
 * \brief [Poission
 * distribution](https://en.wikipedia.org/wiki/Poission_distribution) \details
 * \note improvised from poisson_dist.cpp
 */
namespace Poiss {}  // namespace Poiss

/**
 * \brief [Exponential
 * distribution](https://en.wikipedia.org/wiki/Exponential_distribution) \details
 */
namespace Exp {
void cdf(double x) {}
}  // namespace Exp

namespace Gauss {} // namespace Guass
}  // namespace Distribution

/** Computes n choose r
 * \param [in] n
 * \param [in] r
 * \returns \f$\displaystyle {n\choose r} =
 * \frac{n!}{r!(n-r)!} = \frac{n\times(n-1)\times(n-2)\times\cdots(n-r)}{r!}
 * \f$
 * \see [original
 * version](https://www.geeksforgeeks.org/program-to-calculate-the-value-of-ncr-efficiently/)
 */
ll nCr(int n, int r) {
    ll p = 1, k = 1;
    if (n - r < r) {
        r = n - r;
    }

    if (r != 0) {
        while (r) {
            p *= n;
            k *= r;
            ll m = gcd(p, k);
            p /= m;
            k /= m;
            n--;
            r--;
        }
    } else {
        p = 1;
    }
    return p;
}

/**
 * Main function.
 * Exit and return 0.
 */
int main() {
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "      Example of Uniform Distribution" << std::endl;
    std::cout << std::endl;
    double sig = 0, var = 23;
    double alpha = 2, beta = 18;
    double x = 12;
    std::cout << "Given x=" << x
              << " in X that is uniformly distributed with U(" << sig << ","
              << var << "), then" << std::endl;
    std::cout << "cdf = " << Distribution::Uniform::cdf(x, alpha, beta)
              << std::endl;
    std::cout << "pdf = " << Distribution::Uniform::pdf(x, alpha, beta)
              << std::endl;
    std::cout << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "      Example of Distribution" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    return 0;
}
