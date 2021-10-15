#include <iostream>
#include <queue>

/**
 * The following code depicts the usage of C++ STL Queue.
 * The code covers following:
 * (a) Pushing elements to STL Queue.
 * (b) Popping elements from STL Queue.
 * (c) Checking top element in the STL Queue.
 */
int main() 
{
    std::queue<int> Q;

    //Insert in stack
    for(int i=1;i<10;i++) {
        Q.push(i);
    }

    //Traversing from Queue
    while(!Q.empty()){
        // Picking top element from the Queue
        std::cout<<Q.front()<<" ";

        //Removing elements from the top of Queue
        Q.pop();
    }
}
