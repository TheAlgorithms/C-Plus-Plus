/**
 * Copyright 2020 @author PaulinaQuintero
 * @file
 *
 * \brief Program to calculate the modulus and argument(radians) 
 * value for a complex number
 * the form of a complex number be like z=x+iy
 * so for a pair of numbers (a,b) that a represents x and b y
 * the program can calculate the modulus like
 * |z|=sqrt(a^2+b^2)
 * and the argument like
 * arg=arctan(y/x)
 */

#include <cmath>
#include <iostream>
#include <complex>
#include <cassert>

struct  Numcpx {
    double x , y;
};


/**
 * The method use the Pythagorean theorem to calculate the modulus.
 */
double modulus(Numcpx a) {
    double x_2 = std::pow(std::abs(a.x), 2);
    double y_2 = std::pow(std::abs(a.y), 2);
    return std::sqrt(x_2 + y_2 );
}


/**
 * This method calculates the argument of a complex number at the angle
 * that forms the real semi-axis with the segment that joins the origin
 * of coordinates and the affix of the number, arctangent of y / x
 */
double argument(Numcpx a) {
    double resulta = atan2(a.y , a.x);
    return resulta;
}



/**
* for the pair numbers(4, 3)
* the result must be 5 and argument be 0.6435
*/
void test() {
    std::complex<double>mycomplex(4.0, 3.0);
    Numcpx numcpx = {4 , 3};
    assert(modulus(numcpx) == std::abs(mycomplex));
    assert(argument(numcpx) == std::arg(mycomplex));
    std::cout <<"modulus:"<< modulus(numcpx) << std::endl;
    std::cout <<"argument:"<< argument(numcpx) << std::endl;
}

/**
* for the pair numbers(4.6, 3.3)
* the result must be 5.6612 and argument be 0.6223
*/
void test2() {
    std::complex<double> mycomplex(4.6, 3.3);
    Numcpx numcpx = {4.6 , 3.3};
    assert(modulus(numcpx) == std::abs(mycomplex));
    assert(argument(numcpx) == std::arg(mycomplex));
    std::cout <<"modulus:"<< modulus(numcpx) << std::endl;
    std::cout <<"argument:"<< argument(numcpx) << std::endl;
}


/**
* For this function we call the pair of tests
* and the results should be as expected
*/
int main() {
    test();
    std::cout << std::endl;
    test2();
    std::cout << std::endl;
    return 0;
}
