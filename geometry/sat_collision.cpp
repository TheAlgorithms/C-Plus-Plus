/**
* @file
* @brief Implementation of the [Hyperplane Separation Theorem]
* (https://en.wikipedia.org/wiki/Hyperplane_separation_theorem) (or
* Separating Axis Theorem) for detecting collisions in 2D-space.
* @details
* Implements [Hyperplane Separation Theorem]
* (https://en.wikipedia.org/wiki/Hyperplane_separation_theorem) (or
* Separating Axis Theorem) to detect convex polygon-polygon and convex
* polygon-circle collision.
*
* Two convex objects do not overlap if there exists a line (called axis) onto
* which the two objects' projections do not overlap. The axis is a separating
* axis if a orthogonal straight line (called the separating line) can be drawn
* between the objects without colliding with either.
*
* The algorithm should run in O(n) time for polygon-X collisions and O(1) for
* circle-circle collisions, where n is the largest number of vertices that
* belongs to one of the polygons

* @author [William Fors](https://github.com/WeRiano)
*/


#include <vector>
#include <iostream>
#include <cassert>
#include <limits>

#include "sat_collision.h"

namespace geometry {

namespace collision {

/******************************* VECTOR2 **************************************/
Vec2::Vec2(double x, double y) : m_X(x), m_Y(y) {}
Vec2 Vec2::operator+(const Vec2& other) const {
    return {m_X + other.m_X, m_Y + other.m_Y};
}
Vec2 Vec2::operator-(const Vec2& other) const {
    return {m_X - other.m_X, m_Y - other.m_Y};
}
Vec2 Vec2::operator*(const double s) const {
    return {m_X * s, m_Y * s};
}
double Vec2::ScalarProjection(Vec2 other) const {
    other.Normalize();
    return DotProduct(other);
}
double Vec2::DotProduct(const Vec2& other) const {
    return m_X*other.m_X + m_Y*other.m_Y;
}
void Vec2::Normalize() {
    double len = GetLength();
    m_X /= len;
    m_Y /= len;
}
double Vec2::GetLength() const { return sqrt(m_X*m_X + m_Y*m_Y); }
double Vec2::GetX() const { return m_X; }
double Vec2::GetY() const { return m_Y; }
Vec2 operator-(const Vec2 rhs) { return {-rhs.GetX(), -rhs.GetY()}; }
/******************************************************************************/
/******************************* POLYGON **************************************/
bool Polygon::SAT(const Shape& otherShape) const {
    for(unsigned int i = 0; i < m_Vertices.size(); i++)
    {
        // Get an edge and create the axis perpendicular to it
        Vec2 edge = m_Vertices[i] - m_Vertices[(i + 1) % m_Vertices.size()];
        Vec2 axis = {-edge.GetY(), edge.GetX()};
        axis.Normalize();
        if (!OverlapOnAxis(axis, *this, otherShape)) {
            // If there is a gap on any axis, there is no collision
            return false;
        }
    }
    // If the polygons overlap for all axes (if there is no gap),
    // there (possibly) a collision. To be sure we have to check with the axes
    // defined by otherShape as well
    return true;
}
Vec2 Polygon::GetClosestVertex(Vec2 point) const {
    Vec2 closest = m_Vertices[0];
    double closestLength = (point - m_Vertices[0]).GetLength();
    for(unsigned int i = 1; i < m_Vertices.size(); i++)
    {
        Vec2 temp = m_Vertices[i];
        double len = (point - temp).GetLength();
        if (len < closestLength)
        {
            closest = temp;
            closestLength = len;
        }
    }
    return closest;
}
void Polygon::Project(Vec2 axis, double& minRes, double& maxRes) const {
    minRes = std::numeric_limits<double>::max();
    maxRes = std::numeric_limits<double>::min();
    for (unsigned int i = 0; i < m_Vertices.size(); i++)
    {
        // Keep projecting vertices onto the axis and updating the largest and
        // smallest value of the resulting interval [minRes, maxRes]
        double projValue = m_Vertices[i].ScalarProjection(axis);
        if (projValue < minRes)
        {
            minRes = projValue;
        }
        if (projValue > maxRes)
        {
            maxRes = projValue;
        }
    }
}
/******************************************************************************/
/******************************** CIRCLE **************************************/
Circle::Circle(Vec2 centre, double radius) : m_Centre(centre), m_Radius(radius)
{}
bool Circle::SAT(const Shape& otherShape) const {
    // Only 1 axis to test for a circle: the one formed with its centre minus
    // the closest vertex of the other shape.
    Vec2 closestVertex = otherShape.GetClosestVertex(m_Centre);
    Vec2 axis = closestVertex - m_Centre;
    axis.Normalize();
    return OverlapOnAxis(axis, *this, otherShape);
}
Vec2 Circle::GetClosestVertex(Vec2 point) const {
    // Not technically a vertex but the (only) closest stored point
    return m_Centre;
}
void Circle::Project(Vec2 axis, double& minRes, double& maxRes) const {
    axis.Normalize();
    minRes = (m_Centre - (axis * m_Radius)).ScalarProjection(axis);
    maxRes = (m_Centre + (axis * m_Radius)).ScalarProjection(axis);
}
/******************************************************************************/
/********************************* SAT ****************************************/
bool DoOverlap(double min1, double max1, double min2, double max2) {
    return !((max2 < min1) || (max1 < min2));
}

bool OverlapOnAxis(const Vec2& axis, const Shape& shape1,
              const Shape& shape2) {
    double min1, max1, min2, max2;
    shape1.Project(axis, min1, max1);
    shape2.Project(axis, min2, max2);
    return DoOverlap(min1, max1, min2, max2);
}

bool sat(const Shape& shape1, const Shape& shape2) {
    return shape1.SAT(shape2) && shape2.SAT(shape1);
}
/******************************************************************************/
}}
/********************************* TEST ***************************************/
/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    geometry::collision::Circle c1({2.0, 3.0}, 1.0);
    geometry::collision::Circle c2({1.5374,4.79596}, 1.0);
    geometry::collision::Circle c3({5.5, 2.0}, 2.0);

    geometry::collision::Polygon p1({{1.0, 1.0}, {3.0, 3.0}, {3.0, 1.0}});
    geometry::collision::Polygon p2({{2.0, 2.5}, {4.0, 2.7}, {3.0, 4.0}});
    geometry::collision::Polygon p3({{2.7, 4.5}, {4.6, 4.2}, {3.8, 3.4}});

    // poly-circle collision
    assert(geometry::collision::sat(p1, c1));
    assert(!geometry::collision::sat(c2, p1));
    assert(geometry::collision::sat(p2, c3));

    // poly-poly collision
    assert(geometry::collision::sat(p1, p2));
    assert(!geometry::collision::sat(p1, p3));
    assert(!geometry::collision::sat(p2, p3));

    // circle-circle collision
    assert(geometry::collision::sat(c1, c2));
    assert(!geometry::collision::sat(c1, c3));
    assert(!geometry::collision::sat(c2, c3));

    // A shape should always collide with itself
    assert(geometry::collision::sat(c1, c1));
    assert(geometry::collision::sat(p1, p1));

    std::cout << "All tests passed!" << std::endl;
}
/******************************************************************************/
/*********************************** MAIN *************************************/
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}
/******************************************************************************/