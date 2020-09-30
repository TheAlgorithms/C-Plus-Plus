// C++ program to keep track of maximum 
// element in a stack 
#include <bits/stdc++.h> 
using namespace std; 

class StackWithMax 
{ 
    // main stack 
    stack<int> mainStack; 

    // stack to keep track of max element 
    stack<int> trackStack; 

public: 
    void push(int x) 
    { 
        mainStack.push(x); 
        if (mainStack.size() == 1) 
        { 
            trackStack.push(x); 
            return; 
        } 

        // If current element is greater than 
        // the top element of track stack, push 
        // the current element to track stack 
        // otherwise push the element at top of 
        // track stack again into it. 
        if (x > trackStack.top()) 
            trackStack.push(x); 
        else
            trackStack.push(trackStack.top()); 
    } 

    int getMax() 
    { 
        return trackStack.top(); 
    } 

    int pop() 
    { 
        mainStack.pop(); 
        trackStack.pop(); 
    } 
}; 

// Driver program to test above functions 
int main() 
{ 
    StackWithMax s; 
    int flag=1;
    while(flag)
    {
       int N;
       cout<<"Enter the number you want to add : ";
       cin>>N;
       spush(N);
       cout << s.getMax() << endl;
       cout<<Want to add more(1/0) : ";
       cin>>flag;
       } 
    return 0; 
} 
