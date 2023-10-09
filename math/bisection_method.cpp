/**
 * @file
 * @brief Program to find the roots of a conitnuous function for which two values
 * with opposite signs are known (https://en.wikipedia.org/wiki/Bisection_method)
 *
 * @details
 * The method is applicable for numerically solving the equation f(x) = 0 
 * for the real variable x, where f is a continuous function 
 * defined on an interval [a, b] and where f(a) and f(b) have opposite signs.
 *
 * let the function f(x) be any continuous function such that f(a)*f(b) < 0
 * this method takes the mid value of 'a' and 'b' [mid = (a+b)/2] and then
 * check if f(mid) = 0,
 * if not, then it recursively calls itself with intervals [a, mid] and [mid, b]
 * until the middle value of the provided interval is equal to 0 
 * (or the difference in the value of interval is < the permissible error)
 * [the condition in the above bracket is taken bcoz if the interval are so close
 * then the approximate root of the equation is around the mid value of them]
 *
 * @author [Kush Choudhary](https://github.com/kushchoudhary98)
 */
#include <cassert>    ///for assert
#include <iostream>   ///for IO operations
#include <math.h>     ///for math operations

/**
 * @brief The function f(x) whose root is to be known
 * @param x value to be evaluated in function `f`
 * @return the evaluated value of funtion `f` through x
*/
double f(double x) {
    return cos(x) - x*exp(x);
}

/**
 * @brief Function to get the root of the function `f`
 * @param a first known value
 * @param b second known value
 * @param error permissible error in calculation
 * @return Returns the value of the root of the function `f`.
 * @return Returns `-1` and a message if interval [a,b] is invalid and/or the function does not follow the required assumptions.
*/
double bisection(double a, double b, double error = 0.00001) {
    static bool flag = false;

    //if f(a)*f(b) < 0, then interval [a, b] is invalid
    if(f(a)*f(b) >= 0) {
        if(flag == false) std::cout << "The interval [a,b] provided is not valid returning value -1" << std::endl;
        return -1;
    }

    flag = true;
    double z = (a+b)/2;

    //if difference in interval is less than the `error` then return 
    //the mid as answer
    if(abs(a-b) <= error) {
        return z;
    }

    //if f(mid) = 0, then mid is the root
    if(f(z) == 0.0) {
        return z;
    }
    else {
        //recursively calling the method with interval [a, mid]
        if(f(a)*f(z) < 0) return bisection(a, z, error);

        //recursively calling the method with interval [mid, b]
        else if(f(z)*f(b) < 0) return bisection(b, z, error);

        else {
            std::cout << "The given function does not follow the required assumtions, returning -1" << std::endl;
            return -1;
        }
    }
    return z;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
void test() {
    double ans = bisection(0,1);
    ans = (std::ceil(ans * 100000))/100000;//to round upto 5 decimal places

    assert(ans == 0.51776);

    std::cout << "All tests have successfully passed!\n";
}


/**
 * @brief Main Function
 * @returns 0 on exit
 */
int main(void) {
    test(); //runs self-test implementation
    return 0;
}
