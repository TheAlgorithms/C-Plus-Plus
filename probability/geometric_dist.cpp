/**
 * @file
 * @brief [Geometric
 * Distribution](https://en.wikipedia.org/wiki/Geometric_distribution)
 *
 * @details
 * The geometric distribution models the experiment of doing Bernoulli trials
 * until a sucess was observed. There are two formulations of the geometric
 * distribution: 1) The probability distribution of the number X of Bernoulli
 * trials needed to get one success, supported on the set { 1, 2, 3, ... } 2)
 * The probability distribution of the number Y = X − 1 of failures before the
 * first success, supported on the set { 0, 1, 2, 3, ... } Here, the first one
 * is implemented.
 *
 * Common variables used:
 * p - The success probability
 * k - The number of tries
 *
 * @author [Domenic Zingsheim](https://github.com/DerAndereDomenic)
 */

#include <cassert>   /// for assert
#include <cmath>     /// for math functions
#include <cstdint>   /// for fixed size data types
#include <ctime>     /// for time to initialize rng
#include <iostream>  /// for std::cout
#include <limits>    /// for std::numeric_limits
#include <random>    /// for random numbers
#include <vector>    /// for std::vector

/**
 * @namespace probability
 * @brief Probability algorithms
 */
namespace probability {
/**
 * @namespace geometric_dist
 * @brief Functions for the [Geometric
 * Distribution](https://en.wikipedia.org/wiki/Geometric_distribution) algorithm
 * implementation
 */
namespace geometric_dist {
/**
 * @brief Returns a random number between [0,1]
 * @returns A uniformly distributed random number between 0 (included) and 1
 * (included)
 */
float generate_uniform() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

/**
 * @brief A class to model the geometric distribution
 */
class geometric_distribution {
 private:
    float p;  ///< The succes probability p

 public:
    /**
     * @brief Constructor for the geometric distribution
     * @param p The success probability
     */
    explicit geometric_distribution(const float& p) : p(p) {}

    /**
     * @brief The expected value of a geometrically distributed random variable
     * X
     * @returns E[X] = 1/p
     */
    float expected_value() const { return 1.0f / p; }

    /**
     * @brief The variance of a geometrically distributed random variable X
     * @returns V[X] = (1 - p) / p^2
     */
    float variance() const { return (1.0f - p) / (p * p); }

    /**
     * @brief The standard deviation of a geometrically distributed random
     * variable X
     * @returns \sigma = \sqrt{V[X]}
     */
    float standard_deviation() const { return std::sqrt(variance()); }

    /**
     * @brief The probability density function
     * @details As we use the first definition of the geometric series (1),
     * we are doing k - 1 failed trials and the k-th trial is a success.
     * @param k The number of trials to observe the first success in [1,\infty)
     * @returns A number between [0,1] according to p * (1-p)^{k-1}
     */
    float probability_density(const uint32_t& k) const {
        return std::pow((1.0f - p), static_cast<float>(k - 1)) * p;
    }

    /**
     * @brief The cumulative distribution function
     * @details The sum of all probabilities up to (and including) k trials.
     * Basically CDF(k) = P(x <= k)
     * @param k The number of trials in [1,\infty)
     * @returns The probability to have success within k trials
     */
    float cumulative_distribution(const uint32_t& k) const {
        return 1.0f - std::pow((1.0f - p), static_cast<float>(k));
    }

    /**
     * @brief The inverse cumulative distribution function
     * @details This functions answers the question: Up to how many trials are
     * needed to have success with a probability of cdf? The exact floating
     * point value is reported.
     * @param cdf The probability in [0,1]
     * @returns The number of (exact) trials.
     */
    float inverse_cumulative_distribution(const float& cdf) const {
        return std::log(1.0f - cdf) / std::log(1.0f - p);
    }

    /**
     * @brief Generates a (discrete) sample according to the geometrical
     * distribution
     * @returns A geometrically distributed number in [1,\infty)
     */
    uint32_t draw_sample() const {
        float uniform_sample = generate_uniform();
        return static_cast<uint32_t>(
                   inverse_cumulative_distribution(uniform_sample)) +
               1;
    }

    /**
     * @brief This function computes the probability to have success in a given
     * range of tries
     * @details Computes P(min_tries <= x <= max_tries).
     * Can be used to calculate P(x >= min_tries) by not passing a second
     * argument. Can be used to calculate P(x <= max_tries) by passing 1 as the
     * first argument
     * @param min_tries The minimum number of tries in [1,\infty) (inclusive)
     * @param max_tries The maximum number of tries in [min_tries, \infty)
     * (inclusive)
     * @returns The probability of having success within a range of tries
     * [min_tries, max_tries]
     */
    float range_tries(const uint32_t& min_tries = 1,
                      const uint32_t& max_tries =
                          std::numeric_limits<uint32_t>::max()) const {
        float cdf_lower = cumulative_distribution(min_tries - 1);
        float cdf_upper = max_tries == std::numeric_limits<uint32_t>::max()
                              ? 1.0f
                              : cumulative_distribution(max_tries);
        return cdf_upper - cdf_lower;
    }
};
}  // namespace geometric_dist
}  // namespace probability

