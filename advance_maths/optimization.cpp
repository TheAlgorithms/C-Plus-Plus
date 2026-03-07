/**
 * @file
 * @brief Optimization algorithms: gradient descent and SGD.
 */
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

namespace advance_maths::optimization {

double objective(double x) { return (x - 3.0) * (x - 3.0); }

double objective_grad(double x) { return 2.0 * (x - 3.0); }

double gradient_descent(double initial_x, double learning_rate, int iterations) {
    double x = initial_x;
    for (int i = 0; i < iterations; ++i) {
        x -= learning_rate * objective_grad(x);
    }
    return x;
}

std::pair<double, double> linear_sgd(const std::vector<double>& x, const std::vector<double>& y,
                                     double lr, int epochs) {
    double w = 0.0;
    double b = 0.0;
    std::mt19937 gen(42);
    std::uniform_int_distribution<size_t> dist(0, x.size() - 1);

    for (int epoch = 0; epoch < epochs; ++epoch) {
        size_t i = dist(gen);
        double pred = w * x[i] + b;
        double err = pred - y[i];
        w -= lr * 2.0 * err * x[i];
        b -= lr * 2.0 * err;
    }
    return {w, b};
}
}  // namespace advance_maths::optimization

static void test() {
    using namespace advance_maths::optimization;

    double optimum = gradient_descent(10.0, 0.1, 100);
    assert(std::abs(optimum - 3.0) < 1e-4);
    assert(objective(optimum) < 1e-6);

    std::vector<double> x = {1, 2, 3, 4};
    std::vector<double> y = {3, 5, 7, 9};  // y = 2x + 1
    auto [w, b] = linear_sgd(x, y, 0.01, 10000);
    assert(std::abs(w - 2.0) < 0.25);
    assert(std::abs(b - 1.0) < 0.5);
}

int main() {
    test();
    std::cout << "Optimization module passed.\n";
    return 0;
}
