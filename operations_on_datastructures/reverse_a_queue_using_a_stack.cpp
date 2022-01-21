/**
 * @file 
 * @author Alec Rothenberg 
 * @brief Reverse a queue using a stack
 * @version 0.1
 * @date 2022-01-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <cassert>
#include <queue> 
#include <stack>

namespace name{
/**
 * @brief Using two while loops, a queue is reversed by popping the values and inputting into a 
 * stack. The stack is then emptied and the values are returned in reverse order
 * to the queue
 * 
 * @tparam T 
 * @param input 
 * @return std::queue<T> 
 */
        template<class T>
        std::queue<T> reverse(std::queue<T> input) {
        // temp stack to store values from queue in
        std::stack<T> st;

        while (!input.empty()) {
            st.push() = input.front();
            input.pop();
        }

        while(!st.empty()) {
            input.push() = st.top();
            st.pop();
        }
        return input;

        }
}


