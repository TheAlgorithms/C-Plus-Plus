#include <iostream>
#include <cmath>
#include <string>

long long karatsuba(long long x, long long y) {
    // Base case for recursion
    if (x < 10 || y < 10) {
        return x * y;
    }

    // Determine the size of the numbers
    std::string x_str = std::to_string(x);
    std::string y_str = std::to_string(y);
    int n = std::max(x_str.size(), y_str.size());
    int m = n / 2;

    // Split x and y into high and low parts
    long long power = std::pow(10, m);
    long long x_high = x / power;
    long long x_low = x % power;
    long long y_high = y / power;
    long long y_low = y % power;

    // 3 recursive calls
    long long z0 = karatsuba(x_low, y_low);                         // z0 = x0 * y0
    long long z1 = karatsuba(x_low + x_high, y_low + y_high);     // z1 = (x0 + x1)(y0 + y1)
    long long z2 = karatsuba(x_high, y_high);                       // z2 = x1 * y1

    // Combine the results
    return (z2 * std::pow(10, 2 * m)) + ((z1 - z2 - z0) * power) + z0;
}

int main() {
    long long x = 1234;
    long long y = 5678;
    long long result = karatsuba(x, y);
    std::cout << "The result of " << x << " * " << y << " is: " << result << std::endl;  // Output: 7006652
    return 0;
}

