/**
 * @file
 * @brief
 * Implementation to calculate an estimate of the [number π
 * (Pi)](https://en.wikipedia.org/wiki/File:Pi_30K.gif).
 *
 * @details
 * We take a random point P with coordinates (x, y) such that 0 ≤ x ≤ 1 and 0 ≤
 * y ≤ 1. If x² + y² ≤ 1, then the point is inside the quarter disk of radius 1,
 * else the point is outside. We know that the probability of the point being
 * inside the quarter disk is equal to π/4 double approx(vector<Point> &pts)
 * which will use the points pts (drawn at random) to return an estimate of the
 * number π
 * @note This implementation is better than naive recursive or iterative
 * approach.
 *
 * @author [Qannaf AL-SAHMI](https://github.com/Qannaf)
 */

#include <cassert>   /// for assert
#include <cstdlib>   /// for std::rand
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {

/**
 * @brief structure of points containing two numbers, x and y, such that 0 ≤ x ≤
 * 1 and 0 ≤ y ≤ 1.
 */
using Point = struct {
    double x;
    double y;
};

/**
 * @brief This function uses the points in a given vector 'pts' (drawn at
 * random) to return an approximation of the number π.
 * @param pts Each item of pts contains a point. A point is represented by the
 * point structure (coded above).
 * @return  an estimate of the number π.
 */
double approximate_pi(const std::vector<Point> &pts) {
    double count = 0;  // Points in circle
    for (Point p : pts) {
        if ((p.x * p.x) + (p.y * p.y) <= 1) {
            count++;
        }
    }
    return 4.0 * count / static_cast<double>(pts.size());
}
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    std::vector<math::Point> rands;
    for (std::size_t i = 0; i < 100000; i++) {
        math::Point p;
        p.x = rand() / static_cast<double>(RAND_MAX);  // 0 <= x <= 1
        p.y = rand() / static_cast<double>(RAND_MAX);  // 0 <= y <= 1
        rands.push_back(p);
    }
    assert(math::approximate_pi(rands) > 3.135);
    assert(math::approximate_pi(rands) < 3.145);

    std::cout << "All tests have successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
