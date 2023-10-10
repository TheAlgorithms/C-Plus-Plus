#include <iostream>
#include <cmath>
#include <cassert>
# define maxIterations 1000 // Maximum number of iterations to avoid infinite loops during the computation

// Define the function for which you want to find the root
// In case you want to compute bisection for some different function, you can just make changes in the return value of this function "f"
double f(double x) {
    return x * x - 4; // Here, solving for sqrt(4) = 2
}

// Bisection method
double bisection(double a, double b, double tolerance) {
    if (f(a) * f(b) >= 0) {
        std::cout << "Error: Function has the same sign at endpoints." << std::endl;
        return NAN; // Not-a-number to indicate an error
    }

    double c;

    for (int i = 0; i < maxIterations; ++i) {
        // Calculate the midpoint
        c = (a + b) / 2;

        // Check if the root has been found with the desired tolerance
        if (fabs(f(c)) < tolerance) {
            return c;
        }

        // Update the interval [a, b] based on the sign of f(c)
        if (f(c) * f(a) < 0) {
            b = c;
        } else {
            a = c;
        }
    }

    std::cout << "Warning: Maximum number of iterations reached." << std::endl;
    return c; // Return the best approximation found so far
}

void test() {
    // Test cases with known solutions
    double tolerance = 1e-6;
    
    // Test case 1: Finding the square root of 4
    double root1 = bisection(0.0, 5.0, tolerance);
    assert(std::abs(root1 - 2.0) < tolerance);   //you will have to change the parameter accordindly in case of channge in the above "f" function

}

int main() {
    double tolerance = 1e-6;
    double root = bisection(0.0, 5.0, tolerance);

    if (!std::isnan(root)) {
        std::cout << "Approximate root: " << root << std::endl;
    } else {
        std::cout << "Unable to find a root within the specified tolerance." << std::endl;
    }

    // Run the tests
    test();

    return 0;
}
