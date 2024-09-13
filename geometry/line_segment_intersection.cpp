/**
 * @file
 * @brief check whether two line segments intersect each other
 * or not.
 */
#include <algorithm>
#include <iostream>

/**
 * Define a Point.
 */
struct Point {
    int x;  /// Point respect to x coordinate
    int y;  /// Point respect to y coordinate
};

/**
 * intersect returns true if segments of two line intersects and
 * false if they do not. It calls the subroutines direction
 * which computes the orientation.
 */
struct SegmentIntersection {
    inline bool intersect(Point first_point, Point second_point,
                          Point third_point, Point forth_point) {
        int direction1 = direction(third_point, forth_point, first_point);
        int direction2 = direction(third_point, forth_point, second_point);
        int direction3 = direction(first_point, second_point, third_point);
        int direction4 = direction(first_point, second_point, forth_point);

        if ((direction1 < 0 || direction2 > 0) &&
            (direction3 < 0 || direction4 > 0))
            return true;

        else if (direction1 == 0 &&
                 on_segment(third_point, forth_point, first_point))
            return true;

        else if (direction2 == 0 &&
                 on_segment(third_point, forth_point, second_point))
            return true;

        else if (direction3 == 0 &&
                 on_segment(first_point, second_point, third_point))
            return true;

        else if (direction3 == 0 &&
                 on_segment(first_point, second_point, forth_point))
            return true;

        else
            return false;
    }

    /**
     * We will find direction of line here respect to @first_point.
     * Here @second_point and @third_point is first and second points
     * of the line respectively. we want a method to determine which way a
     * given angle these three points turns. If returned number is negative,
     * then the angle is counter-clockwise. That means the line is going to
     * right to left. We will fount angle as clockwise if the method returns
     * positive number.
     */
    inline int direction(Point first_point, Point second_point,
                         Point third_point) {
        return ((third_point.x - first_point.x) *
                (second_point.y - first_point.y)) -
               ((second_point.x - first_point.x) *
                (third_point.y - first_point.y));
    }

    /**
     * This method determines whether a point known to be colinear
     * with a segment lies on that segment.
     */
    inline bool on_segment(Point first_point, Point second_point,
                           Point third_point) {
        if (std::min(first_point.x, second_point.x) <= third_point.x &&
            third_point.x <= std::max(first_point.x, second_point.x) &&
            std::min(first_point.y, second_point.y) <= third_point.y &&
            third_point.y <= std::max(first_point.y, second_point.y))
            return true;

        else
            return false;
    }
};

/**
 * This is the main function to test whether the algorithm is
 * working well.
 */
int main() {
    SegmentIntersection segment;
    Point first_point, second_point, third_point, forth_point;

    std::cin >> first_point.x >> first_point.y;
    std::cin >> second_point.x >> second_point.y;
    std::cin >> third_point.x >> third_point.y;
    std::cin >> forth_point.x >> forth_point.y;

    printf("%d", segment.intersect(first_point, second_point, third_point,
                                   forth_point));
    std::cout << std::endl;
}
