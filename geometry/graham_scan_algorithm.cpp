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
 * three points be prev(p), curr(c) and next(n). If the orientation of these
 * points (considering them in the same order) is not counterclockwise, we
 * discard c, otherwise we keep it.
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 *
 *******************************************************************************/
#include <cassert>   /// for std::assert
#include <iostream>  /// for IO Operations
#include <vector>    /// for std::vector

#include "./graham_scan_functions.hpp"  /// for all the functions used

/*******************************************************************************
 * @brief Self-test implementations
 * @returns void
 *******************************************************************************/
static void test() {
    std::vector<geometry::grahamscan::Point> points = {
        {0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    std::vector<geometry::grahamscan::Point> expected_result = {
        {0, 3}, {4, 4}, {3, 1}, {0, 0}};
    std::vector<geometry::grahamscan::Point> derived_result;
    std::vector<geometry::grahamscan::Point> res;

    derived_result = geometry::grahamscan::convexHull(points, points.size());

    std::cout << "1st test: ";
    for (int i = 0; i < expected_result.size(); i++) {
        assert(derived_result[i].x == expected_result[i].x);
        assert(derived_result[i].y == expected_result[i].y);
    }
    std::cout << "passed!" << std::endl;
}

/*******************************************************************************
 * @brief Main function
 * @returns 0 on exit
 *******************************************************************************/
int main() {
    test();  // run self-test implementations
    return 0;
}
