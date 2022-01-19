/**
 * @file
 * @brief Implementation to calculate an estimate of the [number π (Pi)](https://en.wikipedia.org/wiki/File:Pi_30K.gif).
 *
 * @details
 * We take a random point P with coordinates (x, y) such that 0 ≤ x ≤ 1 and 0 ≤ y ≤ 1. If x² + y² ≤ 1, then the 
 * point is inside the quarter disk of radius 1, otherwise the point is outside.
 * We know that the probability of the point being inside the quarter disk is equal to π/4
 * double approx(vector<Point> &pts) which will use the points pts (drawn at random) to 
 * return an estimate of the number π
 * \note This implementation is better than naive recursive or iterative
 * approach.
 *
 * @author [Qannaf AL-SAHMI](https://github.com/Qannaf)
 */

#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector
#include <cstdlib>  /// for std::rand

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {

    /**
     * structure of points containing two numbers, respectively x and y such that 0 ≤ x ≤ 1 and 0 ≤ y ≤ 1. 
    */
    typedef struct {
    double x;
    double y;
    } Point;

    double  approximate_pi(const std::vector<Point> &pts) {
    /**
     * This function use the points pts (drawn at random) to return an estimate of the number π  using the given points
     * @param pts Each item of pts contains a point. A point is represented by a structure containing exactly 
     * two numbers, respectively x and y such that 0 ≤ x ≤ 1 and 0 ≤ y ≤ 1. 
     * pts always contains at least one item
     * @return  an estimate of the number π
     */
        {
            int count =0;    // Points in cercle
            for(Point p:pts)
                if(p.x * p.x + p.y*p.y <= 1)
                    ++count;
            
            return 4.0*count/pts.size();
        }
    }
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
        std::vector<math::Point> rands;
    for (std::size_t i = 0; i < 100000; i++) {
        math::Point p;
        p.x = rand() / (double)RAND_MAX; // 0 <= x <= 1
        p.y = rand() / (double)RAND_MAX; // 0 <= y <= 1
        rands.push_back(p);
    }
    std::cout << math::approximate_pi(rands) << std::endl;          // ~3.14
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    return 0;
}
