/**
 * @file
 * @brief Implementation of [Jarvis’s Algorithm](https://en.wikipedia.org/wiki/Gift_wrapping_algorithm) algorithm.
 *
 * @details
 * Given a set of points in the plane. the convex hull of the set
 * is the smallest convex polygon that contains all the points of it.
 *
 * ### Algorithm
 * The idea of Jarvis’s Algorithm is simple, we start from the leftmost point
 * (or point with minimum x coordinate value) and we
 * keep wrapping points in counterclockwise direction.
 *
 * The idea is to use orientation() here. Next point is selected as the
 * point that beats all other points at counterclockwise orientation, i.e.,
 * next point is q if for any other point r,
 * we have “orientation(p, q, r) = counterclockwise”.
 *
 * For Example,
 * If points = {{0, 3}, {2, 2}, {1, 1}, {2, 1},
                      {3, 0}, {0, 0}, {3, 3}};
 *
 * then the convex hull is
 * (0, 3), (0, 0), (3, 0), (3, 3)
 *
 * @author [Rishabh Agarwal](https://github.com/rishabh-997)
 */

#include <utility>
#include <vector>
#include <cassert>
#include <iostream>

/**
 *  @namespace geometry
 *  @brief Geometry algorithms
 */
namespace geometry {
    /**
     * Structure defining the x and y co-ordinates of the given
     * point in space
     */
    struct Point {
        int x, y;
    };

    /**
     * @namespace jarvis
     * @brief Functions for [Jarvis’s Algorithm](https://en.wikipedia.org/wiki/Gift_wrapping_algorithm) algorithm
     */
    namespace jarvis {
        /**
         * Class which can be called from main and is globally available
         * throughout the code
         */
        class Convexhull {
        public:
            std::vector<Point> points;
            int size;

            /**
             * Constructor of given class
             *
             * @param pointList list of all points in the space
             * @param n number of points in space
             */
            Convexhull(std::vector<Point> pointList, int n) {
                points = std::move(pointList);
                size = n;
            }

            /**
             * Creates convex hull of a set of n points.
             * There must be 3 points at least for the convex hull to exist
             *
             * @returns an vector array containing points in space
             * which enclose all given points thus forming a hull
             */
            std::vector<Point> getConvexHull() const {
                // Initialize Result
                std::vector<Point> hull;

                // Find the leftmost point
                int leftmost_point = 0;
                for (int i = 1; i < size; i++) {
                    if (points[i].x < points[leftmost_point].x) {
                        leftmost_point = i;
                    }
                }
                // Start from leftmost point, keep moving counterclockwise
                // until reach the start point again.  This loop runs O(h)
                // times where h is number of points in result or output.
                int p = leftmost_point, q = 0;
                do {
                    // Add current point to result
                    hull.push_back(points[p]);

                    // Search for a point 'q' such that orientation(p, x, q)
                    // is counterclockwise for all points 'x'. The idea
                    // is to keep track of last visited most counter clock-
                    // wise point in q. If any point 'i' is more counter clock-
                    // wise than q, then update q.
                    q = (p + 1) % size;
                    for (int i = 0; i < size; i++) {
                        // If i is more counterclockwise than current q, then
                        // update q
                        if (orientation(points[p], points[i], points[q]) == 2) {
                            q = i;
                        }
                    }

                    // Now q is the most counterclockwise with respect to p
                    // Set p as q for next iteration, so that q is added to
                    // result 'hull'
                    p = q;

                } while (p != leftmost_point);        // While we don't come to first point

                return hull;
            }

            /**
             *
             * @param p first point selected
             * @param q adjacent point for q
             * @param r adjacent point for q
             * @returns the geometric orientation for the three points
             *  0 -> Linear
             *  1 -> Clock Wise
             *  2 -> Anti Clock Wise
             */
            static int orientation(Point p, Point q, Point r) {
                int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

                if (val == 0) {
                    return 0;
                }
                return (val > 0) ? 1 : 2;
            }

        };

    } // namespace jarvis
} // namespace geometry

/**
 * Test function
 * @returns void
 */
static void test() {
    std::vector<geometry::Point> points = {{0, 3},
                                           {2, 2},
                                           {1, 1},
                                           {2, 1},
                                           {3, 0},
                                           {0, 0},
                                           {3, 3}
    };
    int n = points.size();
    geometry::jarvis::Convexhull hull(points, n);
    std::vector<geometry::Point> actualPoint;
    actualPoint = hull.getConvexHull();

    std::vector<geometry::Point> expectedPoint = {{0, 3},
                                                  {0, 0},
                                                  {3, 0},
                                                  {3, 3}};
    for (int i = 0; i < expectedPoint.size(); i++) {
        assert(actualPoint[i].x == expectedPoint[i].x);
        assert(actualPoint[i].y == expectedPoint[i].y);
    }
    std::cout << "Test implementations passed!\n";
}

/** Driver Code */
int main() {
    test();
    return 0;
}
