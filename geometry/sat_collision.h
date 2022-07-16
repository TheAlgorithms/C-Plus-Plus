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
* axis if an orthogonal straight line (called the separating line) can be drawn
* between the objects without colliding with either.
*
* The algorithm should run in O(n) time for polygon-X collisions and O(1) for
* circle-circle collisions, where n is the largest number of vertices that
* belongs to one of the polygons

* @author [William Fors](https://github.com/WeRiano)
*/

namespace geometry {

namespace collision {

/**
 * @brief 2-dimensional vector representation.
 */
class Vec2 {
 public:
    Vec2() = default;
    Vec2(double x, double y);

    /**
     * @brief Implements vector addition
     * @param other Another @Vec2
     * @return The vector sum from adding @other to @this
     */
    Vec2 operator+(const Vec2& other) const;

    /**
     * @brief Implements vector subtraction
     * @param other Another @Vec2
     * @return The vector that results from subtracting @other from @this
     */
    Vec2 operator-(const Vec2& other) const;

    /**
     * @brief Implements vector scaling
     * @param s Real scalar
     * @return @param Vec2 The vector that results from multiplying each element
     *                     of @this with @s
     */
    Vec2 operator*(const double s) const;

    /**
     * @brief Calculates the Scalar Projection of one vector onto another
     * @param other Another @Vec2
     * @return @param double The scalar projection of @other onto @this
     */
    double ScalarProjection(Vec2 other) const;

    /**
     * @brief Calculates the Dot Product of two vectors
     * @param other Another @Vec2
     * @return @param double The Dot Product of @other and @this
     */
    double DotProduct(const Vec2& other) const;

    /**
     * @brief Normalizes @this vector, changing its length to 1.
     * @return void
     */
    void Normalize();

    /**
     * @brief Helper function to calculate vector length/magnitude
     * @return @param double Length of @this vector
     */
    double GetLength() const;

    /**
     * @brief Get function for the x element.
     * @return @param double x element.
     */
    double GetX() const;

    /**
     * @brief Get function for the y element.
     * @return @param double y element.
     */
    double GetY() const;
 private:
    double m_X, m_Y;
};
/**
 * @brief Negating the x and y element of a vector
 * @param rhs @Vec2 to negate
 * @return @param Vec2 negated version of @rhs
 */
Vec2 operator-(const Vec2 rhs);


class Polygon;
class Circle;

/**
 * @brief Abstract shape
 */
class Shape {
 public:
    /**
     * @brief projects @this and @otherShape onto all the
     *        axes defined by @this and checks for overlapping
     * @param otherShape Shape pair to test overlapping against
     * @return `true` if there is no gap on any of the projections.
     * @return `false` otherwise.
     */
    virtual bool SAT(const Shape& otherShape) const = 0;

    /**
     * @brief Finds the vertex which is closest to a given point
     * @param point to compare vertices with, represented by a position vector
     * @return vertex that belongs to this shape and is closest to @point
     */
    virtual Vec2 GetClosestVertex(Vec2 point) const = 0;

    /**
     * @brief projects the shape onto an axis which creates a finite interval
     *        [minRes, maxRes]
     * @param axis to project @this shape on
     * @param minRes smallest value of the resulting line
     * @param maxRes largest value of the resulting line
     * @return void
     */
    virtual void Project(Vec2 axis, double& minRes, double& maxRes) const = 0;
};

/**
 * @brief Convex Polygon representation. Consists of a collection of vertices
 *        (which are represented by position vectors)
 */
class Polygon : public Shape {
 public:
    Polygon(std::vector<Vec2>&& vertices) : m_Vertices(std::move(vertices)) {}
    Polygon(std::vector<Vec2>& vertices) : m_Vertices(std::move(vertices)) {}

    /**
     * @brief projects @this and @otherShape onto all the
     *        axes defined by @this and checks for overlapping
     * @param otherShape Shape pair to test overlapping against
     * @return `true` if there is no gap on any of the projections.
     * @return `false` otherwise.
     * @see Shape::SAT
     */
    bool SAT(const Shape& otherShape) const override;

    /**
     * @brief Finds the vertex which is closest to a given point
     * @param point to compare vertices with, represented by a position vector
     * @return vertex that belongs to this shape and is closest to @point
     * @see Shape::GetClosestVertex
     */
    Vec2 GetClosestVertex(Vec2 point) const override;

    /**
     * @brief Implements @Shape.Project for a circle.
     * @param axis to project @this shape on
     * @param minRes smallest value of the resulting line
     * @param maxRes largest value of the resulting line
     * @return void
     * @see Shape::Project
     */
    void Project(Vec2 axis, double& minRes, double& maxRes) const override;
 private:
    std::vector<Vec2> m_Vertices;
};

/**
 * @brief Circle representation. Consists of a centre (position vector) and a
 *        radius
 */
class Circle : public Shape {
 public:
    Circle(Vec2 centre, double radius);

    /**
     * @brief implements @Shape.SAT for a circle.
     * @param otherShape Shape pair to test overlapping against
     * @return true if there is no gap on any of the projections.
     *         false otherwise.
     * @see Shape::SAT
     */
    bool SAT(const Shape& otherShape) const override;

    /**
     * @brief Implements @Shape.GetClosestVertex for a circle.
     * @param point to compare vertices with, represented by a position vector
     * @return Always returns the centre of the circle, since this is the only
     *         point (vertex) stored by the shape.
     * @see Shape::GetClosestVertex
     */
    Vec2 GetClosestVertex(Vec2 point) const override;

    /**
     * @brief Implements @Shape.Project for a circle.
     * @param axis to project @this shape on
     * @param minRes smallest value of the resulting line
     * @param maxRes largest value of the resulting line
     * @return void
     * @see Shape::Project
     */
    void Project(Vec2 axis, double& minRes, double& maxRes) const override;
 private:
    double m_Radius;
    Vec2 m_Centre;
};

/**
 * @brief Find if two intervals [min1, max1] and [min2, max2] overlaps
 * @param min1 min point of line segment 1
 * @param max1 max point of line segment 1
 * @param min2 min point of line segment 2
 * @param max2 max point of line segment 2
 * @return `true` if the line segments overlap
 * @return `false` otherwise
 */
bool DoOverlap(double min1, double max1, double min2, double max2);

/**
 * @brief Find if two shapes overlap when projected onto an axis
 * @param axis Axis to project shapes onto
 * @param shape1 First shape
 * @param shape2 Second shape
 * @return `true` if the two polygons overlap when projected onto the axis.
 * @return `false` otherwise
 */
bool OverlapOnAxis(const Vec2& axis, const Shape& shape1,
              const Shape& shape2);

/**
 * @brief Performs the SAT collision algorithm on two 2-dimensional shapes
 * @param shape1 First shape
 * @param shape2 Second shape
 * @return `true` if the shapes collide.
 * @return `false` otherwise
 */
bool sat(const Shape& shape1, const Shape& shape2);
}}