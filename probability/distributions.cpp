/**
 * \file
 * \brief Implementation of Discrete & Continuous Distributions
 * \author [Tuan Ho](https://github.com/ttuanho)
 * \note The implementation is based on [this
 * cheatsheet](https://web.cs.elte.hu/~mesti/valszam/kepletek)
 * \todo
 * <ul>
 *  <li>
 *       Adding Gaussian distribution
 *  </li>
 *  <li>
 *       Adding mean and variance function for each distribution
 *  </li>
 *  <li>
 *       Adding cdf function of Normal distribution
 *  </li>
 * </ul>
 */

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES

constexpr double E = 2.71828182845904523536;

using ll = int64_t;

// Find the greatest common divisor
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

namespace Util {
/** Computes n choose r
 * \param [in] n
 * \param [in] r
 * \returns \f$\displaystyle {n\choose r} =
 * \frac{n!}{r!(n-r)!} = \frac{n\times(n-1)\times(n-2)\times\cdots(n-r)}{r!}
 * \f$
 * \note Improvised from this [code
 * snippet](https://www.geeksforgeeks.org/program-to-calculate-the-value-of-ncr-efficiently/)
 */
ll nCr(int n, int r) {
    if (r == 0) {
        return n;
    } else if (n == 0) {
        return 1;
    }
    ll p = 1, k = 1;
    if (n - r < r) {
        r = n - r;
    }

    if (r != 0) {
        while (r) {
            p *= n;
            k *= r;
            ll m = gcd(p, k);
            assert(m >= 1);
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
 * Compute factorial of a given number
 */
double factorial(double x) {
    if (x <= 0) {
        return 1;
    }

    double x_fact = x;
    for (int i = x - 1; i > 0; i--) {
        x_fact *= i;
    }
    return x_fact;
}
}  // namespace Util

namespace Distribution {

/**
 * \brief [Binomial
 * distribution](https://en.wikipedia.org/wiki/Binomial_distribution) \details
 * \note improvised from binomial_dist.cpp
 */
namespace Binom {
/**
 * \details The ***Binomial distribution*** \f$B(n, p)\f$ for \f$n \in N\f$
 * has the mass function
 * \f$B(n,p,k)=\binom{n}{k}p^k(1-p)^{n-k} \text{ where } k=0,1,\cdots, n.\f$
 */
double pmd(double p, ll n, ll k) {
    return static_cast<double>(Util::nCr(n, k)) *
           std::pow(p, static_cast<double>(k)) *
           std::pow(1 - p, static_cast<double>(n) - k);
}
/**
 * \details Probability of choosing no more than \f$k\f$ from \f$n\f$
 * in each of time, the probability of choosing the wanted is \f$p\f$.
*/
double cdf(double p, ll n, ll k) {
    double ans = 0;
    for (auto i = 0; i <= k; i++) {
        ans += static_cast<double>(Util::nCr(n, i)) *
               std::pow(p, static_cast<double>(i)) *
               std::pow(1 - p, static_cast<double>(n) - i);
    }
    return ans;
}
}  // namespace Binom

/**
 * \brief [Uniform
 * distribution](https://en.wikipedia.org/wiki/Uniform_distribution_(continuous))
 * \details The distribution describes an experiment where there is an
 * arbitrary outcome that lies between certain bounds.
 */
namespace Uniform {

/**
 * \details A random variable \f$X\f$ is said to be *uniformly distributed*
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
namespace Normal {
/**
 * \details The continuous random variable \f$X\f$ has ***normal
 * distribution*** \f$N(\mu ,\sigma ^2)\f$ if it has probability density
 * 
 * \f$\phi(x)=\frac{1}{\sqrt{2\pi\sigma^2}}e^{-\frac{1}{2}(\frac{x-\mu}{\sigma})^2}\text{
 * where }-\infty <x<\infty.\f$
 *
 * \param x calculated point
 * \param mean mean
 * \param var variance
 *
*/
double pdf(double x, double mean, double var) {
    double ans = 0;
    return 1 / std::sqrt(2 * std::pow(mean, 2) * M_PI) *
            std::exp(-1/2*std::pow((x-mean)/var,2));
}
double cdf(double x) { return 0; }
}  // namespace Normal

/**
 * \brief [Poission
 * distribution](https://en.wikipedia.org/wiki/Poission_distribution) \details
 * \note improvised from poisson_dist.cpp
 */
namespace Poiss {
/**
 * \details A discrete random variable \f$X\f$ is said to have a Poisson
 * distribution with parameter \f$\lambda >0\f$, if, for \f$k = 0, 1, 2,\cdots\f$, the
 * probability mass function of \f$X\f$ is given by:
 * 
 * \f$
 * f(k,\lambda)=Pr(X=k)=\frac{\lambda^ke^{-\lambda}}{k!}.
 * \f$
*/
double pmd(double k, double lambda) { return std::pow(lambda, k) * std::exp(-lambda) / Util::factorial(k) ; }
}  // namespace Poiss

/**
 * \brief [Exponential
 * distribution](https://en.wikipedia.org/wiki/Exponential_distribution)
 * \details the probability distribution of the time between events in a Poisson
 * point process, i.e., a process in which events occur continuously and
 * independently at a constant average rate
 */
namespace Exp {
/**
 * \details A random variable \f$X\f$ is said to be an ***Exponential random
 * variable*** with parameter \f$\mu(\mu>0)\f$ (\f$X\sim Exp(\mu)\f$) if its probability
 * density function is given by

 * \f$
 * f(x)=\begin{cases}
 * \frac{1}{\mu}e^{-\frac{x}{\mu}}\text{ if }x\geq 0\\
 * 0\quad\text{otherwise}
 * \end{cases}
 * \f$
 * 
 * \param [in] lambda rate parameter
 * \param [in] x considered point
 *
*/
double cdf(double x, double lambda) { return 1 - std::exp(-lambda * x); }
/*
 * \details The cdf of an exponential distribution is
 * \f$
 * F(x)=
 * \begin{cases}
 *   0&\text{ if }x<0\\
 *   1-e^{-\frac{x}{\mu}}&\text{ if }x\geq 0
 * \end{cases}
 * \f$
*/
double pdf(double x, double lambda) {
    double ans = (x >= 0) ? lambda * std::exp(-lambda * x) : 0;    
    return ans;
}
}  // namespace Exp

namespace Gauss {}  // namespace Gauss
}  // namespace Distribution
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
              << " in X ~ U(" << sig << ","
              << var << "), then" << std::endl;
    std::cout << "cdf(x) = " << Distribution::Uniform::cdf(x, alpha, beta)
              << std::endl;
    std::cout << "pdf(x) = " << Distribution::Uniform::pdf(x, alpha, beta)
              << std::endl;
    std::cout << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "      Example of Binomial Distribution" << std::endl;
    std::cout << std::endl;
    double p = 0.5;
    double k = 5, n = 20;
    std::cout << "Given p=" << p << ", chosing k=" << k <<" and X  ~ B(" << n << "," << p << "), then"
              << std::endl;
    std::cout << "cdf(p,n,k) = " << Distribution::Binom::cdf(p, n, k)
              << std::endl;
    std::cout << "pmd(p, n, k) = " << Distribution::Binom::pmd(p, n, k);
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "      Example of Exponential Distribution" << std::endl;
    std::cout << std::endl;
    double lambda = 0.5;
    std::cout << "Given x=" << x<<", lambda = "<< lambda << ", with X ~ Exp(" << lambda << "), "<< std::endl;
    std::cout << "cdf(x, lambda) = " << Distribution::Exp::cdf(x, lambda)
              << std::endl;
    std::cout << "pdf(x, lambda) = " << Distribution::Exp::pdf(x, lambda)
              << std::endl;
    std::cout << std::endl;

    return 0;
}
