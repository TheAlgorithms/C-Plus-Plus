/**
 * @file
 * @brief This code is a basic implementation for use of queue STL in C++.
 * @details
 * The below code includes:
 * (a) Pushing elements to STL Queue.
 * (b) Popping elements from STL Queue.
 * (c) Checking top element in the STL Queue.
 * @author abhishek vanjani(https://github.com/KillerAV)
 */

#include <iostream> /// For input output
#include <queue> /// For usage of queue
#include <cassert> /// For asserts

int main() 
{
    std::queue<int> Q;

    // Insert in Queue
    for(int i=1;i<10;i++) {
        Q.push(i);
    }

    // Traversing from Queue
    while(!Q.empty()){
        // Picking top element from the Queue
        std::cout<<Q.front()<<" ";

        // Removing elements from the top of Queue
        Q.pop();
    }
}
