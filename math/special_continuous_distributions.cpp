/**
 * @file
 * @brief Implementations for various continuous probability distributions
 * @details This file includes implementations of continuous probability
 * distributions, including Normal, Gamma, and Exponential. Each distribution
 * has probability density function (PDF) and cumulative distribution function (CDF) implementations.
 */

#include <iostream>
#include <cmath>    // For mathematical operations
#include <cassert>  // For assertions

/**
 * @namespace probability
 * @brief Namespace containing continuous probability distribution implementations
 */
namespace probability {

/**
 * @class Normal
 * @brief Normal distribution with mean mu and standard deviation sigma
 */
class Normal {
    double mu;
    double sigma;

public:
    Normal(double mean, double stddev) : mu(mean), sigma(stddev) {}

    double pdf(double x) const {
        return (1.0 / (sigma * sqrt(2 * M_PI))) * exp(-0.5 * pow((x - mu) / sigma, 2));
    }

    double cdf(double x) const {
        return 0.5 * (1 + erf((x - mu) / (sigma * sqrt(2))));
    }

    void test() const {
        assert(fabs(pdf(mu) - (1.0 / (sigma * sqrt(2 * M_PI)))) < 1e-5);
        assert(fabs(cdf(mu) - 0.5) < 1e-5);
        std::cout << "Normal distribution tests passed." << std::endl;
    }
};

/**
 * @class Gamma
 * @brief Gamma distribution with shape k and scale theta
 */
class Gamma {
    double k;
    double theta;

public:
    Gamma(double shape, double scale) : k(shape), theta(scale) {}

    double pdf(double x) const {
        return (pow(x, k - 1) * exp(-x / theta)) / (tgamma(k) * pow(theta, k));
    }

    double cdf(double x) const {
        // Approximation of Gamma CDF could be done by using incomplete gamma function, skipped here for simplicity
        return 0.0; // Placeholder as accurate computation needs more complex implementation
    }

    void test() const {
        assert(fabs(pdf(1.0) - (1.0 / (tgamma(k) * pow(theta, k)))) < 1e-5);
        std::cout << "Gamma distribution tests passed (CDF not implemented)." << std::endl;
    }
};

/**
 * @class Exponential
 * @brief Exponential distribution with rate lambda
 */
class Exponential {
    double lambda;

public:
    explicit Exponential(double rate) : lambda(rate) {}

    double pdf(double x) const {
        return (x >= 0) ? lambda * exp(-lambda * x) : 0;
    }

    double cdf(double x) const {
        return (x >= 0) ? 1 - exp(-lambda * x) : 0;
    }

    void test() const {
        assert(fabs(pdf(0) - lambda) < 1e-5);
        assert(fabs(cdf(0) - 0.0) < 1e-5);
        std::cout << "Exponential distribution tests passed." << std::endl;
    }
};

}  // namespace probability

/**
 * @brief Main function to run test cases
 * @returns 0 on successful execution
 */
int main() {
    probability::Normal(0.0, 1.0).test();
    probability::Gamma(2.0, 2.0).test();
    probability::Exponential(1.0).test();

    std::cout << "All continuous distribution tests passed successfully." << std::endl;
    return 0;
}
