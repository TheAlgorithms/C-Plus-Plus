/**
 * @file
 * @brief Implementation of reversing a  queue using a
 * stack(https://www.geeksforgeeks.org/reversing-a-queue/)
 * @details This algorithm pushes a queue's elements into a stack
 * then proceeds to pop out its elements, effectively reversing it
 * @author [Elizabeth Choy](https://github.com/ripeliz)
 */

#include <cassert>   //for assert
#include <iostream>  // for IO operations
#include <queue>     // for queue
#include <stack>     // for stack

/**
 * @namespace operations_on_datastructures
 * @brief Operations on Data Structures
 */
namespace operations_on_datastructures {

/**
 * @brief Prints a queue.
 * @param A reference to the queue.
 * @returns void.
 */
void print(std::queue<int> q) {
    for (int i = 0; i < q.size(); i++) {
        std::cout << q.front();
        q.pop();
    }
}

/**
 * @brief Reverses a queue by utilizing a stack to pop off the elements in
 * reverse.
 * @param A reference to the queue to be reversed.
 * @returns The reversed queue.
 */
std::queue<int> reverse(std::queue<int>& q) {
    std::queue<int> reversed;
    std::stack<int> stk;
    while (!q.empty()) {
        stk.push(q.front());
        q.pop();
    }
    while (!stk.empty()) {
        reversed.push(stk.top());
        stk.pop();
    }
    return reversed;
}

}  // namespace operations_on_datastructures

/**
 * @namespace tests
 * @brief for testing purposes.
 */
namespace tests {
using operations_on_datastructures::print;
using operations_on_datastructures::reverse;

/**
 * @brief A Test to check a simple case
 * @returns void
 */
void test1() {
    std::cout << "Test 1:" << std::endl;
    std::cout << "Queue =  {1, 2, 3, 4, 5}" << std::endl;
    std::cout << "Reversed Queue = {5, 4, 3, 2, 1}" << std::endl;
    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    std::queue<int> res = reverse(q);
    std::queue<int> expected;
    assert(res == expected);
    print(res);
    std::cout << "Test 1 passed!";
}

/**
 * @brief A Test to check a very large qyeye
 * @returns void
 */
void test2() {
    std::cout << "Test 2:" << std::endl;
    std::cout << "Queue =  {1, 2, 3, 4, 5, ... 200}" << std::endl;
    std::cout << "Reversed Queue = {200, 199, 198, 197, 196, ... 1}"
              << std::endl;
    std::queue<int> q;
    for (int i = 0; i <= 200; i++) {
        q.push(i);
    }
    std::queue<int> res = reverse(q);
    std::queue<int> expected;
    assert(res == expected);
    print(res);
    std::cout << "Test 2 passed!";
}

/**
 * @brief A Test to check an empty queue
 * @returns void
 */
void test3() {
    std::cout << "Test 3:" << std::endl;
    std::cout << "Queue =  {}" << std::endl;
    std::cout << "Reversed Queue = {}" << std::endl;
    std::queue<int> q;
    std::queue<int> res = reverse(q);
    std::queue<int> expected;
    assert(res == expected);
    print(res);
    std::cout << "Test 3 passed!";
}
}  //  namespace tests

/**
 * @brief Function to test the correctness of reverse()
 * @returns void
 */
static void test() {
    tests::test1();
    tests::test2();
    tests::test3();
}

/**
 * @brief main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}