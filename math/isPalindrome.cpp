#include<iostream>
using namespace std;
void ispalindrome(int number) {
   int r=0,val;
   var = number;
   while(number > 0) {
      r = r * 10 + number % 10;
      number = number / 10;
   }
   if(var == r)
    cout<<var<<" is a palindrome"<<endl;
   else
    cout<<var<<" isn't a palindrome"<<endl;
}
