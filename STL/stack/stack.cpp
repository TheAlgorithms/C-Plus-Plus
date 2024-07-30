#include <bits/stdc++.h>
using namespace std;
// stack is the LIFO -> last in first out
// in stack there are only 3 generic functions which are push( or emplace ), pop and top, and some extra like size() and etc.
// push -> pushes the element into the stack
// pop -> removes the top most element of the stack
// top -> returns the top most element of the stack
// all the operations of the stack are of O(1) time complexity

int Stack()
{
    stack<int> a;
    a.push(234);   // {234}   pushes the element into the top of the stack
    a.emplace(23); //{234,23}
    a.push(89);    // {234,23,89}
    a.push(892);   // {234,23,89,892}
    a.push(63);    // {234,23,89,892,63}

    a.pop(); // removes the top most element of the stack

    cout << (a.top()) << endl; // returns the top most element of the stack

    cout << (a.size()) << endl; // returns the size of the stack

    for (auto it : a)
        cout << it << endl;
}
int main()
{
    Stack();
    return 0;
}