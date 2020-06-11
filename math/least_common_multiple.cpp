// Copyright 2020 @author tjgurwara99

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

int main() {
    int ans = lcm(5, 10);
    std::cout << ans << std::endl;
    return 0;
}
