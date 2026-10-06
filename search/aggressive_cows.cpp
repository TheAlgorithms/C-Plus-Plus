/**
 * @author [Aarti Gawade](https://github.com/aartigawade2586)
 * @file aggressive_cows.cpp
 * @brief Aggressive Cows problem using binary search.
 * (https://www.spoj.com/problems/AGGRCOW/)
 * problem from the USACO February 2005 Gold Division.
 */
/* Aggressive cow
 *Problem :
 * There is a farmer whose cows are really aggressive.
 * Now he has one shelter with multiple stalls for the cows, where one cow
 * can occupy one stall.
 * The number of each stall represents its position.
 * If we are given stall positions 1 and 5, then the distance between
 * these two stalls will be 4, i.e., '5 - 1'.
 * Here, as the cows are aggressive, we need to allocate them stalls in such
 * a way that there is a maximum distance between any two cows.
 * As the cows are aggressive, to avoid them fighting, we need to keep them
 * away from each other.
 * The minimum distance between any two cows must be maximized.
 */
/*
  ###Time and Space complexity
 * Time complexity in worst case is  O(n log n + n log(maxDistance))
 * Time complexity for best case is O(n log n)
 * Time complexity for average case is O(n log n + n log(maxDistance))
 * Space complexity is O(1) , excluding sorting overhead
 */
#include <algorithm>  // for std::sort function
#include <cassert>    /// for std::assert
#include <iostream>   // for IO operations
#include <vector>     // for std::vector
using namespace std;
/**********************************************************************************************************
 **********************************************************************************************************
 */
// checking if given distance is valid for given number of cows
bool isValid(int mid, int n, const vector<int>& stalls) {
    int lastPosition = stalls[0],
        cowsPlaced =
            1;  // lastPositon represents last position at which cow is placed
    // cowsPlaced represents number cows placed
    for (int i = 1; i < stalls.size(); i++) {
        if ((stalls[i] - lastPosition) >= mid) {
            ++cowsPlaced;
            lastPosition = stalls[i];
        }
    }
    if (cowsPlaced >= n)
        return true;  //// If all cows can be placed, try a larger minimum
                      /// distance.
    else
        return false;
}
/*****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************
 */
// Will return maximum minimum distance between two cows
int aggressiveCows(vector<int>& stalls, int n) {
    int answer = 0;
    sort(stalls.begin(), stalls.end());  // Sorting array first
    // Here we are sorting array that we can access stalls sequentially rather
    // than accessing them randomly
    int st = 1, end = stalls[stalls.size() - 1] -
                      stalls[0];  // st represents possible minimum distance
                                  // between 2 cows
    // end represents maximum distance in between 2 cows
    // Here due to sorting maximum distance between 2 cows will be distance
    // between last cow and first cow
    while (st <= end) {
        int mid = st + (end - st) / 2;
        if (isValid(mid, n, stalls)) {
            answer = mid;
            st = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return answer;
}
/**
 * @brief Self-test implementation #1
 * @returns void
 */
static void test1() {
    std::vector<int> stalls = {1, 3, 5, 7};

    int expected = 6;
    int result = aggressiveCows(stalls, 2);

    std::cout << "Test #1: ";
    assert(result == expected);
    std::cout << "Passed!" << std::endl;
}
/**
 * @brief Self-test implementation #2
 * @returns void
 */
static void test2() {
    std::vector<int> stalls = {2, 5, 8, 3, 9};

    int expected = 3;
    int result = aggressiveCows(stalls, 3);

    std::cout << "Test #2: ";
    assert(result == expected);
    std::cout << "Passed!" << std::endl;
}
/**
 * @brief Self-test implementation #3
 * @returns void
 */
static void test3() {
    std::vector<int> stalls = {1, 2, 4, 8};

    int expected = 1;
    int result = aggressiveCows(stalls, 4);

    std::cout << "Test #3: ";
    assert(result == expected);
    std::cout << "Passed!" << std::endl;
}
/*************************************************************************************************************
 *************************************************************************************************************
 *************************************************************************************************************
 */
int main() {
    test1();  // run self-test implementation #1
    test2();  // run self-test implementation #2
    test3();  // run self-test implementation #3
    return 0;
}