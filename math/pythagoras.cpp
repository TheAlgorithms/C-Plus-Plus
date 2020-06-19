
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
    point(T a, T b, T c=0) : x(a), y(b), z(c) {}  // Constructor for 2D and 3D

    double distance(const point &); // Our prototype of distance method
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
 * Use system `epsilon` to compare if the result is close to expected within the
 * accuract limits
 *
 * \param [in] val1 first value to compare
 * \param [in] val2 second value to compare
 * \param [in, optional] accuracy (optional) limit to which to check result in.
 * Default value is system epsilon
 * \returns `true` if values are close within accuracy
 * \returns `false` if value are not equal within accuracy
 */
template <typename T1, typename T2>
bool are_equal(const T1 &val1, const T2 &val2,
               double accuracy = std::numeric_limits<double>::epsilon()) {
    double diff = std::abs(val1 - val2);
    if (diff <= accuracy) {
        return true;
    }

    std::cerr.precision(17);
    std::cerr << " (" << val1 << " - " << val2 << ") = " << diff << " < "
                << accuracy << "\n\t";
    return false;
}

/**
 * In this method we will test distance between coordinates.
 */
void self_test() {
    std::cout << "Test 1...";
    point<int> p_fir({2, 1, 7});
    point<int> p_sec({1, 3, 5});
    assert(p_fir.distance(p_sec) == 3);
    std::cout << "passed!\n";

    std::cout << "Test 2...";
    point<int> fir_basic({0, 0, 7});
    point<int> sec_basic({1, 0, 0});

    assert(are_equal(fir_basic.distance(sec_basic), 7.0710678118654755));
    std::cout << "passed!\n";

    std::cout << "Test 3...";
    point<int> fir_err({0, 0, 7});
    point<int> sec_err({1, 0});
    assert(are_equal(fir_basic.distance(sec_basic), 7.0710678118654755));
    std::cout << "passed!\n";

    std::cout << "Test 4...";
    point<double> p_fir4({-7.5, 7.2});
    point<double> p_sec4({-1.0, 1.5});
    assert(are_equal(p_fir4.distance(p_sec4), 8.6023252670426267));
    std::cout << "passed!\n";

    std::cout << "Test 5...";
    point<int64_t> fir_high({100, 200, 300});
    point<int64_t> sec_high({400, 500, 600});
    assert(are_equal(fir_high.distance(sec_high), 519.6152422706632));
    std::cout << "passed!\n";

    std::cout << "Test 6...";
    point<int16_t> equal_fir({-1, -2, -3});
    point<int16_t> equal_sec({-1, -2, -3});
    assert(are_equal(equal_fir.distance(equal_sec), 0));
    std::cout << "passed!\n";

    std::cout << "Test 7...";
    point<float> two_fir({-1.9, -2.5});
    point<float> two_sec({-19.2, -10.5});
    assert(are_equal(two_fir.distance(two_sec), 19.05255888325765));
    std::cout << "passed!\n";
}

/**
 * Our main function from where we will check our method.
 */
int main() {
    self_test();
    return 0;
}
