// to check whether a string is a palindrome 
// a palindrome can be considered as a string readed backwards and forwards same. 
#include<bits/stdc++.h>
using namespace std;

int main(){ 
    //declaration of a string 
    string result = "hi";  
    //creating  a copy by storing the string in another string.
    string check = result;
    //reversing the string
   int start = 0;
   int end = result.size() - 1;
   while(start<=end){
    swap(result[start], result[end]);
    start++;
    end--;
   } 
   if(result==check){
    cout<<"String is a Palindrome"<<endl;
   } 
   else{
    cout<<"String is not a Palindrome"<<endl;
   }
return 0;
}