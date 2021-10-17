/*
 * @file
 * @brief Determines the [Date of
 * Easter](https://en.wikipedia.org/wiki/Date_of_Easter) after 1582
 *
 * @details
 * The date of Easter is determined in each year through a calculation known as
 * "computus." Easter is celebrated on the first Sunday after the Paschal full
 * moon, which is the first full moon on or after 21 March. Determining this
 * date in advance requires a correlation between the lunar months and the solar
 * year, while also accounting for the month, date, and weekday of the Julian or
 * Gregorian calendar. The complexity of the algorithm arises because of the
 * desire to associate the date of Easter with the date of the Jewish feast of
 * Passover which, Christians believe, is when Jesus was crucified.
 *
 *
 * @author [AlternateWalls](https://github.com/AlternateWalls)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/*
 * @brief Contains information for Easter date
 */
class EasterYearMonthDay {
 public:
    uint64_t year;   ///< year Easter is on
    uint64_t month;  ///< month Easter is on
    uint64_t day;    ///< day Easter is on

    EasterYearMonthDay(uint64_t newYear, uint64_t newMonth, uint64_t newDay) {
        year = newYear;  // Assigns year to class
        month = newMonth;
        day = newDay;
    }
};

/*
 * @brief Function that finds the month and day of Easter
 * @params param1 An int "y" of the year you want to find Easter on after
 * 1582
 * @returns An instance of the easterYearMonthDay calss that contains the
 * information (Ex. 420 - 4/20 or April 20th)
 */
EasterYearMonthDay findEaster(uint64_t y) {
    if (y > 1582) {
        uint64_t a = y % 19;   // Year's location on Metonic Calendar
        uint64_t b = y / 100;  // Century index
        uint64_t c = y % 100;
        uint64_t d = b / 4;
        uint64_t e = b % 4;  // Takes into account leap years
        uint64_t f = (b + 8) / 25;
        uint64_t g = (b - f + 1) / 3;
        uint64_t h = (19 * a + b - d - g + 15) %
                     30;  // Days from Mar. 21st until the full moon
        uint64_t i = c / 4;
        uint64_t k = c % 4;
        uint64_t r =
            (32 + 2 * e + 2 * i - h - k) %
            7;  // The number of days from Paschal full moon to next Sunday
        uint64_t m = (a + 11 * h + 22 * r) / 451;
        uint64_t n = (h + r - 7 * m + 114) / 31;  // Month of Easter
        uint64_t p = (h + r - 7 * m + 114) % 31;  // p + 1 is the day of Easter

        // Assign values
        EasterYearMonthDay date(
            y, n, p + 1);  // Assign values to new instance of class

        // Return date
        return date;
    } else {
        EasterYearMonthDay date(0, 0, 0);

        // Return date
        return date;
    }
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 2003 | April 20th
    assert(findEaster(2003).month == 4);  // Should return true
    assert(findEaster(2003).day == 20);   // Should return true

    // 1910 | March 27th
    assert(findEaster(1910).month == 3);  // Should return true
    assert(findEaster(1910).day == 27);   // Should return true

    // 1877 | April 1st
    assert(findEaster(1877).month != 3);  // Should return true
    assert(findEaster(1877).day != 22);   // Should return true

    // 1400 | Invalid date
    assert(findEaster(1400).month == 0);  // Should return true
    assert(findEaster(1400).day == 0);    // Should return true
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
