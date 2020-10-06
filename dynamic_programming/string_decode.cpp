/**
 * @file
 * @brief Program to find the number of ways a string containing digits can be
 * decoded
 *
 * @details
 * Consider 'A' = 1, 'B' = 2, ... , 'Z' = 26
 * Given a string containing digits only, the code returns the number of ways
 * they can be decoded
 * For eg,
 * the string is '216'
 * It can be decoded as BP(2,16), UF(21,6) and BAF(2,1,6)
 *
 * @author [Anjali Jha](https://github.com/anjali1903)
 */
#include <cassert>
#include <iostream>
#include <vector>

/**
 * Function that finds the number of ways a string containing digits only can be
 * decoded
 */
int decode(std::string s) {
    int n = s.length();
    // There is no character mapping 0
    if (s[0] == '0') {
        return 0;
    }
    std::vector<int> dp(n + 1);
    dp[0] = 1;
    dp[1] = 1;
    int i;
    for (i = 2; i <= n; i++) {
        // if current digit > 0, the current cell assumes value of previous cell
        if (s[i - 1] > '0')
            dp[i] = dp[i - 1];
        // if current and previous digits form a number less than 27 or previous
        // 1 digit is 1(making the combined result between 11 to 19), current
        // cell assumes value of current-2 cell
        if ((s[i - 1] < '7' and s[i - 2] == '2') or s[i - 2] == '1')
            dp[i] += dp[i - 2];
    }
    return dp[n];
}

/** Test function */
void test() {
    // decode("216") return 3
    assert(decode("216") == 3);
    // decode("03") return 0
    assert(decode("03") == 0);
    // decode("10") return 1
    assert(decode("10") == 1);
}
/**
 * Main Function
 */
int main() {
    test();  // execute the tests
    return 0;
}
