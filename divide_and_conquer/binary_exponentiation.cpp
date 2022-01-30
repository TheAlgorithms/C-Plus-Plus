/**
 * @file
 * @brief algorithm for faster exponentiation
 * @details
 * This is a multi-line
 * description containing links, references,
 * math equations, etc.
 * @author [Sarah Foster](https://github.com/fostersarah)
 * @see related_file.cpp, another_file.cpp
 */

#include <math.h>

#include <bitset>
#include <cassert>
#include <iostream>
using namespace std;

namespace divide_and_conquer {

/**
 * @namespace binary_exponentiation
 * @brief Functions for binary exponentiation algorithm
 * (https://cp-algorithms.com/algebra/binary-exp.html)
 */

namespace binary_exponentiation {
/**
 *@brief Helper function for the main function, that implements Binary
 * exponentiation for efficient exponent calculations
 * @param first the input integer base
 * @param second the input integer exponent
 * @returns the answer to the exponentiation
 */

// put the functions that carries out the operation here

long binary_exponentiation(long base, long power) {
    string binary = bitset<64>(power).to_string();
    long multiplier = base;
    long answer = 1;

    if (base == 0) {
        return 0;
    }

    for (long i = binary.size() - 1; i >= 0; i--) {
        if (binary.at(i) == '1') {
            answer = answer * multiplier;
        }
        multiplier = multiplier * multiplier;
    }
    return answer;
}
/**
 * @brief Function documentation
 * @tparam T this is a one-line info about T
 * @param param1 on-line info about param1
 * @param param2 on-line info about param2
 * @returns `true` if ...
 * @returns `false` if ...
 */

bool func(long param1, long param2) {
    // function statements here
    long test = binary_exponentiation::binary_exponentiation(param1, param2);
    long answer = pow(param1, param2);
    if (test != answer) {
        return false;
    }
    return true;
}
}  // namespace binary_exponentiation
}  // namespace divide_and_conquer

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /* descriptions of the following test */
    assert(divide_and_conquer::binary_exponentiation::func(2, 5) ==
           true);  // this ensures that the algorithm works as expected
    assert(divide_and_conquer::binary_exponentiation::func(5, 0) == true);
    assert(divide_and_conquer::binary_exponentiation::func(0, 5) == true);

    // can have multiple checks
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    // code here
    return 0;
}