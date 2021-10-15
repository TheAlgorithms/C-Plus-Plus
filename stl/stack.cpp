#include <iostream>
#include <stack>
#include <cassert>

/**
 * The following code depicts the usage of C++ STL Stack.
 * The code covers following:
 * (a) Pushing elements to STL Stack.
 * (b) Popping elements from STL Stack.
 * (c) Checking top element in the STL Stack.
 */
int main() 
{
    std::stack<int> S;

    //Insert in stack
    for(int i=1;i<10;i++) {
        S.push(i);
    }

    //Traversing from stack
    while(!S.empty()){
        // Picking top element from the stack
        std::cout<<S.top()<<" ";

        //Removing elements from the top of stack
        S.pop();
    }
}
