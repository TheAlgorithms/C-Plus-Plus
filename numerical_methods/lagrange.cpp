#include <array>    // sttd::array<type, nElemnts>
#include <iostream> // for std::cout

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

// check if lagrange
constexpr auto check = []() {
  constexpr std::array<float, 5> xi{1, 2, 3, 4, 5};
  constexpr std::array<float, 5> yi{2, 3, 4, 6, 7};
  // should return true
  return (lagrange(xi, yi, 3.) == 4.0f);
};

int main() {
  // shows the the result for the calculations
  std::cout << std::boolalpha << check();
}