#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>

namespace greedy_algorithms{

/**
 * @brief A class that provides methods to separate the digits of a large
 * positive number.
 */
    class DigitSeparation {
    public:
        /**
         * @brief Default constructor for the DigitSeparation class.
         */
        DigitSeparation() {}

        /**
         * @brief Separates the digits of a large positive number into a vector in
         * reverse order.
         *
         * @param largeNumber The large number to separate digits from.
         * @return A vector of digits in reverse order.
         */
        std::vector<long long> digitSeparationReverseOrder(
            long long largeNumber) const;

        /**
         * @brief Separates the digits of a large positive number into a vector in
         * forward order.
         *
         * @param largeNumber The large number to separate digits from.
         * @return A vector of digits in forward order.
         */
        std::vector<long long> digitSeparationForwardOrder(
            long long largeNumber) const;
    };

    /**
     * @brief Implementation of digitSeparationReverseOrder method.
     *
     * @param largeNumber The large number to separate digits from.
     * @return A vector of digits in reverse order.
     */
    std::vector<long long> DigitSeparation::digitSeparationReverseOrder(
        long long largeNumber) const {
        std::vector<long long> result;
        if (largeNumber != 0) {
            while (largeNumber != 0) {
                result.push_back(std::abs(largeNumber % 10));
                largeNumber /= 10;
            }
        } else {
            result.push_back(0);
        }
        return result;
    }

    /**
     * @brief Implementation of digitSeparationForwardOrder method.
     *
     * @param largeNumber The large number to separate digits from.
     * @return A vector of digits in forward order.
     */
    std::vector<long long> DigitSeparation::digitSeparationForwardOrder(
        long long largeNumber) const {
        std::vector<long long> result = digitSeparationReverseOrder(largeNumber);
        std::reverse(result.begin(), result.end());
        return result;
    }
}

int main() {
    greedy_algorithms::DigitSeparation ds;

    // Test case: Positive number
    long long number = 1234567890;
    std::vector<long long> expectedReverse = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<long long> expectedForward = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    // Testing reverse order
    std::vector<long long> reverseOrder = ds.digitSeparationReverseOrder(number);
    assert(reverseOrder == expectedReverse);

    // Testing forward order
    std::vector<long long> forwardOrder = ds.digitSeparationForwardOrder(number);
    assert(forwardOrder == expectedForward);

    // Test case: Single digit number
    number = 5;
    expectedReverse = {5};
    expectedForward = {5};

    reverseOrder = ds.digitSeparationReverseOrder(number);
    assert(reverseOrder == expectedReverse);

    forwardOrder = ds.digitSeparationForwardOrder(number);
    assert(forwardOrder == expectedForward);

    // Test case: Zero
    number = 0;
    expectedReverse = {0};
    expectedForward = {0};

    reverseOrder = ds.digitSeparationReverseOrder(number);
    assert(reverseOrder == expectedReverse);

    forwardOrder = ds.digitSeparationForwardOrder(number);
    assert(forwardOrder == expectedForward);

    // Test case: Large number
    number = 987654321012345;
    expectedReverse = {5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    expectedForward = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5};

    reverseOrder = ds.digitSeparationReverseOrder(number);
    assert(reverseOrder == expectedReverse);

    forwardOrder = ds.digitSeparationForwardOrder(number);
    assert(forwardOrder == expectedForward);

    // Test case: Negative number
    number = -987654321012345;
    expectedReverse = {5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    expectedForward = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5};

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
