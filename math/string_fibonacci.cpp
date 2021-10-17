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

/**
 * function to add two string numbers
 * \param [in] a first number in string to add
 * \param [in] b second number in string to add
 * \returns sum as a std::string
 */
std::string add(std::string a, std::string b) {
    std::string temp = "";

    // carry flag
    int carry = 0;

    // fills up with zeros
    while (a.length() < b.length()) {
        a = "0" + a;
    }

    // fills up with zeros
    while (b.length() < a.length()) {
        b = "0" + b;
    }

    // adds the numbers a and b
    for (int i = a.length() - 1; i >= 0; i--) {
        char val = static_cast<char>(((a[i] - 48) + (b[i] - 48)) + 48 + carry);
        if (val > 57) {
            carry = 1;
            val -= 10;
        } else {
            carry = 0;
        }
        temp = val + temp;
    }

    // processes the carry flag
    if (carry == 1) {
        temp = "1" + temp;
    }

    // removes leading zeros.
    while (temp[0] == '0' && temp.length() > 1) {
        temp = temp.substr(1);
    }

    return temp;
}

/** Fibonacci iterator
 * \param [in] n n^th Fibonacci number
 */
void fib_Accurate(uint64_t n) {
    std::string tmp = "";
    std::string fibMinus1 = "1";
    std::string fibMinus2 = "0";
    for (uint64_t i = 0; i < n; i++) {
        tmp = add(fibMinus1, fibMinus2);
        fibMinus2 = fibMinus1;
        fibMinus1 = tmp;
    }
    std::cout << fibMinus2;
}

/** main function */
int main() {
    int n;
    std::cout << "Enter whatever number N you want to find the fibonacci of\n";
    std::cin >> n;
    std::cout << n << " th Fibonacci is \n";
    fib_Accurate(n);

    return 0;
}
