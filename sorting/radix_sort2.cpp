/**
 * @file
 * @brief Algorith of [Radix sort](https://en.wikipedia.org/wiki/Radix_sort)
 * @author [Suyash Jaiswal](https://github.com/Suyashjaiswal)
 * @details
 * Sort the vector of integers using radix sort i.e. sorting digit by digit
 using [Counting Sort](https://en.wikipedia.org/wiki/Counting_sort) as subroutine.
 * Running time of radix is O(d*(n+b)) where b is the base for representing
 numbers and d in the max digits in input inegers and n is number of integers.
 * consider example for n = 5, aray elements = 432,234,143,332,123
 *sorting digit by digit
 *sorting according to
 *1) 1st digit place
 *=> 432,332,143,123,234
 *
 *2) 2nd digit place
 *=> 123,432,332,234,143
 *
 *3) 3rd digit place
 *=> 123,143,234,332,432
 *
 *using count sort at each step, which is stable.
 *stable => already sorted according to previous digits.
*/

// header files
#include <iostream>  // for io operations
#include <vector>    // for std::vector
#include <algorithm> // for collection of functions
/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {
    /**
    * @namespace radix_sort
    * @brief Functions for [Radix sort](https://en.wikipedia.org/wiki/Radix_sort)
    * algorithm
    */
    namespace radix_sort {
        /**
        * @brief Function to sort vector according to current digit using stable
        * sorting.
        * @returns none
        */
        void step_ith(int cur_digit,std::vector<int>& ar) {  // sorting according to current digit.
            int n = ar.size();
            std::vector<int> position(10, 0);
            for (int i = 0; i < n; i++) {
                position[(ar[i] / cur_digit) %
                         10]++;  // counting frequency of 0-9 at cur_digit.
            }
            int cur = 0;
            for (int i = 0; i < 10; i++) {
                int a = position[i];
                position[i] = cur;  // assingning starting position of 0-9.
                cur += a;
            }
            std::vector<int> temp(n);
            for (int i = 0; i < n; i++) {
                temp[position[(ar[i] / cur_digit) % 10]] =
                    ar[i];  // storing ar[i] in ar[i]'s cur_digit expected position of
                            // this step.
                position[(ar[i] / cur_digit) %
                         10]++;  // incrementing ar[i]'s cur_digit position by 1, as
                                 // current place used by ar[i].
            }
            ar = temp;
        }
        /**
        * @brief Function to sort vector digit by digit.
        * @returns none
        */
        void radix(std::vector<int>& ar) {
            int max_ele = *max_element(ar.begin(), ar.end()); // returns the max element.
            for (int i = 1; max_ele / i > 0;
                 i *= 10) {  // loop breaks when i > max_ele because no further digits
                             // left to makes changes in aray.
                step_ith(i,ar);
            }
            for (int i = 0; i < ar.size(); i++) std::cout << ar[i] << " ";
            std::cout << "\n";
        }
    }  // namespace radix_sort
}  // namespace sorting

/**
 * Function to test the above algorithm
 * @returns none
 */
static void test1() {
    std::vector<int> ar = {432, 234, 143, 332, 123};
    sorting::radix_sort::radix(ar);
}
/**
 * Function to test the above algorithm
 * @returns none
 */
static void test2() {
    std::vector<int> ar = {213, 3214, 123, 111, 112, 142,
                           133, 132,  32,  12,  113};
    sorting::radix_sort::radix(ar);
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test1();
    test2();  // execute the tests
    int n = 0;
    std::cin >> n;
    std::vector<int> ar;
    for (int i = 0; i < n; i++) {
        int x = 0;
        std::cin >> x;
        ar.push_back(x);
    }
    sorting::radix_sort::radix(ar);
    return 0;
}