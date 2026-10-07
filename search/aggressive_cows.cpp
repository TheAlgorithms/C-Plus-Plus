/**
 * @author [Aarti Gawade](https://github.com/aartigawade2586)
 * @file aggressive_cows.cpp
 * @brief Solves the Aggressive Cows problem using binary search on the
 * answer.
 * @details
 * [Aggressive Cows](https://www.spoj.com/problems/AGGRCOW/)
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
 *
 * ### Time and Space complexity
 * Time complexity: \f$O(n \log n + n \log D)\f$, where D is the maximum
 * possible distance between the first and last stall.
 *
 * Space complexity: \f$O(1)\f$, excluding sorting overhead.
 */
#include <algorithm>  // for std::sort function
#include <cassert>    /// for std::assert
#include <iostream>   // for IO operations
#include <vector>     // for std::vector
namespace search {
/**
 * @brief Checks whether the given minimum distance is valid for placing
 *        the required number of cows.
 * @param minDistance Minimum distance between two cows.
 * @param cows Number of cows to place.
 * @param stalls Positions of the stalls.
 * @return true if all cows can be placed, otherwise false.
 */
bool isValid(int minDistance, int cows, const std::vector<int>& stalls) {
    int lastPosition = stalls[0],
        cowsPlaced =
            1;  // lastPositon represents last position at which cow is placed
    // cowsPlaced represents number cows placed
    for (int i = 1; i < stalls.size(); i++) {
        if ((stalls[i] - lastPosition) >= minDistance) {
            ++cowsPlaced;
            lastPosition = stalls[i];
        }
    }
    if (cowsPlaced >= cows)
        return true;  //// If all cows can be placed, try a larger minimum
                      /// distance.
    else
        return false;
}
/**
 * @brief Finds the maximum possible minimum distance between cows.
 *
 * @param stalls Positions of the stalls.
 * @param cows Number of cows to place.
 * @return Maximum possible minimum distance between any two cows.
 */
int aggressiveCows(std::vector<int>& stalls, int cows) {
    int answer = 0;
    std::sort(stalls.begin(), stalls.end());  // Sorting array first
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
        if (isValid(mid, cows, stalls)) {
            answer = mid;
            st = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return answer;
}
}  // namespace search
/**
 * @brief Runs self-tests for the Aggressive Cows solution.
 * @returns void
 */
static void test() {
    {
        std::vector<int> stalls = {1, 3, 5, 7};
        int expected = 6;
        int result = search::aggressiveCows(stalls, 2);

        std::cout << "Test #1: ";
        assert(result == expected);
        std::cout << "Passed!" << std::endl;
    }

    {
        std::vector<int> stalls = {2, 5, 8, 3, 9};
        int expected = 3;
        int result = search::aggressiveCows(stalls, 3);

        std::cout << "Test #2: ";
        assert(result == expected);
        std::cout << "Passed!" << std::endl;
    }

    {
        std::vector<int> stalls = {1, 2, 4, 8};
        int expected = 1;
        int result = search::aggressiveCows(stalls, 4);

        std::cout << "Test #3: ";
        assert(result == expected);
        std::cout << "Passed!" << std::endl;
    }
}

int main() {
    test();
    return 0;
}
