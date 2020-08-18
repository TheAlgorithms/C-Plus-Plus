/**
 * @file
 * @brief C++ program to find factorial of given number
 */
#include <iostream> 
#include <sstream> 
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;
/** function to find factorial of given number */
unsigned int factorial(unsigned int n) {
    if (n == 0) {
    return 1;
}
    return n * factorial(n - 1);
}


/** Main function */
int main() {
    string str;
    int found = str.find("-");
    int num;
    cout << "Please enter an integer to test factorial(0-33):" << endl;
    cin >> str;
    if (str[0] == '-') {
        cout << "Integer cannot be negative" << endl;
    }
    else {
                stringstream ss;
                ss << str;
                ss >> num;
                cout << "Factorial of " << num << " is " << factorial(num) << endl;    
        
    }
    return 0;
}
