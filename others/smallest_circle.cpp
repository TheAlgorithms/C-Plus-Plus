/**
 * @file
 * @brief Get centre and radius of the
 * [smallest circle](https://en.wikipedia.org/wiki/Smallest-circle_problem)
 * that circumscribes given set of points.
 *
 * @see [other
 * implementation](https://www.nayuki.io/page/smallest-enclosing-circle)
 */
#include <cmath>
#include <iostream>
#include <vector>

/** Define a point */
struct Point {
    double x, /**< abscissa */
        y;    /**< ordinate */

    /** construct a point
     * \param [in] a absicca (default = 0.0)
     * \param [in] b ordinate (default = 0.0)
     */
    explicit Point(double a = 0.f, double b = 0.f) {
        x = a;
        y = b;
    }
};

/** Compute the Euclidian distance between two points \f$A\equiv(x_1,y_1)\f$ and
 * \f$B\equiv(x_2,y_2)\f$ using the formula:
 * \f[d=\sqrt{\left(x_1-x_2\right)^2+\left(y_1-y_2\right)^2}\f]
 *
 * \param [in] A point A
 * \param [in] B point B
 * \return ditance
 */
double LenghtLine(const Point &A, const Point &B) {
    double dx = B.x - A.x;
    double dy = B.y - A.y;
    return std::sqrt((dx * dx) + (dy * dy));
}

/**
 * Compute the area of triangle formed by three points using [Heron's
 * formula](https://en.wikipedia.org/wiki/Heron%27s_formula).
 * If the lengths of the sides of the triangle are \f$a,\,b,\,c\f$ and
 * \f$s=\displaystyle\frac{a+b+c}{2}\f$ is the semi-perimeter then the area is
 * given by \f[A=\sqrt{s(s-a)(s-b)(s-c)}\f]
 * \param [in] A vertex A
 * \param [in] B vertex B
 * \param [in] C vertex C
 * \returns area of triangle
 */
double TriangleArea(const Point &A, const Point &B, const Point &C) {
    double a = LenghtLine(A, B);
    double b = LenghtLine(B, C);
    double c = LenghtLine(C, A);
    double p = (a + b + c) / 2;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

/**
 * Check if a set of points lie within given circle. This is true if the
 * distance of all the points from the centre of the circle is less than the
 * radius of the circle
 * \param [in] P set of points to check
 * \param [in] Center coordinates to centre of the circle
 * \param [in] R radius of the circle
 * \returns True if P lies on or within the circle
 * \returns False if P lies outside the circle
 */
bool PointInCircle(const std::vector<Point> &P, const Point &Center, double R) {
    for (size_t i = 0; i < P.size(); i++) {
        if (LenghtLine(P[i], Center) > R)
            return false;
    }
    return true;
}

/**
 * Find the centre and radius of a circle enclosing a set of points.\n
 * The function returns the radius of the circle and prints the coordinated of
 * the centre of the circle.
 * \param [in] P vector of points
 * \returns radius of the circle
 */
double circle(const std::vector<Point> &P) {
    double minR = INFINITY;
    double R;
    Point C;
    Point minC;

    /* This code is invalid and does not give correct result for TEST 3 */
    // for each point in the list
    for (size_t i = 0; i < P.size() - 2; i++)
        // for every subsequent point in the list
        for (size_t j = i + 1; j < P.size(); j++)
            // for every subsequent point in the list
            for (size_t k = j + 1; k < P.size(); k++) {
                // here, we now have picked three points from the given set of
                // points that we can use
                // viz., P[i], P[j] and P[k]
                C.x = -0.5 * ((P[i].y * (P[j].x * P[j].x + P[j].y * P[j].y -
                                         P[k].x * P[k].x - P[k].y * P[k].y) +
                               P[j].y * (P[k].x * P[k].x + P[k].y * P[k].y -
                                         P[i].x * P[i].x - P[i].y * P[i].y) +
                               P[k].y * (P[i].x * P[i].x + P[i].y * P[i].y -
                                         P[j].x * P[j].x - P[j].y * P[j].y)) /
                              (P[i].x * (P[j].y - P[k].y) +
                               P[j].x * (P[k].y - P[i].y) +
                               P[k].x * (P[i].y - P[j].y)));
                C.y = 0.5 * ((P[i].x * (P[j].x * P[j].x + P[j].y * P[j].y -
                                        P[k].x * P[k].x - P[k].y * P[k].y) +
                              P[j].x * (P[k].x * P[k].x + P[k].y * P[k].y -
                                        P[i].x * P[i].x - P[i].y * P[i].y) +
                              P[k].x * (P[i].x * P[i].x + P[i].y * P[i].y -
                                        P[j].x * P[j].x - P[j].y * P[j].y)) /
                             (P[i].x * (P[j].y - P[k].y) +
                              P[j].x * (P[k].y - P[i].y) +
                              P[k].x * (P[i].y - P[j].y)));
                R = (LenghtLine(P[i], P[j]) * LenghtLine(P[j], P[k]) *
                     LenghtLine(P[k], P[i])) /
                    (4 * TriangleArea(P[i], P[j], P[k]));
                if (!PointInCircle(P, C, R)) {
                    continue;
                }
                if (R <= minR) {
                    minR = R;
                    minC = C;
                }
            }

    // for each point in the list
    for (size_t i = 0; i < P.size() - 1; i++)
        // for every subsequent point in the list
        for (size_t j = i + 1; j < P.size(); j++) {
            // check for diameterically opposite points
            C.x = (P[i].x + P[j].x) / 2;
            C.y = (P[i].y + P[j].y) / 2;
            R = LenghtLine(C, P[i]);
            if (!PointInCircle(P, C, R)) {
                continue;
            }
            if (R <= minR) {
                minR = R;
                minC = C;
            }
        }
    std::cout << minC.x << " " << minC.y << std::endl;
    return minR;
}

/** Test case: result should be:
 * \n Circle with
 * \n radius 3.318493136080724
 * \n centre at (3.0454545454545454, 1.3181818181818181)
 */
void test() {
    std::vector<Point> Pv;
    Pv.push_back(Point(0, 0));
    Pv.push_back(Point(5, 4));
    Pv.push_back(Point(1, 3));
    Pv.push_back(Point(4, 1));
    Pv.push_back(Point(3, -2));
    std::cout << circle(Pv) << std::endl;
}

/** Test case: result should be:
 * \n Circle with
 * \n radius 1.4142135623730951
 * \n centre at (1.0, 1.0)
 */
void test2() {
    std::vector<Point> Pv;
    Pv.push_back(Point(0, 0));
    Pv.push_back(Point(0, 2));
    Pv.push_back(Point(2, 2));
    Pv.push_back(Point(2, 0));
    std::cout << circle(Pv) << std::endl;
}

/** Test case: result should be:
 * \n Circle with
 * \n radius 1.821078397711709
 * \n centre at (2.142857142857143, 1.7857142857142856)
 * @todo This test fails
 */
void test3() {
    std::vector<Point> Pv;
    Pv.push_back(Point(0.5, 1));
    Pv.push_back(Point(3.5, 3));
    Pv.push_back(Point(2.5, 0));
    Pv.push_back(Point(2, 1.5));
    std::cout << circle(Pv) << std::endl;
}

/** Main program */
int main() {
    test();
    std::cout << std::endl;
    test2();
    std::cout << std::endl;
    test3();
    return 0;
}
