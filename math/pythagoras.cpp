/**
 * Copyright 2020 @author beqakd
 * @file
 *
 * A basic implementation of 3d distance between two point.
 */

#include <iostream> // For io operations
#include <cassert> // For testing(assert)
#include <cmath> // For std::pow(), std::sqrt() and so on

/**
 * The distance between two points in a three dimensional - 3D - coordinate
 * system. For this we have struct point where we save coordinates of our points
 * and later on calculate the distance as mentioned.
 */
class Distance {
public:
    /**
    * Point struct to save 3D coordinates.
    */
    struct Point {
        int x;
        int y;
        int z;
    };

    // Our two points to calculate distance.
    Point a;
    Point b;

    /**
    * Constructor of this class. 
    * @param point_fir 3D coordinates of first point.
    * @param point_sec 3d coordinates of second point.
    */
    Distance(const int point_fir[], const int point_sec[])
    {
        this->a = *(Point*)point_fir;
        this->b = *(Point*)point_sec;
        ;
    }

    /**
    * This method is just helper one to call private method from public class
    * and return result of distance.
    * @return distance between two given 3D point.
    */
    double calculateDistance()
    {
        double result = distance();
        return result;
    }

private:
    /**
    * The distance between two points in a three dimensional - 3D - coordinate
    * system. This method is private so it will be called from public class
    * method.
    * @return distance between two given 3D point.
    */
    int distance()
    {
        // initialaize Point a and b
        Point a = this->a;
        Point b = this->b;

        // calculate distance and return it.
        int x_2 = std::pow(std::abs(b.x - a.x), 2);
        int y_2 = std::pow(std::abs(b.y - a.y), 2);
        int z_2 = std::pow(std::abs(b.z - a.z), 2);
        return std::sqrt(x_2 + y_2 + z_2);
    }
};

/**
 * In this method we will test distance between 3D coordinates.
 * This one is very basic tests
 */
void test_1()
{

    int point_fir[3] = { 2, 1, 7 };
    int point_sec[3] = { 1, 3, 5 };
    Distance dist(point_fir, point_sec);
    assert(dist.calculateDistance() == 3);

    int fir_basic[3] = { 0, 0, 7 };
    int sec_basic[3] = { 1, 0, 0 };
    Distance dist_basic(fir_basic, sec_basic);
    assert(dist_basic.calculateDistance() == 7);
}

/**
 * In this method we will test distance between 3D coordinates.
 * This one is more advanced tests looking edge cases and other ones.
 */
void test_2()
{
    int point_fir[3] = { -7, 0, 7 };
    int point_sec[3] = { -1, 0, 1 };
    Distance dist(point_fir, point_sec);
    assert(dist.calculateDistance() == 8);

    int fir_high[3] = { 100, 200, 300 };
    int sec_high[3] = { 400, 500, 600 };
    Distance dist_high(fir_high, sec_high);
    assert(dist_high.calculateDistance() == 519);

    int equal_fir[3] = { -1, -2, -3 };
    int equal_sec[3] = { -1, -2, -3 };
    Distance dist_equal(equal_fir, equal_sec);
    assert(dist_equal.calculateDistance() == 0);
}

/**
 * Our main function from where we will check our method.
 */
int main()
{
    test_1();
    test_2();
    return 0;
}
