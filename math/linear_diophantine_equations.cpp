/**
 * @file
 * @brief Algorithm to check whether a diophantine equation
 *  has integral exists integral roots or not.
 * @details A Diophantine equation is a polynomial equation, usually in two
 * or more unknowns, such that only the integral solutions are required.
 * example: Given three integers a, b, c representing a linear equation of
 * the form : ax + by = c. We have to determine if the equation has a solution
 * such that x and y are both integral values or not.
 * @see more on
 * https://en.wikipedia.org/wiki/Diophantine_equation
 * @author [OREO1210] (https://github.com/OREO1210)
 */

#include <bits/stdc++.h>
using namespace std;

// function to find the GCD of two numbers
int gcd(int a, int b) { return (a % b == 0) ? abs(b) : gcd(b, a % b); }

// function to check if integral solutions are possible or not.
bool isPossible(int a, int b, int c) { return (c % gcd(a, b) == 0); }

void test() {
    // test-1
    int a = 3, b = 6, c = 9;
    isPossible(a, b, c) ? cout << "Possible\n" : cout << "Not Possible\n";

    // test-2
    a = 3, b = 6, c = 8;
    isPossible(a, b, c) ? cout << "Possible\n" : cout << "Not Possible\n";

    // test-3
    a = 2, b = 5, c = 1;
    isPossible(a, b, c) ? cout << "Possible\n" : cout << "Not Possible\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */

int main() {
    test();  // execute the tests
    return 0;
}