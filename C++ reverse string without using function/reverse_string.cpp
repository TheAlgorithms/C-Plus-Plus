
// c++ program to reverse a string without using any functions.



#include<iostream>   // iostream provides basic input and output services for C++ programs. 
using namespace std;  // namespace is a declarative region that provides a scope to the identifiers 

int main() {

    char str[100], temp;   // Here, without creating a temp variable to swap characters.
    int size = 0, i = 0;

    cout << "Enter a string:";
    cin.getline(str, 100);     // take input from the user and store into str variable.

    while (str[size] != '\0') {   //iterating the  the string using while loop.
        size++;
    }

    size = size - 1;          
    while (i < size) { 
        temp = str[i];            // Copy alphabetic characters from the given array to temp[] and reverse the string.
        str[i] = str[size];     
        str[size] = temp;
        size--;
        i++;
    }
    cout << "After reverse string:" << str;     //Return the final output string..

    return 0;
}
