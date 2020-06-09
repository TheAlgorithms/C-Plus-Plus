#include <cmath>
#include <iostream>
#include <cassert>

/**
 * The distance between two points in a three dimensional - 3D - coordinate system.
 * For this we have struct point where we save coordinates
 * of our points and later on calculate the distance as mentioned.
 */
struct  Point {
    int x;
    int y;
    int z;
};

/**
 * The distance between two points in a three dimensional - 3D - coordinate system
 */
int distance(Point a, Point b) {
    int x_2 = std::pow(std::abs(b.x - a.x), 2);
    int y_2 = std::pow(std::abs(b.y - a.y), 2);
    int z_2 = std::pow(std::abs(b.z - a.z), 2);
    return std::sqrt(x_2 + y_2 + z_2);
}

/**
 * In this method we will test distance between 3D coordinates.
 */
void tests() {
    Point point_fir = {2, 1, 7};
    Point point_sec = {1, 3, 5};
    assert(distance(point_fir, point_sec) == 3);

    point_fir = {0, 0, 7};
    point_sec = {1, 0, 0};
    assert(distance(point_fir, point_sec) == 7);
    
    point_fir = {-7, 0, 7};
    point_sec = {-1, 0, 1};
    assert(distance(point_fir, point_sec) == 8);
    
    point_fir = {100, 200, 300};
    point_sec = {400, 500, 600};
    assert(distance(point_fir, point_sec) == 519);
    
    point_fir = {-1, -2, -3};
    point_sec = {-1, -2, -3};
    assert(distance(point_fir, point_sec) == 0);
    
}
/**
 * Our main function from where we will check our method.
 */
int main() {
    tests();
    return 0;
}
