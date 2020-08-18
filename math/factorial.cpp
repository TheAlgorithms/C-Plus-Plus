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
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

/*check string is number or not*/
bool check_number(string str) {
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
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
        if (found != 0) {
            if (check_number(str)) {
                stringstream ss;
                ss << str;
                ss >> num;
                cout << "Factorial of " << num << " is " << factorial(num) << endl;
            }
            else
                cout << str << " is a string" << endl;
        }
    }
    return 0;
}
