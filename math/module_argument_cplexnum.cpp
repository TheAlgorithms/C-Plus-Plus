/// c++ program to calculate de modulus and argument of a complex number
#include <cmath>
#include <iostream>
/**
 *Calculate the modulus and argument(radians) value for a complex number
 *the form of a complex number be like z=x+iy
 *so for a pair of numbers (a,b) that a represents x and b y
 *the program can calculate the modulus like 
 *|z|=sqrt(a^2+b^2)
 *and the argument like 
 *arg=arctan(y/x)
 */
struct  Numcpx {
    double x , y;
    Point(double p = 0.0, double o = 0.0){
        x = p;
        y = o;
    }
};

/**
 *The metod use the Pythagorean theorem to calcule the modulus.
 */
double modulus(Numcpx a) {
    double x_2 = std::pow(std::abs(a.x), 2);
    double y_2 = std::pow(std::abs(a.y), 2);
    return std::sqrt(x_2 + y_2 );
}

double argument(Numcpx a) {
    double resulta = atan2(a.y , a.x);
    return resulta;
}

void test() {
/**
*    for the pair numbers(4,3)
*    the result must be 5 and argument be 0.6435
*/
    Numcpx numcpx = {4 , 3};
    std::cout <<"modulus:"<< modulus(numcpx) << std::endl;
    std::cout <<"argument:"<< argument(numcpx) << std::endl;
}

void test2() {
    Numcpx numcpx = {4.6 , 3.3};
    std::cout <<"modulus:"<< modulus(numcpx) << std::endl;
    std::cout <<"argument:"<< argument(numcpx) << std::endl;
}
int main() {
  test();
  std::cout << std::endl;
  test2();
  std::cout << std::endl;
  return 0;
}
