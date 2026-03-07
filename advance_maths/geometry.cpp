/**
 * @file
 * @brief Geometry-related similarity and projection utilities.
 */
#include <cassert>
#include <cmath>
#include <iostream>
#include <set>
#include <stdexcept>
#include <vector>

namespace advance_maths::geometry {
using Vector = std::vector<double>;

double dot(const Vector& a, const Vector& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must have the same size.");
    }
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

double norm(const Vector& v) {
    return std::sqrt(dot(v, v));
}

double cosine_similarity(const Vector& a, const Vector& b) {
    double denom = norm(a) * norm(b);
    if (denom < 1e-12) {
        throw std::invalid_argument("Norm cannot be zero.");
    }
    return dot(a, b) / denom;
}

double jaccard_similarity(const std::set<int>& a, const std::set<int>& b) {
    size_t intersection_count = 0;
    for (int item : a) {
        if (b.count(item) > 0) {
            ++intersection_count;
        }
    }
    const size_t union_count = a.size() + b.size() - intersection_count;
    return union_count == 0 ? 1.0 : static_cast<double>(intersection_count) / static_cast<double>(union_count);
}

bool are_orthogonal(const Vector& a, const Vector& b, double eps = 1e-9) {
    return std::abs(dot(a, b)) < eps;
}

Vector projection(const Vector& a, const Vector& b) {
    const double denom = dot(b, b);
    if (denom < 1e-12) {
        throw std::invalid_argument("Cannot project onto a zero vector.");
    }
    const double scale = dot(a, b) / denom;
    Vector proj = b;
    for (double& value : proj) {
        value *= scale;
    }
    return proj;
}
}  // namespace advance_maths::geometry

static void test() {
    using namespace advance_maths::geometry;

    Vector a = {1.0, 2.0, 3.0};
    Vector b = {2.0, 4.0, 6.0};
    assert(std::abs(cosine_similarity(a, b) - 1.0) < 1e-9);

    std::set<int> s1 = {1, 2, 3, 5};
    std::set<int> s2 = {2, 3, 4};
    assert(std::abs(jaccard_similarity(s1, s2) - 0.4) < 1e-9);

    Vector o1 = {1.0, 0.0};
    Vector o2 = {0.0, 4.0};
    assert(are_orthogonal(o1, o2));

    Vector p = projection(a, b);
    assert(std::abs(p[0] - 1.0) < 1e-9);
    assert(std::abs(p[1] - 2.0) < 1e-9);
    assert(std::abs(p[2] - 3.0) < 1e-9);
}

int main() {
    test();
    std::cout << "Geometry module passed.\n";
    return 0;
}
