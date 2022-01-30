/**
 * @file
 * @brief Function to determine whether a string is a palindrome using stack
 */

#include <cassert>   /// for assert
#include <stack>   //for stack
#include <string> // for strings
#include <iostream> //for main input

//using std namespace as it will not interefere with any we are using libraries
using namespace std;

 /**
  * This bool function returns true if the string entered is a palindrome, and false if the string
  * is not a palindrome
  */
bool IsPalindrome(string input) {
    
    bool isTrue = true;
    stack<char> paliCheck;
    int stringLen = input.size();

    //intializing our increment variable outside of the for loop to later use it to keep track of iteration of stack
    int i = 0;
    
    //pushing half of the input string into the stack, and then compare the second half
    for (i = 0; i < stringLen / 2; i++)
        paliCheck.push(input[i]);

    //If the string is an odd amount we must incremenet by 1 as the middle is irrelevant to determine if the string is a palindrome
    if (stringLen % 2 == 1)
        i++;

    /*Iterating through the stack the remaining of the string, comparing whether characters are the same, if they are not we break 
    * and return false 
    */
    for (; i < stringLen; i++) {
        if (input[i] != paliCheck.top()) {
            isTrue = false;
            break;
        }

        //iterating through stack by popping top element
        paliCheck.pop();
    }

    return isTrue;
}


/**
 * @brief Main will just be asking the user for input of of our isPalindrome function, and displaying
 * @returns 0 on exit
 */
int main() {
    std::cout << "Enter string: ";
    string input;
    std::cin >> input;

    //displays result of palindrome function
    if (IsPalindrome(input)) { 
        cout << input << " is a palindrome!";
    }
    else {
        cout << input << " is NOT a palindrome!";
    }
    


    return 0;
}