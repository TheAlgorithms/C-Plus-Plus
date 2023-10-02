#include <cstddef>
#include <iostream>
#include <vector>

/// @brief performs lagrange interpolation on `xi, yi` with `x` provided
/// @param xi first container
/// @param yi second container
/// @param x
/// @return Ty
template <class Cont, class Ty>
[[nodiscard]] constexpr auto lagrange(const Cont &xi, const Cont &yi,
                                      const Ty x) {
    Ty temp{};
    Ty lagrange{};
    for (size_t i{}; i < xi.size(); ++i) {
        temp = yi[i];
        for (size_t j{}; j < xi.size(); ++j) {
            if (i != j) {
                temp *= (x - xi[j]) / (xi[i] - xi[j]);
            }
        }
        lagrange += temp;
    }
    return lagrange;
}

int main() {
    std::vector<float> xi{1, 2, 3, 4, 5};
    std::vector<float> yi{2, 3, 4, 6, 7};
    std::cout << lagrange(xi, yi, 3.);
}