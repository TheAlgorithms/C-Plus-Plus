#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <ctime>
#include <cmath>

/*
    Program that computes a^b in O(logN) time.
    It is based on formula that:
        case1) if b is even: a^b = a^(b/2) * a^(b/2) = (a^(b/2))ˆ2
        case2) if b is odd: a^b = a^((b-1)/2) * a^((b-1)/2) * a = (a^((b-1)/2))^2 * a
    We can compute a^b recursively using above algorithm.
*/

double fast_power_recursive(int64_t a, int64_t b) {
    // negative power. a^b = 1 / (a^-b)
    if (b < 0)
        return 1.0 / fast_power_recursive(a, -b);

    if (b == 0) return 1;
    int64_t bottom = fast_power_recursive(a, b >> 1);
    // Since it is integer division b/2 = (b-1)/2 where b is odd.
    // Therefore, case2 is easily solved by integer division.

    int64_t result;
    if ((b & 1) == 0)  // case1
        result = bottom * bottom;
    else  // case2
        result = bottom * bottom * a;
    return result;
}

/*
    Same algorithm with little different formula.
    It still calculates in O(logN)
*/
double fast_power_linear(int64_t a, int64_t b) {
    // negative power. a^b = 1 / (a^-b)
    if (b < 0)
        return 1.0 / fast_power_linear(a, -b);

    double result = 1;
    while (b) {
        if (b & 1) result = result * a;
        a = a * a;
        b = b >> 1;
    }
    return result;
}

int main() {
    std::srand(time(NULL));
    std::ios_base::sync_with_stdio(false);

    std::cout << "Testing..." << std::endl;
    for (int i = 0; i < 20; i++) {
        unsigned int *rand1, *rand2;
        int a = rand_r(rand1) % 20 - 10;
        int b = rand_r(rand2) % 20 - 10;
        std::cout << std::endl << "Calculating " << a << "^" << b << std::endl;
        assert(fast_power_recursive(a, b) == std::pow(a, b));
        assert(fast_power_linear(a, b) == std::pow(a, b));

        std::cout << "------ " << a << "^" << b << " = "<<
            fast_power_recursive(a, b) << std::endl;
    }

    int64_t a, b;
    std::cin >> a >> b;

    std::cout << a << "^" << b << " = "<<
        fast_power_recursive(a, b) << std::endl;

    std::cout << a << "^" << b << " = "<<
        fast_power_linear(a, b) << std::endl;

    return 0;
}
