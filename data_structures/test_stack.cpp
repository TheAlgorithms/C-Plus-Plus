#include <iostream>

#include "./stack.hpp"

int main() {
    stack<int> stk;
    std::cout << "---------------------- Test construct ----------------------"
              << std::endl;
    stk.display();
    std::cout
        << "---------------------- Test isEmptyStack ----------------------"
        << std::endl;
    if (stk.isEmptyStack()) {
        std::cout << "PASS" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }
    std::cout << "---------------------- Test push ----------------------"
              << std::endl;
    std::cout << "After pushing 10 20 30 40 into stack: " << std::endl;
    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    stk.display();
    std::cout << "---------------------- Test top ----------------------"
              << std::endl;
    int value = stk.top();
    if (value == 40) {
        std::cout << "PASS" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }
    std::cout << "---------------------- Test pop ----------------------"
              << std::endl;
    stk.display();
    stk.pop();
    stk.pop();
    std::cout << "After popping 2 times: " << std::endl;
    stk.display();
    std::cout << "---------------------- Test overload = operator "
                 "----------------------"
              << std::endl;
    stack<int> stk1;
    std::cout << "stk current: " << std::endl;
    stk.display();
    std::cout << std::endl << "Assign stk1 = stk " << std::endl;
    stk1 = stk;
    stk1.display();
    std::cout << std::endl << "After pushing 8 9 10 into stk1:" << std::endl;
    stk1.push(8);
    stk1.push(9);
    stk1.push(10);
    stk1.display();
    std::cout << std::endl << "stk current: " << std::endl;
    stk.display();
    std::cout << "Assign back stk = stk1:" << std::endl;
    stk = stk1;
    stk.display();
    return 0;
}
