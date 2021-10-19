/**
 * @file
 * @brief [Area Formula](https://en.wikipedia.org/wiki/Area) implementations
 * @details
 * 
 * @author [Focusucof](https://github.com/Focusucof)
 */
#define _USE_MATH_DEFINES
#include <math.h> // for M_PI definition and pow()
#include <iostream> // for IO operations
#include <cassert> // for assert

/**
 * @brief area of a square (l * l)
 * @param length is the length of the square
 * @returns area of square 
 */
int square_area(int length) {
	return length * length;
}

/**
 * @brief area of a rectangle (l * w)
 * @param length is the length of the rectangle
 * @param width is the width of the rectangle
 * @returns area of the rectangle
 */
int rect_area(int length, int width) {
	return length * width;
}

/**
 * @brief area of a trangle (b * h / 2)
 * @param base is the length of the bottom side of the triangle
 * @param height is the length of the tallest point in the triangle
 * @returns area of the triangle 
 */
int triangle_area(int base, int height) {
	return base * height / 2;
}

/**
 * @brief area of a circle (pi * r^2)
 * @param radius is the radius of the circle
 * @returns area of the circle
 */
int circle_area(int radius) {
	return M_PI * pow(radius, 2);
}

/**
 * @brief area of a parallelogram (b * h)
 * @param base is the length of the bottom side of the parallelogram
 * @param height is the length of the tallest point in the parallelogram
 * @returns area of the parallelogram
 */
int parallelogram_area(int base, int height) {
	return base * height;
}

static void test() {
	// 1st test
	int area = square_area(4);
    std::cout << area;
}

int main() {
	test();
    return 0;
}
