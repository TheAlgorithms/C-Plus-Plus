/**
 * @file
 * @brief A program to calculate factors of a given number
 * @author [Pradyumn Rahar](https://github.com/Hannibal404)
 */
#include <cassert>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
/**
 * Function to calculate factors of a given number.
 * @param n number whose factors we need to calculate.
 * @return all factors of number.
 */

std::vector<int64_t> factors(int64_t n) {
    std::vector<int64_t> ans;
    if (n < 1) {
        return ans;
    }
    ans.push_back(1);
    int64_t d = 0;
    if (n == 1) return ans;
    for (int i = 2; i <= static_cast<int64_t>(sqrt(n));i++) {
        if (n % i == 0) {
            ans.push_back(i);
            d = n / i;
            if (d != i) {
                ans.push_back(d);
            }
        }
    }

    ans.push_back(n);
    sort(ans.begin(), ans.end());
    return ans;
}

/** Test function
 * @returns void
 */
void tests() {
    std::cout << "Test 1:\t n=1\n";
    std::vector<int64_t> out1 = {1};
    assert(factors(1) == out1);
    std::cout << "passed\n";

    std::cout << "Test 2:\t n=5\n";
    std::vector<int64_t> out2 = {1, 5};
    assert(factors(5) == out2);
    std::cout << "passed\n";

    std::cout << "Test 3:\t n=24\n";
    std::vector<int64_t> out3 = {1, 2, 3, 4, 6, 8, 12, 24};
    assert(factors(24) == out3);
    std::cout << "passed\n";

    std::cout << "Test 4:\t n=-24\n";
    std::vector<int64_t> out4 = {};
    assert(factors(-24) == out4);
    std::cout << "passed\n";
}

/** Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
