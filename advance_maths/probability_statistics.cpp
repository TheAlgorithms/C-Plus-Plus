/**
 * @file
 * @brief Probability and statistics utilities and demonstrations.
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
#include <vector>

namespace advance_maths::probability_statistics {
using Vector = std::vector<double>;

double mean(const Vector& v) {
    if (v.empty()) {
        throw std::invalid_argument("Vector cannot be empty.");
    }
    return std::accumulate(v.begin(), v.end(), 0.0) / static_cast<double>(v.size());
}

double variance(const Vector& v) {
    const double m = mean(v);
    double sum = 0.0;
    for (double x : v) {
        sum += (x - m) * (x - m);
    }
    return sum / static_cast<double>(v.size());
}

double standard_deviation(const Vector& v) { return std::sqrt(variance(v)); }

double covariance(const Vector& x, const Vector& y) {
    if (x.size() != y.size() || x.empty()) {
        throw std::invalid_argument("Vectors must be non-empty and same size.");
    }
    const double mx = mean(x);
    const double my = mean(y);
    double sum = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        sum += (x[i] - mx) * (y[i] - my);
    }
    return sum / static_cast<double>(x.size());
}

double pearson_correlation(const Vector& x, const Vector& y) {
    const double denom = standard_deviation(x) * standard_deviation(y);
    if (denom < 1e-12) {
        throw std::invalid_argument("Standard deviation is zero.");
    }
    return covariance(x, y) / denom;
}

double joint_probability(double p_a, double p_b_given_a) { return p_a * p_b_given_a; }

double conditional_probability(double joint, double p_condition) {
    if (p_condition <= 0.0) {
        throw std::invalid_argument("Condition probability must be > 0.");
    }
    return joint / p_condition;
}

double bayes(double p_b_given_a, double p_a, double p_b) {
    if (p_b <= 0.0) {
        throw std::invalid_argument("Marginal probability p(B) must be > 0.");
    }
    return (p_b_given_a * p_a) / p_b;
}

double binomial_pmf(int n, int k, double p) {
    if (k < 0 || k > n || p < 0.0 || p > 1.0) {
        throw std::invalid_argument("Invalid binomial parameters.");
    }
    auto combination = [&](int nn, int kk) {
        double c = 1.0;
        for (int i = 1; i <= kk; ++i) {
            c = c * (nn - (kk - i)) / i;
        }
        return c;
    };
    return combination(n, k) * std::pow(p, k) * std::pow(1.0 - p, n - k);
}

double normal_pdf(double x, double mu, double sigma) {
    if (sigma <= 0.0) {
        throw std::invalid_argument("Sigma must be > 0.");
    }
    const double z = (x - mu) / sigma;
    return std::exp(-0.5 * z * z) / (sigma * std::sqrt(2.0 * M_PI));
}

std::pair<double, double> confidence_interval_mean(const Vector& v, double z_score = 1.96) {
    const double m = mean(v);
    const double se = standard_deviation(v) / std::sqrt(static_cast<double>(v.size()));
    return {m - z_score * se, m + z_score * se};
}

bool z_test_reject(double sample_mean, double hypothesized_mean, double sigma, int n,
                   double alpha = 0.05) {
    const double z = std::abs(sample_mean - hypothesized_mean) / (sigma / std::sqrt(static_cast<double>(n)));
    const double critical = (alpha == 0.05 ? 1.96 : 2.58);
    return z > critical;
}

double bootstrap_mean_estimate(const Vector& v, int iterations = 200) {
    std::mt19937 gen(123);
    std::uniform_int_distribution<size_t> dist(0, v.size() - 1);
    Vector bootstrap_means;
    bootstrap_means.reserve(iterations);

    for (int it = 0; it < iterations; ++it) {
        double sum = 0.0;
        for (size_t i = 0; i < v.size(); ++i) {
            sum += v[dist(gen)];
        }
        bootstrap_means.push_back(sum / static_cast<double>(v.size()));
    }
    return mean(bootstrap_means);
}
}  // namespace advance_maths::probability_statistics

static void test() {
    using namespace advance_maths::probability_statistics;
    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {2, 4, 6, 8, 10};

    assert(std::abs(mean(x) - 3.0) < 1e-9);
    assert(std::abs(variance(x) - 2.0) < 1e-9);
    assert(std::abs(standard_deviation(x) - std::sqrt(2.0)) < 1e-9);
    assert(std::abs(covariance(x, y) - 4.0) < 1e-9);
    assert(std::abs(pearson_correlation(x, y) - 1.0) < 1e-9);

    double joint = joint_probability(0.5, 0.2);
    assert(std::abs(joint - 0.1) < 1e-9);
    assert(std::abs(conditional_probability(0.1, 0.5) - 0.2) < 1e-9);
    assert(std::abs(bayes(0.9, 0.01, 0.02) - 0.45) < 1e-9);

    assert(std::abs(binomial_pmf(5, 2, 0.5) - 0.3125) < 1e-9);
    assert(std::abs(normal_pdf(0.0, 0.0, 1.0) - 0.3989422804) < 1e-6);

    auto ci = confidence_interval_mean(x);
    assert(ci.first < 3.0 && ci.second > 3.0);
    assert(!z_test_reject(5.1, 5.0, 1.0, 100));

    double boot = bootstrap_mean_estimate(x);
    assert(std::abs(boot - 3.0) < 0.2);
}

int main() {
    test();
    std::cout << "Probability and statistics module passed.\n";
    return 0;
}
