/**
 * @file
 * @brief This program aims at checking that the given number is perfect square or not
 * @author [Aman Deep](https://github.com/AmanDeep-21)
 */

#include <cassert>          // for assert
#include <iostream>         // for io operations

/**
 * @brief Getting the integral square root of the number using binary search
 * @param num number to be checked
 * @returns int64_t integral part of the square root of @param 'num'
 */
int64_t get_integral_square_root(int64_t num){
    int64_t low = 0;                        // using inclusion exclusion binary search, low = minimum possible
    int64_t high = num + 1;                 // high = any larger value which could never be the answer
    
    while(high - low > 1){
        int64_t mid = (low + high) >> 1;
        if(mid * mid <= num){
            low = mid;                  // if conditions looks good, we increase low
        }
        else{
            high = mid;                 // otherwise we decrease high
        }
    }
    
    return low;
}

/**
 * @brief Method to check that given number is perfect square or not
 * @param num number to be checked
 * @returns bool if number is perfect square, it returns @ true, else it returns @ false
 */
bool check_perfect_square(int64_t num){
    if(num < 0) return false;           // square of real numbers can never be negative 
    
    int64_t value = get_integral_square_root(num);
    return value * value == num;
}

/**
 * @brief 1st test case
 * @returns void
 */
static void test1(){
    int64_t test_case_1 = check_perfect_square(-4);
    assert(test_case_1 == false);
}

/**
 * @brief 2nd test case
 * @returns void
 */
static void test2(){
    int64_t test_case_2 = check_perfect_square(1);
    assert(test_case_2 == true);
}

/**
 * @brief 3rd test case
 * @returns void
 */
static void test3(){
    int64_t test_case_3 = check_perfect_square(2);
    assert(test_case_3 == false);
}

/**
 * @brief 4th test case
 * @returns void
 */
static void test4(){
    int64_t test_case_4 = check_perfect_square(4);
    assert(test_case_4 == true);
}

/**
 * @brief 5th test case
 * @returns void
 */
static void test5(){
    int64_t test_case_5 = check_perfect_square(8);
    assert(test_case_5 == false);
}

/**
 * @brief Method for testing the 
 * check_perfect_square() with 
 * all the test cases.
 *
 * @returns void
 */
static void test() {
    // First test
    test1();
    // Second test
    test2();
    // Third test
    test3();
    // Fourth test
    test4();
    // Fifth test
    test5();
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    std::cout << "Success." << std::endl;
    return 0;
}
