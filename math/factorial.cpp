/**
 * @file
 * @brief C++ program to find factorial of given number
 */
#include <iostream> 
#include <sstream> 
using std::cout;
using std::cin;
using std::endl;
/** function to find factorial of given number */
unsigned int factorial(unsigned int n) {
    if (n == 0) {
    return 1;
}
    return n * factorial(n - 1);
}


/** Main function */
int main() {
    
    int num;
    cout << "Please enter an integer to test factorial(0-33):" << endl;
    cin >> num;
    if (num<0) {
        cout << "Integer cannot be negative" << endl;
    }
    else {
                cout << "Factorial of " << num << " is " << factorial(num) << endl;    
        
    }
    return 0;
}
