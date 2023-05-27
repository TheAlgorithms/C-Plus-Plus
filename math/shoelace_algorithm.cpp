/**
 * @file
 * @brief Implementation of the [shoelace
 * algorithm](https://en.wikipedia.org/wiki/Shoelace_formula)
 *
 * @author [Renjian-buchai](https://github.com/Renjian-buchai)
 *
 * @details Calculates area of a polygon using the coordinates of its vertices.
 * Area of polygon
 * = 0.5 | (\x1, \y1) (\x2, \y2) ... (\xn, \yn) (\x1, \y1) |
 * = 0.5 | (\x1 * \y2 + \x2 * \y3 + ... + \xn * \y1) -
 *         (\x1 * \yn + \xn * \y(n-1)) + ... + \x2 * \y1) |
 * = 0.5 ( | \x1 * \y2 - \x2 * \y1 | + | \x2 * \y3 - \x3 * \y1 | + ...
 *       + | \xn * \y1 - \x1 * \yn | )
 * Where each point \xn is adjacent to \x(n-1) and \x(n+1).
 *
 * Usually, the formula also states that \x(n+1) must be counterclockwise to
 * \xn, but if you take the absolute value of the output, it doesn't matter even
 * if you input the points in clockwise order.
 *
 * The formula with multiple modulus operators is easier to implement.
 *
 * Example:
 * Points are inputted in counterclockwise order:
 * \p1 = (-2, 4)
 * \p2 = (-2, 1)
 * \p3 = (3, -3)
 * \p4 = (4, 4)
 *
 * Area
 * = 0.5 ( | ((-2), 4) ((-2), 1) | + | ((-2), 1) (3, (-3)) | +
 *         | (3, (-3)) (4, 4) | + | (4, 4) ((-2), 4) | )
 * = 0.5 ( | (-2) * 1 - (-2) * 4 | + | (-2) * (-3) - 3 * 1 | +
 *         | 3 * 4 - 4 * (-3) | + | 4 * 4 - (-2) * 4 | )
 * = 0.5 ( 6 + 3 + 24 + 24 )
 * = 0.5 (57)
 * = 28.5 units^2
 *
 * Note:
 * Case where points are inputted in clockwise order:
 * \p1 = (4, 4)
 * \p2 = (3, -3)
 * \p3 = (-2, 1)
 * \p4 = (-2, 4)
 *
 * Area
 * = 0.5 | (4, 4) (3, (-3)) | + | (3, (-3)) ((-2), 1) | +
 *       | ((-2), 1) ((-2), 4) | + | ((-2), 4) (4, 4) |
 * = 0.5 ( | 4 * (-3) - 4 * 3 | + | 3 * 1 - (-2) * (-3) | +
 *         | (-2) * 4 - (-2) * 1 | + | (-2) * 4 - 4 * 4 | )
 * = 0.5 ( | -24 | + | -3 | + | -6 | + | -24 | )
 * = 0.5 (57)
 * = 28.5 units^2
 *
 * If we remove the modulus operators, we find out that the output = -28.5
 * units. So, as long as we apply the modulus operator after, it doesn't matter
 * whether the points are inputted in clockwise order or counterclockwise order.
 */

#include <array>
#include <cassert>
#include <cmath>
#include <iostream>

namespace math {

/**
 * @brief Calculates area of a polygon with the coordinates
 * @tparam T: Any arithmetic type
 * @tparam N: Number of vertices of the ploygon
 * @param coordinates Array of coordinates of vertices of the polygon
 * @return Area of quadrilateral bounded by the coordinates provided
 * @note Each adjacent point must be adjacent to the prior point
 */
template <typename T, size_t N>
double shoelace(std::array<std::array<T, 2>, N> coordinates) {
    double sum = 0;
    for (size_t i = 0; i < N - 1; ++i) {
        sum += coordinates[i][0] * coordinates[i + 1][1] -
               coordinates[i + 1][0] * coordinates[i][1];
    }
    sum += coordinates[N - 2][0] * coordinates[N - 1][1] -
           coordinates[N - 1][0] * coordinates[N - 2][1];
    return std::abs(0.5 * sum);
}

}  // namespace math

/**
 * @brief Self-test implementations for shoelace algorithm
 */
static void test() {
    using std::array;

    std::cout << "Case 1:\n"
                 "Input: | (4, 4) (3, -3) (-2, 1) (-2, 4)\n"
                 "Expected output: 28.5\n";
    array<array<long, 2>, 4> case1{array<long, 2>{4, 4}, array<long, 2>{3, -3},
                                   array<long, 2>{-2, 1},
                                   array<long, 2>{-2, 4}};
    assert(math::shoelace(case1) == 28.5);

    std::cout << "Case 2:\n"
                 "Input: | (1, 6) (3, 1) (7, 2) (4, 4) (8, 5) |\n"
                 "Expected output: 16.5\n";
    array<array<long, 2>, 5> case2{array<long, 2>{1, 6}, array<long, 2>{2, 1},
                                   array<long, 2>{7, 2}, array<long, 2>{4, 4},
                                   array<long, 2>{8, 5}};
    assert(math::shoelace(case2) == 16.5);

    std::cout << "Case 3:\n"
                 "Input: | (7, 2) (4, 4) (8, 6) |\n"
                 "Expected output: 7\n";
    array<array<long, 2>, 3> case3{array<long, 2>{7, 2}, array<long, 2>{4, 4},
                                   array<long, 2>{8, 6}};
    assert(math::shoelace(case3) == 7);
}

/**
 * @brief Main function
 * @return 0 on exit
 */
int main() { test(); }