/******************************************************************************
 * @file
 * @brief Implementation of the [Convex
 * Hull](https://en.wikipedia.org/wiki/Convex_hull) implementation using [Graham
 * Scan](https://en.wikipedia.org/wiki/Graham_scan)
 * @details
 * In geometry, the convex hull or convex envelope or convex closure of a shape
 * is the smallest convex set that contains it. The convex hull may be defined
 * either as the intersection of all convex sets containing a given subset of a
 * Euclidean space, or equivalently as the set of all convex combinations of
 * points in the subset. For a bounded subset of the plane, the convex hull may
 * be visualized as the shape enclosed by a rubber band stretched around the
 * subset.
 *
 * The worst case time complexity of Jarvis’s Algorithm is O(n^2). Using
 * Graham’s scan algorithm, we can find Convex Hull in O(nLogn) time.
 *
 * ### Implementation
 *
 * Sort points
 * We first find the bottom-most point. The idea is to pre-process
 * points be sorting them with respect to the bottom-most point. Once the points
 * are sorted, they form a simple closed path.
 * The sorting criteria is to use the orientation to compare angles without
 * actually computing them (See the compare() function below) because
 * computation of actual angles would be inefficient since trigonometric
 * functions are not simple to evaluate.
 *
 * Accept or Reject Points
 * Once we have the closed path, the next step is to traverse the path and
 * remove concave points on this path using orientation. The first two points in
 * sorted array are always part of Convex Hull. For remaining points, we keep
 * track of recent three points, and find the angle formed by them. Let the
 * three points be prev(p), curr(c) and next(n). If orientation of these points
 * (considering them in same order) is not counterclockwise, we discard c,
 * otherwise we keep it.
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 *
 *******************************************************************************/
#include <algorithm>  /// for std::swap
#include <cstdlib>    /// for mathematics and datatype conversion
#include <iostream>   /// for IO operations
#include <stack>      /// for std::stack
#include <vector>     /// for std::vector

/******************************************************************************
 * @namespace geometry
 * @brief geometric algorithms
 *******************************************************************************/
namespace geometry {

/******************************************************************************
 * @namespace graham scan
 * @brief convex hull algorithm
 *******************************************************************************/
namespace grahamscan {

/******************************************************************************
 * @struct Point
 * @brief for X and Y co-ordinates of the co-ordinate.
 *******************************************************************************/
struct Point {
    int x, y;
};

// A global point needed for sorting points with reference
// to  the first point Used in compare function of qsort()

Point p0;

/******************************************************************************
 * @brief A utility function to find next to top in a stack.
 * @param S Stack to be used for the process.
 * @returns @param Point Co-ordinates of the Point <int, int>
 *******************************************************************************/
Point nextToTop(std::stack<Point> *S) {
    Point p = S->top();
    S->pop();
    Point res = S->top();
    S->push(p);
    return res;
}

/******************************************************************************
 * @brief A utility function to return square of distance between p1 and p2.
 * @param p1 Co-ordinates of Point 1 <int, int>.
 * @param p2 Co-ordinates of Point 2 <int, int>.
 * @returns @param int distance between p1 and p2.
 *******************************************************************************/
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

/******************************************************************************
 * @brief To find orientation of ordered triplet (p, q, r).
 * @param p Co-ordinates of Point p <int, int>.
 * @param q Co-ordinates of Point q <int, int>.
 * @param r Co-ordinates of Point r <int, int>.
 * @returns @param int 0 --> p, q and r are collinear, 1 --> Clockwise,
 * 2 --> Counterclockwise
 *******************************************************************************/
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) {
        return 0;  // collinear
    }
    return (val > 0) ? 1 : 2;  // clock or counter-clock wise
}

/******************************************************************************
 * @brief A function used by library function qsort() to sort an array of
 * points with respect to the first point
 * @param vp1 Co-ordinates of Point 1 <int, int>.
 * @param vp2 Co-ordinates of Point 2 <int, int>.
 * @returns @param int distance between p1 and p2.
 *******************************************************************************/
int compare(const void *vp1, const void *vp2) {
    auto *p1 = static_cast<const Point *>(vp1);
    auto *p2 = static_cast<const Point *>(vp2);

    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0) {
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;
    }

    return (o == 2) ? -1 : 1;
}

/******************************************************************************
 * @brief Prints convex hull of a set of n points.
 * @param points vector of Point<int, int> with co-ordinates.
 * @param size Size of the vector.
 * @returns @param vector vector of Conver Hull.
 *******************************************************************************/
std::vector<Point> convexHull(std::vector<Point> points, uint64_t size) {
    // Find the bottom-most point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < size; i++) {
        int y = points[i].y;

        // Pick the bottom-most or chose the left-most point in case of tie
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            ymin = points[i].y, min = i;
        }
    }

    // Place the bottom-most point at first position
    std::swap(points[0], points[min]);

    // Sort n-1 points with respect to the first point. A point p1 comes
    // before p2 in sorted output if p2 has larger polar angle
    // (in counterclockwise direction) than p1.
    p0 = points[0];
    qsort(&points[1], size - 1, sizeof(Point), compare);

    // If two or more points make same angle with p0, Remove all but the one
    // that is farthest from p0 Remember that, in above sorting, our criteria
    // was to keep the farthest point at the end when more than one points have
    // same angle.
    int m = 1;  // Initialize size of modified array
    for (int i = 1; i < size; i++) {
        // Keep removing i while angle of i and i+1 is same with respect to p0
        while (i < size - 1 && orientation(p0, points[i], points[i + 1]) == 0) {
            i++;
        }

        points[m] = points[i];
        m++;  // Update size of modified array
    }

    // If modified array of points has less than 3 points, convex hull is not
    // possible
    if (m < 3) {
        return {};
    };

    // Create an empty stack and push first three points to it.
    std::stack<Point> St;
    St.push(points[0]);
    St.push(points[1]);
    St.push(points[2]);

    // Process remaining n-3 points
    for (int i = 3; i < m; i++) {
        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn
        while (St.size() > 1 &&
               orientation(nextToTop(&St), St.top(), points[i]) != 2) {
            St.pop();
        }
        St.push(points[i]);
    }

    std::vector<Point> result;
    // Now stack has the output points, push them into the resultant vector
    while (!St.empty()) {
        Point p = St.top();
        result.push_back(p);
        St.pop();
    }

    return result;  // return resultant vector with Convex Hull co-ordinates.
}
}  // namespace grahamscan
}  // namespace geometry
