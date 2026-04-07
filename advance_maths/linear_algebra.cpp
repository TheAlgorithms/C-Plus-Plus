/**
 * @file
 * @brief Core linear algebra utilities and demonstrations.
 */
#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace advance_maths::linear_algebra {
using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

static void validate_same_size(const Vector& a, const Vector& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must have the same size.");
    }
}

double dot_product(const Vector& a, const Vector& b) {
    validate_same_size(a, b);
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

double l2_norm(const Vector& a) { return std::sqrt(dot_product(a, a)); }

double manhattan_norm(const Vector& a) {
    double sum = 0.0;
    for (double value : a) {
        sum += std::abs(value);
    }
    return sum;
}

double euclidean_distance(const Vector& a, const Vector& b) {
    validate_same_size(a, b);
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return std::sqrt(sum);
}

double manhattan_distance(const Vector& a, const Vector& b) {
    validate_same_size(a, b);
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += std::abs(a[i] - b[i]);
    }
    return sum;
}

Matrix multiply(const Matrix& a, const Matrix& b) {
    if (a.empty() || b.empty() || a[0].size() != b.size()) {
        throw std::invalid_argument("Incompatible matrix dimensions.");
    }

    Matrix result(a.size(), Vector(b[0].size(), 0.0));
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t k = 0; k < b.size(); ++k) {
            for (size_t j = 0; j < b[0].size(); ++j) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

std::pair<Matrix, Matrix> lu_decomposition_2x2(const Matrix& m) {
    if (m.size() != 2 || m[0].size() != 2 || m[1].size() != 2) {
        throw std::invalid_argument("This demo supports only 2x2 matrices.");
    }
    if (std::abs(m[0][0]) < 1e-12) {
        throw std::invalid_argument("Pivot too small for this simple LU decomposition.");
    }

    Matrix l = {{1.0, 0.0}, {m[1][0] / m[0][0], 1.0}};
    Matrix u = {{m[0][0], m[0][1]}, {0.0, m[1][1] - l[1][0] * m[0][1]}};
    return {l, u};
}

std::pair<double, double> eigenvalues_2x2(const Matrix& m) {
    if (m.size() != 2 || m[0].size() != 2 || m[1].size() != 2) {
        throw std::invalid_argument("This demo supports only 2x2 matrices.");
    }

    const double trace = m[0][0] + m[1][1];
    const double det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    const double disc = std::sqrt(trace * trace - 4.0 * det);
    return {(trace + disc) / 2.0, (trace - disc) / 2.0};
}

Vector dominant_right_singular_vector_2x2(const Matrix& m) {
    Matrix mtm = {
        {m[0][0] * m[0][0] + m[1][0] * m[1][0], m[0][0] * m[0][1] + m[1][0] * m[1][1]},
        {m[0][0] * m[0][1] + m[1][0] * m[1][1], m[0][1] * m[0][1] + m[1][1] * m[1][1]}};

    auto eig = eigenvalues_2x2(mtm);
    double lambda = std::max(eig.first, eig.second);

    Vector v = {mtm[0][1], lambda - mtm[0][0]};
    double norm = l2_norm(v);
    if (norm < 1e-12) {
        return {1.0, 0.0};
    }
    v[0] /= norm;
    v[1] /= norm;
    return v;
}
}  // namespace advance_maths::linear_algebra

static void test() {
    using namespace advance_maths::linear_algebra;

    Vector a = {1.0, 2.0, 3.0};
    Vector b = {4.0, 1.0, -2.0};
    assert(std::abs(dot_product(a, b) - 0.0) < 1e-9);
    assert(std::abs(l2_norm(a) - std::sqrt(14.0)) < 1e-9);
    assert(std::abs(manhattan_norm(a) - 6.0) < 1e-9);
    assert(std::abs(euclidean_distance(a, b) - std::sqrt(35.0)) < 1e-9);
    assert(std::abs(manhattan_distance(a, b) - 9.0) < 1e-9);

    Matrix m = {{4.0, 3.0}, {4.0, 3.0}};
    auto [l, u] = lu_decomposition_2x2(m);
    Matrix reconstructed = multiply(l, u);
    assert(std::abs(reconstructed[0][0] - 4.0) < 1e-9);
    assert(std::abs(reconstructed[1][0] - 4.0) < 1e-9);

    auto eig = eigenvalues_2x2(m);
    assert(std::abs(eig.first - 7.0) < 1e-9 || std::abs(eig.second - 7.0) < 1e-9);

    Vector sv = dominant_right_singular_vector_2x2({{1.0, 2.0}, {3.0, 4.0}});
    assert(std::abs(l2_norm(sv) - 1.0) < 1e-9);
}

int main() {
    test();
    std::cout << "Linear algebra module passed.\n";
    return 0;
}
