// Program to check whether a number is an armstrong number or not
#include <cmath>
#include <iostream>
using std::cin;
using std::cout;

int main() {
    int n = 0;
    cout << "Enter a number: ";
    cin >> n;
    
    string original = to_string(n);
    bool palindrome = true ; 
    for(int i=0;i<original.length();i++)
    {
        if(original[i]!=original[original.length()-i-1])
        {
            palindrome = false;
            break;
        }
    }
    
    if(palindrome)
    {
        cout<<"It is Palindrome number"<<endl;
    }
    else
    {
        cout<<"It is not a Palindrome number"<<endl;

    }
    
    return 0;
}
