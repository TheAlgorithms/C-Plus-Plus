
/**
 * Copyright 2020 @author beqakd
 * @file
 *
 * A basic implementation of 3d distance between two point.
 */

#include <cassert>   // For testing(assert)
#include <cmath>     // For std::pow(), std::sqrt() and so on
#include <iostream>  // For io operations

/**
 * The distance between two points in a three dimensional - 3D - coordinate
 * system. For this we have 3 point x, y, z.
 * Also we created method int distance which takes points and returns distance.
 */
template <typename T> class point {
 private:
    T x;
    T y;
    T z;

 public:
    /**
    * We have two constructor. First is for 3D point. it takes T type 3 value
    * and save it to our calss. Second one takes only 2 T type value and third
    * one is defoult 0 and save it into the class too.
    */
    point(T a, T b, T c) : x(a), y(b), z(c) {}  // Consructor for 3D points.
    point(T a, T b) : x(a), y(b), z(0) {}       // Second constructor for 2D points.
    double distance(const point &);             // Our prototype of distance method.
};

/**
 * The distance between two points in a three dimensional - 3D - coordinate
 * system.
 * @param point_fir 3D coordinates of first point.
 * @param point_sec 3d coordinates of second point.
 * @return returns the distance between this two Point.
 */
template <typename T> double point<T>::distance(const point &other) {
    // calculate distance and return it.
    int x_2 = std::pow(std::abs(other.x - this->x), 2);
    int y_2 = std::pow(std::abs(other.y - this->y), 2);
    int z_2 = std::pow(std::abs(other.z - this->z), 2);
    double result = std::sqrt(x_2 + y_2 + z_2);
    return result;
}

/**
 * In this method we will test distance between 3D coordinates.
 * This one is very basic tests
 */
void test_1() {
    point<int> p_fir(2, 1, 7);
    point<int> p_sec(1, 3, 5);
    assert(p_fir.distance(p_sec) == 3);

    point<int> fir_basic(0, 0, 7);
    point<int> sec_basic(1, 0, 0);
    assert(static_cast<int>(fir_basic.distance(sec_basic)) == 7);
}

/**
 * In this method we will test distance between 3D coordinates.
 * This one is more advanced tests looking edge cases and other ones.
 */
void test_2() {
    point<double> p_fir(-7.5, 0.0, 7.2);
    point<double> p_sec(-1.0, 0.0, 1.5);
    assert(static_cast<int>(p_fir.distance(p_sec)) == 8);

    point<int> fir_high(100, 200, 300);
    point<int> sec_high(400, 500, 600);
    assert(static_cast<int>(fir_high.distance(sec_high)) == 519);

    point<int> equal_fir(-1, -2, -3);
    point<int> equal_sec(-1, -2, -3);
    assert(static_cast<int>(equal_fir.distance(equal_sec)) == 0);

    point<double> two_fir(-1.9, -2.5);
    point<double> two_sec(-19.2, -10.5);
    assert(static_cast<int>(two_fir.distance(two_sec)) == 19);
}

/**
 * Our main function from where we will check our method.
 */
int main() {
    test_1();
    test_2();
    return 0;
}
