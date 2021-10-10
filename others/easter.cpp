/*
 * @file
 * @brief Determines the date of Easter after 1582
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
 * You can read more about the date of Easter here:
 * https://en.wikipedia.org/wiki/Date_of_Easter
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
    int year;   ///< year Easter is on
    int month;  ///< month Easter is on
    int day;    ///< day Easter is on

    EasterYearMonthDay(int newYear, int newMonth, int newDay) {
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

EasterYearMonthDay findEaster(int y) {
    if (y > 1582) {
        int a = y % 19;   // Year's location on Metonic Calendar
        int b = y / 100;  // Century index
        int c = y % 100;
        int d = b / 4;
        int e = b % 4;  // Takes into account leap years
        int f = (b + 8) / 25;
        int g = (b - f + 1) / 3;
        int h = (19 * a + b - d - g + 15) %
                30;  // Days from Mar. 21st until the full moon
        int i = c / 4;
        int k = c % 4;
        int r = (32 + 2 * e + 2 * i - h - k) %
                7;  // The number of days from Paschal full moon to next Sunday
        int m = (a + 11 * h + 22 * r) / 451;
        int n = (h + r - 7 * m + 114) / 31;  // Month of Easter
        int p = (h + r - 7 * m + 114) % 31;  // p + 1 is the day of Easter

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

static void test() {
    /*
     * @brief Inputting different year values and comparing the outputs to a
     * calendar
     */

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

// Main
int main() {
    test();
    return 0;
}
