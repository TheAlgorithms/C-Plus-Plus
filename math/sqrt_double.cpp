#include <iostream>
#include <cassert>

/* Calculate the square root of any 
number in O(logn) time, 
with precision fixed */

double Sqrt(double x) {
    if ( x > 0 && x < 1 ) {
        return 1/Sqrt(1/x);
    }
    double l = 0, r = x;
    /* Epsilon is the precision. 
    A great precision is 
    between 1e-7 and 1e-12.
    double epsilon = 1e-12;
    */
    double epsilon = 1e-12;
    while ( l <= r ) {
        double mid = (l + r) / 2;
        if ( mid * mid > x ) {
            r = mid;
        } else {
            if ( x - mid * mid < epsilon ) {
                return mid;
            }
            l = mid;
        }
    }
    return -1;
}
int main() {
  double n{};
  std::cin >> n;
  assert(n >= 0);
  // Change this line for a better precision
  std::cout.precision(12);
  std::cout << std::fixed << Sqrt(n);
}
