/**
 * @file
 * @brief Basic and intermediate calculus utilities.
 */
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

namespace advance_maths::calculus {
using Vector = std::vector<double>;

double derivative(const std::function<double(double)>& f, double x, double h = 1e-5) {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

double second_derivative(const std::function<double(double)>& f, double x, double h = 1e-5) {
    return (f(x + h) - 2.0 * f(x) + f(x - h)) / (h * h);
}

double partial_derivative_x(const std::function<double(double, double)>& f, double x, double y,
                            double h = 1e-5) {
    return (f(x + h, y) - f(x - h, y)) / (2.0 * h);
}

double partial_derivative_y(const std::function<double(double, double)>& f, double x, double y,
                            double h = 1e-5) {
    return (f(x, y + h) - f(x, y - h)) / (2.0 * h);
}

Vector gradient_2d(const std::function<double(double, double)>& f, double x, double y) {
    return {partial_derivative_x(f, x, y), partial_derivative_y(f, x, y)};
}

double chain_rule(double df_dg, double dg_dx) { return df_dg * dg_dx; }

double backprop_single_weight(double prediction, double target, double input) {
    double loss_grad_prediction = 2.0 * (prediction - target);  // dL/dy for MSE
    double prediction_grad_weight = input;                       // dy/dw for y = wx
    return chain_rule(loss_grad_prediction, prediction_grad_weight);
}
}  // namespace advance_maths::calculus

static void test() {
    using namespace advance_maths::calculus;

    auto f = [](double x) { return x * x * x; };
    assert(std::abs(derivative(f, 2.0) - 12.0) < 1e-3);
    assert(std::abs(second_derivative(f, 2.0) - 12.0) < 1e-2);

    auto g = [](double x, double y) { return x * x + 3.0 * x * y + y * y; };
    assert(std::abs(partial_derivative_x(g, 1.0, 2.0) - 8.0) < 1e-3);
    assert(std::abs(partial_derivative_y(g, 1.0, 2.0) - 7.0) < 1e-3);

    auto grad = gradient_2d(g, 1.0, 2.0);
    assert(std::abs(grad[0] - 8.0) < 1e-3 && std::abs(grad[1] - 7.0) < 1e-3);

    double dldw = backprop_single_weight(3.0, 1.0, 2.0);
    assert(std::abs(dldw - 8.0) < 1e-9);
}

int main() {
    test();
    std::cout << "Calculus module passed.\n";
    return 0;
}
