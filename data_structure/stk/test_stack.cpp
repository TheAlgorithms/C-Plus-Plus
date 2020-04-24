#include <iostream>
#include "stack.h"
#include "stack.cpp"

using namespace std;

int main()
{
    stack<int> stk;
    cout << "---------------------- Test construct ----------------------" << endl;
    stk.display();
    cout << "---------------------- Test isEmptyStack ----------------------" << endl;
    if(stk.isEmptyStack())
        cout << "PASS" <<endl;
    else
        cout << "FAIL" <<endl;
    cout << "---------------------- Test push ----------------------" << endl;
    cout << "After pushing 10 20 30 40 into stack: "<<endl;
    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    stk.display();
    cout << "---------------------- Test top ----------------------" << endl;
    int value = stk.top();
    if (value == 40)
        cout << "PASS" <<endl;
    else
        cout << "FAIL" <<endl;
    cout << "---------------------- Test pop ----------------------" << endl;
    stk.display();
    stk.pop();
    stk.pop();
    cout << "After popping 2 times: "<< endl;
    stk.display();
    cout << "---------------------- Test overload = operator ----------------------" << endl;
    stack<int> stk1;
    cout << "stk current: "<< endl;
    stk.display();
    cout << endl << "Assign stk1 = stk "<< endl;
    stk1 = stk;
    stk1.display();
    cout << endl<< "After pushing 8 9 10 into stk1:" <<endl;
    stk1.push(8);
    stk1.push(9);
    stk1.push(10);
    stk1.display();
    cout << endl << "stk current: " <<endl;
    stk.display();
    cout << "Assign back stk = stk1:" << endl;
    stk = stk1;
    stk.display();
    return 0;
}
