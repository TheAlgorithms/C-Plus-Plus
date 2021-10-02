/**
 * @file
 * @brief Construct convex hull from points using Graham's Scan.
 * @author Ayman Azzam
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

struct point {
    double x, y;
};

/**
 * @brief Compare two points
 * @param a the first point
 * @param b the second point
 * @returns `true` if the first point is on the left of the second point
 * or the first point is below the second point if they have the same x value
 * @returns `false` otherwise
 */
bool compare(point a, point b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

/**
 * @param a the first point
 * @param b the second point
 * @param c the third point
 * @returns `true` if orientation of the three points is clockwise
 * @returns `false` otherwise
 */
bool cw(point a, point b, point c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
}

/**
 * @param a the first point
 * @param b the second point
 * @param c the third point
 * @returns `true` if orientation of the three points is counter clockwise
 * @returns `false` otherwise
 */
bool ccw(point a, point b, point c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}

/**
 * @brief it make cw check if check_type = 1 and ccw check if check_type = 2
 * @param check_type the type check which is !cw or !ccw
 * @param a the first point
 * @param b the second point
 * @param c the third point
 */
bool check(int check_type, point a, point b, point c) {
    switch (check_type) {
        case 1:
            return !cw(a, b, c);
        case 2:
            return !ccw(a, b, c);
        default:
            cout << "ERROR: This check type isn't exist";
            return false;
    }
}

/**
 * @brief
 * it adds the current point to the convex hull
 * and remove any unnecessary points
 * @param convex_hull the convex hull to add the point to
 * @param current the point to add it to the convex hull
 * @param type the type which upper convex hull or lower
 */
void add_point(vector<point>& convex_hull, point current, int type) {
    point last, second_last;

    last = convex_hull[convex_hull.size() - 1];
    second_last = convex_hull[convex_hull.size() - 2];

    /*** remove the points inside the convex hull ***/
    /*** which isn't an edge in the convex hull ***/
    while (convex_hull.size() >= 2 && check(type, second_last, last, current)) {
        convex_hull.pop_back();
        last = convex_hull[convex_hull.size() - 1];
        second_last = convex_hull[convex_hull.size() - 2];
    }

    convex_hull.push_back(current);
}

/**
 * @param points The point to be included in the convex hull
 * @return the minimum convex hull edges that include all the points
 */
void convex_hull_construction(vector<point>& points) {
    if (points.size() == 1)
        return;

    /*********** sort the points ascending based on the x axis ***********/
    sort(points.begin(), points.end(), &compare);

    /*********** get the left most point and right most point ***********/
    point left_point = points[0], right_point = points.back(), current;

    /*** get the upper/lower convex hulls for the left/right most points ***/
    vector<point> up_hull, low_hull;
    up_hull.push_back(left_point);
    low_hull.push_back(left_point);
    for (int i = 1; i < points.size(); i++) {
        current = points[i];
        /*** if the current point in the upper convex hull ***/
        if (i == points.size() - 1 || cw(left_point, current, right_point))
            /*** add the current point to the upper convex hull ***/
            add_point(up_hull, current, 1);

        /*** if the current point in the lower convex hull ***/
        if (i == points.size() - 1 || ccw(left_point, current, right_point))
            /*** add the current point to the lower convex hull ***/
            add_point(low_hull, current, 2);
    }

    points.clear();
    for (int i = 0; i < up_hull.size(); i++) points.push_back(up_hull[i]);
    for (int i = low_hull.size() - 2; i > 0; i--) points.push_back(low_hull[i]);
}

/**
 * small test for the convex hull construction
 */
static void test() {
    vector<point> points;
    point p1, p2, p3, p4, p5;
    p1.x = 6;
    p1.y = 12;
    p2.x = 4;
    p2.y = 12;
    p3.x = 2;
    p3.y = 10;
    p4.x = 5;
    p4.y = 10;
    p5.x = 4;
    p5.y = 8;

    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);
    convex_hull_construction(points);

    vector<point> expected = {{2, 10}, {4, 12}, {6, 12}, {4, 8}};
    for (int i = 0; i < points.size(); i++) {
        assert(points[i].x == expected[i].x);
        assert(points[i].y == expected[i].y);
    }
}

int main() {
    test();
    return 0;
}
