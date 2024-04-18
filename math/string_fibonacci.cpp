/**
 * @file
 * @brief This Programme returns the Nth fibonacci as a string.
 *
 * The method used is manual addition with carry and placing it in a string
 * which is called string addition This makes it have no bounds or limits
 *
 * @see fibonacci_large.cpp, fibonacci_fast.cpp, fibonacci.cpp
 */

#include <iostream>
#ifdef _MSC_VER
#include <string>  // use this for MS Visual C
#else
#include <cstring>  // otherwise
#endif

#include <algorithm>
#include <vector>

/**
 * function to add two string numbers
 * \param [in] a first number in string to add
 * \param [in] b second number in string to add
 * \returns sum as a std::string
 */
std::string add(const std::string& a, const std::string& b) {
    std::string result;
    int carry = 0;
    for (int i = 0; i < std::max(a.size(), b.size()); i++) {
        int sum = carry;
        if (i < a.size()) sum += a[a.size() - 1 - i] - '0';
        if (i < b.size()) sum += b[b.size() - 1 - i] - '0';
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }
    if (carry) result.push_back(carry + '0');
    std::reverse(result.begin(), result.end());
    return result;
}

/** Fibonacci iterator
 * \param [in] n n^th Fibonacci number
 */
void fib_Accurate(uint64_t n) {
    std::vector<std::string> fib(n+1);
    fib[0] = "0";
    fib[1] = "1";
    for (uint64_t i = 2; i <= n; i++) {
        fib[i] = add(fib[i-1], fib[i-2]);
    }
    std::cout << fib[n];
}

/** main function */
int main() {
    uint64_t n;
    std::cout << "Enter whatever number N you want to find the fibonacci of\n";
    std::cin >> n;
    std::cout << n << " th Fibonacci is \n";
    fib_Accurate(n);

    return 0;
}
