/**
 * @perfect_number.cpp
 * Tells us if a number is perfect or not
 * A number is perfect if the addition
 * of all of its factors (excluding itself)
 * add up to the number itself
 * Ex.: Factors of 6 are: 1 2 3 6
 * Their addition (not including 6):
 * 1 + 2 + 3 = 6
 * [Fredy Jose-Castaneda] (https://github.com/fredward36)
 */

#include <iostream>
#include <cassert>   /// for assert
#include<stdio.h>
#include <vector>

namespace perfect_number {
    int a;
    int divisorSum(int num) {
        if (num == 1) {
            return 0;
        }
        int sum = 0;
        std::vector<int> factors;
        /** How to get factors of a number:
        *https://www.geeksforgeeks.org/find-divisors-natural-number-set-1/ We
        *get the factors of the number first. We continuously divide the
        *number by any natural number less than it should the remainder be 0.
        * Store all the factors in a vector to be used later in the addition.
        */
        for (int i = 1; i <= num; i++) {
            if (num % i == 0) {
                factors.push_back(i);
            }
        }
        ///
        /// We don't include the number itself in the addition of its factors
        ///
        for (unsigned int i = 0; i < factors.size() - 1; i++) {
            sum += factors.at(i);
        }
        return sum;
    }

    template <class T>
    bool func(int param1, T param2) {
        // Check that param2 is actually a natural number
        scanf("%f", &param2);
        if (param2 != (int) param2) {
            return false;
        }
        return true;
    }

    static bool test() {
        std::cout << "<------ Checking if a number is perfect------>\n";
        // 1. 6 is a perfect number
        a = 6;
        if (a != divisorSum(a)) {
            std::cerr << "\tFailed 1/6 (" << a << "!= 6)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 1/6...";
        // 2. 28 is a perfect number
        a = 28;
        if (a != divisorSum(a)) {
            std::cerr << "\tFailed 2/6 (" << a << "!= 28)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 2/6...";
        // 3. 496 is a perfect number
        a = 496;
        if (a != divisorSum(a)) {
            std::cerr << "\tFailed 3/6 (" << a << "!= 496)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 3/6...";
        // 4. 10 is not a perfect number
        a = 10;
        if (a == divisorSum(a)) {
            std::cerr << "\tFailed 3/6 (" << divisorSum(a) << "== 10)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 3/6...";
        // 5. 34 is prime, therefore not perfect
        a = 34;
        if (a != divisorSum(a)) {
            std::cerr << "\tFailed 3/6 (" << divisorSum(a) << "!= 34)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 3/6...";
        // 6. 1 cannot be a perfect number.
        a = 1;
        if (a == divisorSum(a)) {
            std::cerr << "\tFailed 3/6 (" << divisorSum(a) << "!= 1)" << std::endl;
            return false;
        }
        std::cout << "\tPassed 3/6...";
    }

}