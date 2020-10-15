/**
 * @file vector_cross_product.cpp
 *
 * @brief Calculates the cross product and the magnitude of two mathematical vectors from their direction ratios.
 *
 * @details Cross Product of two vectors gives a vector.
 * Direction Ratios of a vector are the numeric parts of the given vector. They are the tree parts of the
 * vector which determine the magnitude (value) of the vector.
 * The method of finding a cross product is the same as finding the determinant of an order 3 matrix consisting
 * of the first row with unit vectors of magnitude 1, the second row with the direction ratios of the
 * first vector and the third row with the direction ratios of the second vector.
 * The magnitude of a vector is it's value expressed as a number.
 * Let the direction ratios of the first vector, P be: a, b, c
 * Let the direction ratios of the second vector, Q be: x, y, z
 * Therefore the calculation for the cross product can be arranged as:
 * P x Q:
 *  	1	1	1
 *  	a	b	c
 *  	x	y	x
 *
 * @algorithm The direction ratios (DR) are calculated as follows:
 *  	1st DR, J:  (b * x) - (c * y)
 *  	2nd DR, A: -((a * x) - (c * x))
 *  	3rd DR, N:  (a * y) - (b * x)
 *
 * Therefore, the direction ratios of the cross product are: J, A, N
 * The following C++ Program calculates the direction ratios of the cross products of two vector.
 * The program uses a function, cross() for doing so.
 * The direction ratios for the first and the second vector has to be passed one by one seperated by a space character.
 *
 * Magnitude of a vector is the square root of the sum of the squares of the direction ratios.
 *
 * @example An example of a running instance of the executable program:
 *
 * 	Pass the first Vector: 1 2 3
 *	Pass the second Vector: 4 5 6
 *	The cross product is: -3 6 -3
 *	Magnitude: 7.34847
 */

#include <iostream>
#include <array>
#include <cmath>

/**
 * @brief cross() calculates the cross product of the passed arrays containing the direction ratios of the two mathematical vectors.
 * @param A and B, both of type std::array<double, 3>
 * @returns an array of type std::array<double, 3>
 */
std::array<double, 3> cross(std::array<double, 3> A, std::array<double, 3> B) {
	std::array<double, 3> product;
	/// Performs the cross product as shown in @algorithm.
	product[0] = (A[1] * B[2]) - (A[2] * B[1]);
	product[1] = -((A[0] * B[2]) - (A[2] * B[0]));
	product[2] = (A[0] * B[1]) - (A[1] * B[0]);
	return product;
}

/**
 * @brief mag() calculates the magnitude of the mathematical vector from it's direction ratios.
 * @param an array of type std::array<double, 3>
 * @returns an array of type std::array<double, 3>
 */
double mag(std::array<double, 3> vec) {
	double magnitude = sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]));
	return magnitude;
}

/**
 * @brief main() runs the program and asks the user to enter the direction ratios for each of the two mathematical vectors using std::cin.
 * @param none
 * @returns 0 on exit.
 */
int main() {
	std::array<double, 3> vec1;
	std::array<double, 3> vec2;

	/// Gets the values for the first vector.
	std::cout << "\nPass the first Vector: ";
	std::cin >> vec1[0] >> vec1[1] >> vec1[2];

	/// Gets the values for the second vector.
	std::cout << "\nPass the second Vector: ";
	std::cin >> vec2[0] >> vec2[1] >> vec2[2];

	/// Displays the output out.
	std::array<double, 3> product = cross(vec1, vec2);
	std::cout << "\nThe cross product is: " << product[0] << " " << product[1] << " " << product[2] << std::endl;

	/// Displays the magnitude of the cross product.
	std::cout << "Magnitude: " << mag(product) << "\n" << std::endl;

	return 0;
}
