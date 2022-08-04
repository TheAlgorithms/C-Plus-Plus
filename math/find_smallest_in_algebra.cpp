// To find the smallest values of x and y that satisfy "ax - by = 0"
#include <iostream>
#include <cassert>

namespace math
{
    // To find GCD using Euclid's algorithm
    int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        return (gcd(b, a % b));
    }

    // "ax = by" ==> x/y = b/a
    // Prints smallest value of x that satisfy "ax - by = 0"
    int findSmallestX(int a, int b)
    {
        int g = gcd(a, b);
        int x = b / g;
        return x;
    }

    // Prints smallest value of y that satisfy "ax - by = 0"
    int findSmallestY(int a, int b)
    {
        int g = gcd(a, b);
        int y = a / g;
        return y;
    }
}

// Function for testing findSmallest function
// Test cases
static void test()
{
    // a = 6, b = 18 return x = 3, y = 1
    std::cout << "Test Case 1...\n";
    assert(math::findSmallestX(6, 18) == 3);
    assert(math::findSmallestY(6, 18) == 1);
    std::cout << "Passed\n";

    // a = 25, b = 35 return x = 7, y = 5
    std::cout << "Test Case 2...\n";
    assert(math::findSmallestX(25, 35) == 7);
    assert(math::findSmallestY(25, 35) == 5);
    std::cout << "Passed\n";

    // a = 126, b = 93 return x = 31, y = 42
    std::cout << "Test Case 3...\n";
    assert(math::findSmallestX(126, 93) == 31);
    assert(math::findSmallestY(126, 93) == 42);
    std::cout << "Passed\n";

}

// Main function
int main()
{
    // Run self-test
    test();
    return 0;
}