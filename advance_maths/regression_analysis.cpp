/**
 * @file
 * @brief Regression analysis utilities: MLE and MSE.
 */
#include <cassert>
#include <cmath>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <vector>

namespace advance_maths::regression_analysis {

double mean_squared_error(const std::vector<double>& y_true, const std::vector<double>& y_pred) {
    if (y_true.size() != y_pred.size() || y_true.empty()) {
        throw std::invalid_argument("Vectors must be same size and non-empty.");
    }
    double sum = 0.0;
    for (size_t i = 0; i < y_true.size(); ++i) {
        const double e = y_true[i] - y_pred[i];
        sum += e * e;
    }
    return sum / static_cast<double>(y_true.size());
}

std::pair<double, double> linear_regression_mle(const std::vector<double>& x,
                                                const std::vector<double>& y) {
    const double n = static_cast<double>(x.size());
    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_xy = 0.0;
    double sum_x2 = 0.0;

    for (size_t i = 0; i < x.size(); ++i) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    const double denom = n * sum_x2 - sum_x * sum_x;
    const double slope = (n * sum_xy - sum_x * sum_y) / denom;
    const double intercept = (sum_y - slope * sum_x) / n;
    return {slope, intercept};
}

double estimate_gaussian_mean_mle(const std::vector<double>& samples) {
    double sum = 0.0;
    for (double value : samples) {
        sum += value;
    }
    return sum / static_cast<double>(samples.size());
}

double estimate_gaussian_variance_mle(const std::vector<double>& samples, double mu_hat) {
    double sum = 0.0;
    for (double value : samples) {
        sum += (value - mu_hat) * (value - mu_hat);
    }
    return sum / static_cast<double>(samples.size());
}
}  // namespace advance_maths::regression_analysis

static void test() {
    using namespace advance_maths::regression_analysis;

    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {3, 5, 7, 9, 11};  // y = 2x + 1

    auto [slope, intercept] = linear_regression_mle(x, y);
    assert(std::abs(slope - 2.0) < 1e-9);
    assert(std::abs(intercept - 1.0) < 1e-9);

    std::vector<double> y_pred;
    for (double xv : x) {
        y_pred.push_back(slope * xv + intercept);
    }
    assert(std::abs(mean_squared_error(y, y_pred)) < 1e-9);

    std::vector<double> gaussian_samples = {2.0, 3.0, 4.0, 5.0};
    double mu_hat = estimate_gaussian_mean_mle(gaussian_samples);
    double var_hat = estimate_gaussian_variance_mle(gaussian_samples, mu_hat);
    assert(std::abs(mu_hat - 3.5) < 1e-9);
    assert(std::abs(var_hat - 1.25) < 1e-9);
}

int main() {
    test();
    std::cout << "Regression analysis module passed.\n";
    return 0;
}
