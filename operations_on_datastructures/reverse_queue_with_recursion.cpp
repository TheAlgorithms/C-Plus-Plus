/**
 * @file reverse_queue_with_recursion
 * @brief reverses a queue using a recursive sequence
 * @details
 * Function that takes in a queue of any variable type and will reverse it using 
 * recursion. This function has no return variable since the queue is passed by reference.
 * @author [Caden Trca](https://github.com/clt313)
 */

#include <cassert>   /// for assert
#include <queue>     /// for queue structures
#include <iostream>  /// for inputs/outputs

using namespace std;
/**
 * @namespace operations_on_datastructures
 * @brief Operations on Data Structures
 */
namespace operations_on_datastructures {

/**
 * @brief Function to reverse queue using recursion
 * @tparam blank data type defined by user
 * @param '&q' reference to the queue to be reversed
 * @return updated reversed queue 'q'
 */

template<class T>
void reverse(queue<T> &q) {
    if (q.empty()) {
        return;
    }
    else {
        T tempData = q.front();     /// temporarily store front data
        q.pop();                    /// remove front data
        reverse(q);                 /// recursive call to reverse queue
        q.push(tempData);           /// once empty will start pushing front data from bottom
    }
}

} // namespace operations_on_data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /* will test reversing a queue containing the numbers 1 through 10*/
    queue<int> q1, q2;
    for (int i = 1; i < 11; i++){
        q1.push(i);
        q2.push(11-i);
    }

    assert(reverse(q1) == q2); // this ensures that the algorithm works as expected
    cout << "Test Passed\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}