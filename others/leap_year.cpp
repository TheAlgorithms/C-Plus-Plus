/**
 * @file
 * @brief [Leap year](https://en.wikipedia.org/wiki/Leap_year)
 * @details Determine if a given year is leap or not
 * @author [Long Nhat Nguyen](https://github.com/torn4dom4n)
 */

#include <iostream>

bool leapYear(int year) {
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
        return true;
    }
    return false;
}

int main() {
    int n = 0;
    std::cout << "Enter a year:";
    std::cin >> n;
    if (leapYear(n)) {
        std::cout << n << " is a leap year" << std::endl;
    } else {
        std::cout << n << " is not a leap year" << std::endl;
    }
    return 0;
}
