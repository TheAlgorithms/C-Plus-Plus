/**
 * @file
 * @brief A buzz number is a number that is either divisible by 7 or has last
 * digit as 7.
 */
#include <iostream>

/** main function */
int main() {
    int n, t;
    std::cin >> t;
    while (t--) {
        std::cin >> n;
        if ((n % 7 == 0) || (n % 10 == 7))
            std::cout << n << " is a buzz number" << std::endl;
        else
            std::cout << n << " is not a buzz number" << std::endl;
    }
    return 0;
}
