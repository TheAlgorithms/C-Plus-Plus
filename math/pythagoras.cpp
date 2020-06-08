#include <math.h>

#include <iostream>

// Our class for point coordinates.
struct  Point {
    int x;
    int y;
    int z;
};

// This method just calculate pythagorian distance from a point to b.
int distance(Point a, Point b) {
    int x_2 = pow(abs(b.x - a.x), 2);
    int y_2 = pow(abs(b.y - a.y), 2);
    int z_2 = pow(abs(b.z - a.z), 2);
    return sqrt(x_2 + y_2 + z_2);
}

// Our main function.
int main() {
    // first point
    Point point_fir = {2, -1, 7};
    Point point_sec = {1, -3, 5};
    // Distance should be 3!
    std::cout << distance(point_fir, point_sec) << std::endl;
    return 0;
}
