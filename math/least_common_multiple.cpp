/**
 * Copyright 2020 @author tjgurwara99
 * @file
 *
 * A simple function that finds the least common multiple
 * of two numbers using the algorithm greatest common
 * divisor of those two numbers.
 */

#include <cassert>
#include <iostream>

/*
 * First we create a function for greatest common divisor,
 * there are many ways of implementing this function. I chose to
 * use recursive function to reduce unnecessary loops.
 */
unsigned int gcd(unsigned int x, unsigned int y) {
    if (x == 0) {
        return y;
    }
    if (y == 0) {
        return x;
    }
    if (x == y) {
        return x;
    }
    if (x > y) {
        // The following is valid because we have checked whether y == 0

        int temp = x / y;
        return gcd(y, x - temp * y);
    }
    // Again the following is valid because we have checked whether x == 0

    int temp = y / x;
    return gcd(x, y - temp * x);
}

/*
 * Now we use the fact that lcm(x,y) * gcd(x,y)  = x * y
 */
unsigned int lcm(unsigned int x, unsigned int y) { return x * y / gcd(x, y); }

void tests() {
    /*
     * First test on lcm(5,10) == 10
     */

    assert(((void)"LCM of 5 and 10 is 10 but lcm function gives a different "
                  "result.\n",
            lcm(5, 10) == 10));
    std::cout << "First assertion passes: LCM of 5 and 10 is " << lcm(5, 10)
              << std::endl;

    /*
     * Second test on lcm(2,3) == 6 as 2 and 3 are coprime (prime in fact)
     */

    assert(((void)"LCM of 2 and 3 is 6 but lcm function gives a different "
                  "result.\n",
            lcm(2, 3) == 6));
    std::cout << "Second assertion passes: LCM of 2 and 3 is " << lcm(2, 3)
              << std::endl;
}

int main() {
    tests();
    return 0;
}
