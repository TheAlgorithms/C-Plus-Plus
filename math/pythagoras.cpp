/**
 * Copyright 2020 @author beqakd
 * @file
 *
 * A basic implementation of 3d distance between two point.
 */

#include <cassert>  // For testing(assert)
#include <cmath>    // For std::pow(), std::sqrt() and so on
#include <iostream> // For io operations

/**
 * The distance between two points in a three dimensional - 3D - coordinate
 * system. For this we have 3 point x, y, z.
 * Also we created method int distance which takes points and returns distance.
 */
class point {
 private:
    int x;
    int y;
    int z;

 public:
    point(int a, int b, int c)
        : x(a), y(b), z(c) {}  // Our constructor to fill coordinates.
    int distance(const point &,
                const point &);  // Our prototype of distance method.
};

/**
 * The distance between two points in a three dimensional - 3D - coordinate
 * system.
 * @param point_fir 3D coordinates of first point.
 * @param point_sec 3d coordinates of second point.
 * @return returns the distance between this two Point.
 */
int point::distance(const point &a, const point &b) {
    // calculate distance and return it.
    int x_2 = std::pow(std::abs(b.x - a.x), 2);
    int y_2 = std::pow(std::abs(b.y - a.y), 2);
    int z_2 = std::pow(std::abs(b.z - a.z), 2);
    return std::sqrt(x_2 + y_2 + z_2);
}

/**
 * In this method we will test distance between 3D coordinates.
 * This one is very basic tests
 */
void test_1() {
    point p_fir(2, 1, 7);
    point p_sec(1, 3, 5);
    assert(p_fir.distance(p_fir, p_sec) == 3);

    point fir_basic(0, 0, 7);
    point sec_basic(1, 0, 0);
    assert(fir_basic.distance(fir_basic, sec_basic) == 7);
}

/**
 * In this method we will test distance between 3D coordinates.
 * This one is more advanced tests looking edge cases and other ones.
 */
void test_2() {
    point p_fir(-7, 0, 7);
    point p_sec(-1, 0, 1);
    assert(p_fir.distance(p_fir, p_sec) == 8);

    point fir_high(100, 200, 300);
    point sec_high(400, 500, 600);
    assert(fir_high.distance(fir_high, sec_high) == 519);

    point equal_fir(-1, -2, -3);
    point equal_sec(-1, -2, -3);
    assert(equal_fir.distance(equal_fir, equal_sec) == 0);
}

/**
 * Our main function from where we will check our method.
 */
int main() {
    test_1();
    test_2();
    return 0;
}
