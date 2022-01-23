/**
 * @file reverse_queue_using_stack
 * @brief reverses a queue using a stack data structure
 * @details
 * Takes in a queue of any defined type and reverses its order
 * by updating the original queue.
 * @author [Paige Harvey](https://github.com/paigeharvey)
 */


#include <iostream> /// for input and output
#include <queue> /// for queue data structure
#include <stack> /// for stack data structure
#include <stdlib.h> /// for clock time function
#include <time.h> /// for clock time function
#include <cassert> /// for assert

namespace data_structures {
namespace reverse_queue {
/**
 * Function to print the queue
 * @tparam T can be any defined data type
 * @param q is the queue being passed in
 * @return void, simply prints
 */
template<class T>
void print(std::queue<T> q) {
    while (!q.empty()) {
        std::cout << " " << q.front();
        q.pop();
    }
    std::cout << " " << std::endl;
}
/**
 * Function to reverse the queue.
 * @tparam T can be any defined data type
 * @param q is a reference to the queue that will be reversed
 * @return q, the updated, newly reversed queue
 */
template<class T>
std::queue<T> reverse(std::queue<T> &q) {
    std::stack<T> s; 

    while (!q.empty()) {
        T top = q.front();
        s.push(top);
        q.pop();
    }
    
    while (!s.empty()) {
        T t = s.top();
        q.push(t);
        s.pop();
    }

    return q;
}
/**
 * @brief Function to check if the two queues are the same (should be the same after reversal due to passing by reference)
 * @tparam T can be any defined data type
 * @param param1 the first queue passed in
 * @param param2 the second queue passed in
 * @returns `true` if the two queues return the same values in the same order
 * @returns `false` if the two queues are of different size or do not contain the same values
 */
template<class T>
bool sameQ(std::queue<T> param1, std::queue<T> param2) { 

    if (param1.size() != param2.size()) {
        return false;
    }
    for (int i = 0; i < param1.size(); i++) {
        if (param1.front() != param2.front()) {
            return false;
        }
    }
    return true;
}
}
}


int main() { 
    /** 
     * Main function, contains a simple test which can be updated to any data type
     * Also contains the assert test function.
     */
    std::queue<int> q1, q2; 
    srand(time(0)); // code to generate random numbers for random testing
    for (int i = 0; i < 10; i++) {
        q1.push(rand() % 100);
    }
    
    std::cout << "The quueue BEFORE reversal is:";
    data_structures::reverse_queue::print(q1);

    q2 = data_structures::reverse_queue::reverse(q1);
    std::cout << "The queue AFTER reversal is:";
    data_structures::reverse_queue::print(q2);

    assert(data_structures::reverse_queue::sameQ(q1, q2) == true); // self-check
}