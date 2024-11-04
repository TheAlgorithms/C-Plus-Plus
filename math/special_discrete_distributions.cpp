/**
 * @file
 * @brief Implementations for various discrete probability distributions
 * @details This file includes implementations of discrete probability
 * distributions, including Bernoulli, Binomial, Negative Binomial, Poisson,
 * Geometric, and Negative Geometric. Each distribution has probability mass
 * function (PMF) and cumulative distribution function (CDF) implementations.
 * @note This code supports integer input for the trial counts and floating-point
 * input for probabilities.
 */

#include <iostream>
#include <cmath>    // For mathematical operations
#include <cassert>  // For assertions

/**
 * @namespace probability
 * @brief Namespace containing discrete probability distribution implementations
 */
namespace probability {

/**
 * @class Bernoulli
 * @brief Bernoulli distribution with probability of success `p`
 */
class Bernoulli {
    double p;

public:
    explicit Bernoulli(double probability) : p(probability) {}

    double pmf(int k) const {
        return (k == 0) ? 1 - p : (k == 1 ? p : 0);
    }

    double cdf(int k) const {
        return (k < 0) ? 0 : (k < 1 ? 1 - p : 1);
    }
    
    void test() const {
        assert(fabs(pmf(0) - (1 - p)) < 1e-9);
        assert(fabs(pmf(1) - p) < 1e-9);
        assert(fabs(cdf(0) - (1 - p)) < 1e-9);
        assert(fabs(cdf(1) - 1.0) < 1e-9);
        std::cout << "Bernoulli tests passed." << std::endl;
    }
};

/**
 * @class Binomial
 * @brief Binomial distribution for a given number of trials `n` and probability of success `p`
 */
class Binomial {
    int n;
    double p;

    int factorial(int x) const {
        int result = 1;
        for (int i = 2; i <= x; ++i)
            result *= i;
        return result;
    }

    int combination(int n, int k) const {
        return factorial(n) / (factorial(k) * factorial(n - k));
    }

public:
    Binomial(int trials, double probability) : n(trials), p(probability) {}

    double pmf(int k) const {
        return combination(n, k) * pow(p, k) * pow(1 - p, n - k);
    }

    double cdf(int k) const {
        double cumulative = 0;
        for (int i = 0; i <= k; ++i)
            cumulative += pmf(i);
        return cumulative;
    }
    
    void test() const {
        assert(fabs(pmf(2) - 0.3125) < 1e-9); // for n=5, p=0.5, k=2
        assert(fabs(cdf(2) - 0.5) < 1e-9);     // cumulative probability
        std::cout << "Binomial tests passed." << std::endl;
    }
};

/**
 * @class NegativeBinomial
 * @brief Negative Binomial distribution for a given number of successes `r` and probability of success `p`
 */
class NegativeBinomial {
    int r;
    double p;

    int factorial(int x) const {
        int result = 1;
        for (int i = 2; i <= x; ++i)
            result *= i;
        return result;
    }

    int combination(int n, int k) const {
        return factorial(n) / (factorial(k) * factorial(n - k));
    }

public:
    NegativeBinomial(int successes, double probability) : r(successes), p(probability) {}

    double pmf(int k) const {
        return combination(k + r - 1, r - 1) * pow(p, r) * pow(1 - p, k);
    }

    double cdf(int k) const {
        double cumulative = 0;
        for (int i = 0; i <= k; ++i)
            cumulative += pmf(i);
        return cumulative;
    }
    
    void test() const {
        assert(fabs(pmf(3) - 0.08789) < 1e-4); // for r=2, p=0.5, k=3
        assert(fabs(cdf(3) - 0.87891) < 1e-4);
        std::cout << "Negative Binomial tests passed." << std::endl;
    }
};

/**
 * @class Poisson
 * @brief Poisson distribution with average rate of occurrence `lambda`
 */
class Poisson {
    double lambda;

public:
    explicit Poisson(double rate) : lambda(rate) {}

    double pmf(int k) const {
        return pow(lambda, k) * exp(-lambda) / tgamma(k + 1);
    }

    double cdf(int k) const {
        double cumulative = 0;
        for (int i = 0; i <= k; ++i)
            cumulative += pmf(i);
        return cumulative;
    }
    
    void test() const {
        assert(fabs(pmf(2) - 0.18394) < 1e-5); // for lambda=3, k=2
        assert(fabs(cdf(2) - 0.42319) < 1e-5);
        std::cout << "Poisson tests passed." << std::endl;
    }
};

/**
 * @class Geometric
 * @brief Geometric distribution with probability of success `p`
 */
class Geometric {
    double p;

public:
    explicit Geometric(double probability) : p(probability) {}

    double pmf(int k) const {
        return pow(1 - p, k - 1) * p;
    }

    double cdf(int k) const {
        return 1 - pow(1 - p, k);
    }
    
    void test() const {
        assert(fabs(pmf(2) - 0.25) < 1e-5);  // for p=0.5, k=2
        assert(fabs(cdf(2) - 0.75) < 1e-5);
        std::cout << "Geometric tests passed." << std::endl;
    }
};

/**
 * @class NegativeGeometric
 * @brief Negative Geometric distribution with probability of success `p`
 */
class NegativeGeometric {
    double p;

public:
    explicit NegativeGeometric(double probability) : p(probability) {}

    double pmf(int k) const {
        return pow(1 - p, k) * p;
    }

    double cdf(int k) const {
        return 1 - pow(1 - p, k + 1);
    }
    
    void test() const {
        assert(fabs(pmf(2) - 0.125) < 1e-5);  // for p=0.5, k=2
        assert(fabs(cdf(2) - 0.875) < 1e-5);
        std::cout << "Negative Geometric tests passed." << std::endl;
    }
};

}  // namespace probability

/**
 * @brief Main function to run test cases
 * @returns 0 on successful execution
 */
int main() {
    probability::Bernoulli(0.5).test();
    probability::Binomial(5, 0.5).test();
    probability::NegativeBinomial(2, 0.5).test();
    probability::Poisson(3.0).test();
    probability::Geometric(0.5).test();
    probability::NegativeGeometric(0.5).test();

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
