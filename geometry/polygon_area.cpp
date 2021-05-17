/**
 * @file
 * @brief Implementation of [Polygon Area](https://en.wikipedia.org/wiki/https://en.wikipedia.org/wiki/Polygon).
 *
 * @details
 * Given a set of points of a simple polygon, the algorithm returns the area of
 * the polygon.
 *
 * @author [Karimi Zayan](https://github.com/waffleSheep)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <numeric>   /// for inner_product function
#include <vector>    /// for vector data structure

/**
 *  @namespace geometry
 *  @brief Geometry algorithms
 */
namespace geometry {
/**
 *  @namespace polygon_area
 *  @brief Functions for [Polygon Area](https://en.wikipedia.org/wiki/https://en.wikipedia.org/wiki/Polygon) implementation.
 */
namespace polygon_area {
/**
 * Point Struct
 * @tparam for numeric type of the point
 */
template <typename T>
struct Point {
    T x, y;  /// x and y values for a point
};

/**
 * Class for Polygon Area
 * @tparam for numeric type of the points
 */
template <typename T>
class Polygon_Area {
    std::vector<Point<T>> points;  /// list of all points in the 2d space
 public:
    /**
     * Constructor of given class
     *
     * @param point_list list of all the points in the 2d space
     */
    explicit Polygon_Area(std::vector<Point<T>> point_list)
        : points(std::move(point_list)){};
    /**
     * Calculates area of the simple polygon
     * with the [Shoelace
     * formula](https://en.wikipedia.org/wiki/Shoelace_formula)
     *
     * @returns the area of the simple polygon
     */
    T get_polygon_area() {
        /**
         * This lambda multiplies the x value of the
         * first point by the y value of the second point
         */
        auto multiply_xy_of_two_points = [](const Point<T> &first_point,
                                            const Point<T> &second_point) {
            return first_point.x * second_point.y;
        };
        auto first_point = points.begin();             // first point iterator
        auto last_point = std::prev(points.end(), 1);  // last point iterator
        auto first_term =
            std::inner_product(points.begin(), std::prev(points.end(), 1),
                               std::next(points.begin(), 1), 0, std::plus<T>(),
                               multiply_xy_of_two_points);
        auto second_term = std::inner_product(
            std::next(points.begin(), 1), points.end(), points.begin(), 0,
            std::plus<T>(), multiply_xy_of_two_points);
        return 0.5 * std::abs(first_term - second_term +
                              last_point->x * first_point->y -
                              first_point->x * last_point->y);
    }
};
}  // namespace polygon_area
}  // namespace geometry

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // Area of polygon enclosed by points (0,0), (0,1), (1,1), (2,0). Expected
    // value is 1.5
    std::vector<geometry::polygon_area::Point<double>> v = {
        {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {2.0, 0.0}};
    geometry::polygon_area::Polygon_Area<double> p(v);
    assert(p.get_polygon_area() == 1.5);
    std::cout << "Test 1: passed" << std::endl;
    // Area of polygon enclosed by points (0,0), (0,1), (1,0). Expected value is
    // 0.5
    std::vector<geometry::polygon_area::Point<double>> v1 = {
        {0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}};
    geometry::polygon_area::Polygon_Area<double> p1(v1);
    assert(p1.get_polygon_area() == 0.5);
    std::cout << "Test 2: passed" << std::endl;
    // Area of polygon enclosed by points (3, 4), (5, 11), (12, 8), (9, 5), (5,
    // 6). Expected value is 30
    std::vector<geometry::polygon_area::Point<int>> v2 = {
        {3, 4}, {5, 11}, {12, 8}, {9, 5}, {5, 6}};
    geometry::polygon_area::Polygon_Area<int> p2(v2);
    assert(p2.get_polygon_area() == 30);
    std::cout << "Test 3: passed" << std::endl;
}
