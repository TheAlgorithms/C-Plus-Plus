/**
 * @file
 * @brief Vector calculus utilities: Jacobian and Hessian.
 */
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

namespace advance_maths::vector_calculus {
using Vector = std::vector<double>;
using Matrix = std::vector<std::vector<double>>;

Vector gradient(const std::function<double(const Vector&)>& f, const Vector& x, double h = 1e-5) {
    Vector grad(x.size(), 0.0);
    for (size_t i = 0; i < x.size(); ++i) {
        Vector x_plus = x;
        Vector x_minus = x;
        x_plus[i] += h;
        x_minus[i] -= h;
        grad[i] = (f(x_plus) - f(x_minus)) / (2.0 * h);
    }
    return grad;
}

Matrix jacobian(const std::vector<std::function<double(const Vector&)>>& funcs, const Vector& x,
                double h = 1e-5) {
    Matrix j(funcs.size(), Vector(x.size(), 0.0));
    for (size_t row = 0; row < funcs.size(); ++row) {
        for (size_t col = 0; col < x.size(); ++col) {
            Vector x_plus = x;
            Vector x_minus = x;
            x_plus[col] += h;
            x_minus[col] -= h;
            j[row][col] = (funcs[row](x_plus) - funcs[row](x_minus)) / (2.0 * h);
        }
    }
    return j;
}

Matrix hessian(const std::function<double(const Vector&)>& f, const Vector& x, double h = 1e-4) {
    size_t n = x.size();
    Matrix hess(n, Vector(n, 0.0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            Vector x_pp = x, x_pm = x, x_mp = x, x_mm = x;
            x_pp[i] += h;
            x_pp[j] += h;
            x_pm[i] += h;
            x_pm[j] -= h;
            x_mp[i] -= h;
            x_mp[j] += h;
            x_mm[i] -= h;
            x_mm[j] -= h;
            hess[i][j] = (f(x_pp) - f(x_pm) - f(x_mp) + f(x_mm)) / (4.0 * h * h);
        }
    }
    return hess;
}
}  // namespace advance_maths::vector_calculus

static void test() {
    using namespace advance_maths::vector_calculus;

    auto scalar = [](const Vector& v) { return v[0] * v[0] + 3.0 * v[0] * v[1] + v[1] * v[1]; };
    Vector x = {1.0, 2.0};

    auto grad = gradient(scalar, x);
    assert(std::abs(grad[0] - 8.0) < 1e-3);
    assert(std::abs(grad[1] - 7.0) < 1e-3);

    std::vector<std::function<double(const Vector&)>> funcs = {
        [](const Vector& v) { return v[0] + v[1]; },
        [](const Vector& v) { return v[0] * v[1]; }};
    auto j = jacobian(funcs, x);
    assert(std::abs(j[0][0] - 1.0) < 1e-4 && std::abs(j[0][1] - 1.0) < 1e-4);
    assert(std::abs(j[1][0] - 2.0) < 1e-3 && std::abs(j[1][1] - 1.0) < 1e-3);

    auto h = hessian(scalar, x);
    assert(std::abs(h[0][0] - 2.0) < 1e-2);
    assert(std::abs(h[0][1] - 3.0) < 1e-2);
    assert(std::abs(h[1][0] - 3.0) < 1e-2);
    assert(std::abs(h[1][1] - 2.0) < 1e-2);
}

int main() {
    test();
    std::cout << "Vector calculus module passed.\n";
    return 0;
}
