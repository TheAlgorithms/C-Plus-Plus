/**
 * @file
 * @brief This code is a basic implementation for use of stack STL in C++.
 * @details
 * The below code includes:
 * (a) Pushing elements to STL Stack.
 * (b) Popping elements from STL Stack.
 * (c) Checking top element in the STL Stack.
 * @author abhishek vanjani(https://github.com/KillerAV)
 */

#include <iostream> /// For input output
#include <stack> /// For usage of stack
#include <cassert> /// For asserts

int main() 
{
    std::stack<int> S;

    // Insert in stack
    for(int i=1;i<10;i++) {
        S.push(i);
    }

    // Traversing from stack
    while(!S.empty()){
        // Picking top element from the stack
        std::cout<<S.top()<<" ";

        // Removing elements from the top of stack
        S.pop();
    }
}
