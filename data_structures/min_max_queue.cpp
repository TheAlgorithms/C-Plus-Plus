/**
 * @file
 * @brief Implementation of the Min/Max Queue Data Structure
 * @details
 * Min/Max Queue - 
 * A queue data structure that allows the following
 * operations:
 * 
 * Enque                        - O(1) (Average)
 * Dequeue                      - O(1)
 * Get maximum element in queue - O(1)
 * Get minimum element in queue - O(1)
 * 
 * @author [Chirag](https://github.com/soul0101)
 */

#include <cassert>   /// for assert
#include <iostream>
#include <deque>
#include <queue>
using std::deque;
using std::queue;

/**
 * @namespace data_structures
 * @brief Algorithms with data structures
 */

namespace data_structures {
namespace min_max_queue {
/**
 * @brief Implementation of the Min/Max Queue Class
 */
    class MinMaxQueue {
    public:
        //To maintain order of elements
        queue<int> Q;

        //Deqeue to get Minimum in O(1)
        deque<int> D_min;
        //Deqeue to get Maximum in O(1)
        deque<int> D_max;
        
        // Function to push a element
        // into the queue
        void push(int element)
        {
            Q.push(element);

            //If Queue is empty
            if (Q.size() == 0) {
                D_min.push_back(element);
                D_max.push_back(element);
            }
            else {          
                // Pop the elements out
                // until the element at
                // back is greater than
                // current element
                while (!D_min.empty() &&
                D_min.back() > element) {
                    D_min.pop_back();
                }
                D_min.push_back(element);

                // Pop the elements out
                // until the element at
                // back is lesser than
                // current element
                while (!D_max.empty() &&
                D_max.back() < element) {
                    D_max.pop_back();
                }
                D_max.push_back(element);
            }
        }
        
        // Function to pop the element
        // out from the queue
        void pop() {
            // Condition when the Minimum
            // element is the element at
            // the front of the Deque
            if (Q.front() == D_min.front()) {
                D_min.pop_front();
            }
            // Condition when the Maximum
            // element is the element at
            // the front of the Deque
            if (Q.front() == D_max.front()) {
                D_max.pop_front();
            }
            Q.pop();
        }
        
        int getMin(){
            return D_min.front();
        }

        int getMax() {
            return D_max.front();
        }
    };

}  // namespace min_max_queue
}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    data_structures::min_max_queue::MinMaxQueue q;
    // Enqueing
    q.push(3);
    assert(q.getMax() == 3);
    assert(q.getMin() == 3);
    q.push(4);
    assert(q.getMax() == 4);
    assert(q.getMin() == 3);
    q.push(0);
    assert(q.getMax() == 4);
    assert(q.getMin() == 0);
    q.push(92);
    assert(q.getMax() == 92);
    assert(q.getMin() == 0);
    q.push(12);
    assert(q.getMax() == 92);
    assert(q.getMin() == 0);
    // Dequeueing
    assert(q.getMax() == 92);
    assert(q.getMin() == 0);
    q.pop();
    assert(q.getMax() == 92);
    assert(q.getMin() == 0);
    q.pop();
    assert(q.getMax() == 92);
    assert(q.getMin() == 0);
    q.pop();
    assert(q.getMax() == 92);
    assert(q.getMin() == 12);
    q.pop();
    assert(q.getMax() == 12);
    assert(q.getMin() == 12);
    q.pop();

    std::cout << "All tests have successfully passed!" << std::endl;
}


/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */

int main(int argc, char *argv[]) {
    test();

    return 0;
}