/**
 * @brief Tests the sampling method of the geometric distribution
 * @details Draws 1000000 random samples and estimates mean and variance
 * These should be close to the expected value and variance of the given
 * distribution to pass.
 * @param dist The distribution to test
 */
void sample_test(
    const probability::geometric_dist::geometric_distribution& dist) {
    uint32_t n_tries = 1000000;
    std::vector<float> tries;
    tries.resize(n_tries);

    float mean = 0.0f;
    for (uint32_t i = 0; i < n_tries; ++i) {
        tries[i] = static_cast<float>(dist.draw_sample());
        mean += tries[i];
    }

    mean /= static_cast<float>(n_tries);

    float var = 0.0f;
    for (uint32_t i = 0; i < n_tries; ++i) {
        var += (tries[i] - mean) * (tries[i] - mean);
    }

    // Unbiased estimate of variance
    var /= static_cast<float>(n_tries - 1);

    std::cout << "This value should be near " << dist.expected_value() << ": "
              << mean << std::endl;
    std::cout << "This value should be near " << dist.variance() << ": " << var
              << std::endl;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    probability::geometric_dist::geometric_distribution dist(0.3);

    const float threshold = 1e-3f;

    std::cout << "Starting tests for p = 0.3..." << std::endl;
    assert(std::abs(dist.expected_value() - 3.33333333f) < threshold);
    assert(std::abs(dist.variance() - 7.77777777f) < threshold);
    assert(std::abs(dist.standard_deviation() - 2.788866755) < threshold);
    assert(std::abs(dist.probability_density(5) - 0.07203) < threshold);
    assert(std::abs(dist.cumulative_distribution(6) - 0.882351) < threshold);
    assert(std::abs(dist.inverse_cumulative_distribution(
                        dist.cumulative_distribution(8)) -
                    8) < threshold);
    assert(std::abs(dist.range_tries() - 1.0f) < threshold);
    assert(std::abs(dist.range_tries(3) - 0.49f) < threshold);
    assert(std::abs(dist.range_tries(5, 11) - 0.2203267f) < threshold);
    std::cout << "All tests passed" << std::endl;
    sample_test(dist);

    dist = probability::geometric_dist::geometric_distribution(0.5f);

    std::cout << "Starting tests for p = 0.5..." << std::endl;
    assert(std::abs(dist.expected_value() - 2.0f) < threshold);
    assert(std::abs(dist.variance() - 2.0f) < threshold);
    assert(std::abs(dist.standard_deviation() - 1.4142135f) < threshold);
    assert(std::abs(dist.probability_density(5) - 0.03125) < threshold);
    assert(std::abs(dist.cumulative_distribution(6) - 0.984375) < threshold);
    assert(std::abs(dist.inverse_cumulative_distribution(
                        dist.cumulative_distribution(8)) -
                    8) < threshold);
    assert(std::abs(dist.range_tries() - 1.0f) < threshold);
    assert(std::abs(dist.range_tries(3) - 0.25f) < threshold);
    assert(std::abs(dist.range_tries(5, 11) - 0.062011f) < threshold);
    std::cout << "All tests passed" << std::endl;
    sample_test(dist);

    dist = probability::geometric_dist::geometric_distribution(0.8f);

    std::cout << "Starting tests for p = 0.8..." << std::endl;
    assert(std::abs(dist.expected_value() - 1.25f) < threshold);
    assert(std::abs(dist.variance() - 0.3125f) < threshold);
    assert(std::abs(dist.standard_deviation() - 0.559016f) < threshold);
    assert(std::abs(dist.probability_density(5) - 0.00128) < threshold);
    assert(std::abs(dist.cumulative_distribution(6) - 0.999936) < threshold);
    assert(std::abs(dist.inverse_cumulative_distribution(
                        dist.cumulative_distribution(8)) -
                    8) < threshold);
    assert(std::abs(dist.range_tries() - 1.0f) < threshold);
    assert(std::abs(dist.range_tries(3) - 0.04f) < threshold);
    assert(std::abs(dist.range_tries(5, 11) - 0.00159997f) < threshold);
    std::cout << "All tests have successfully passed!" << std::endl;
    sample_test(dist);
}

/**
 * @brief Main function
 * @return 0 on exit
 */
int main() {
    srand(time(nullptr));
    test();  // run self-test implementations
    return 0;
}
