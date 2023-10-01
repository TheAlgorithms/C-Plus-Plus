#include <cstdint>
#include <iostream>
#include <vector>
//
[[nodiscard]] constexpr auto factorial(std::size_t val) -> std::size_t {
    if (val <= 1) {
        return 1;
    }
    return val * factorial(val - 1);
}
//
/// @brief performs Newton's Forward Difference Formula on two dynamic
/// containers
/// @param xi container
/// @param yi container
/// @param x [by default it's `1`]
/// @return Ty
template <class Ty, class Cont>
[[nodiscard]] auto newton_forward(const Cont &xi, Cont &yi, const Ty x) -> Ty {
    Cont forward{yi[0]}; // holds forward difference of `yi` init = yi[0]
    std::size_t size{yi.size()};
    //
    for (std::size_t i{}; i < size;
         ++i) { // calculates forward difference of `yi`
        Cont temp{};
        for (std::size_t j{1}; j < size; ++j) {
            temp.push_back(yi[j - 1] = (yi[j] - yi[j - 1]));
            if (j == yi.size() - 1) {
                yi.erase(yi.begin() + static_cast<int64_t>(size - 1));
            }
        }
        size = temp.size();
        forward.push_back(temp[0]);
    }
    forward.push_back(yi[0] = yi[1] - yi[0]);
    const auto cal_u = [](const Ty u, const std::size_t times) -> Ty {
        Ty result{u};
        for (std::size_t i{1}; i < times; ++i) {
            result *= u - static_cast<Ty>(i);
        }
        return result;
    };
    const Ty u{(x - xi[0]) / (xi[1] - xi[0])};
    Ty y{(forward[0])};
    //
    for (std::size_t i{1}; i < xi.size(); ++i) {
        y = y + (cal_u(u, i) * (forward[i])) / static_cast<Ty>(factorial(i));
    }
    return y;
}
//
auto main() -> int {
    std::vector<float> xi{1891, 1901, 1911, 1921, 1931};
    std::vector<float> yi{46, 66, 81, 93, 101};
    std::cout << newton_forward(xi, yi, 1.) << '\n';
}