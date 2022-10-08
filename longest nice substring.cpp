// A string s is nice if, for every letter of the alphabet that s contains, it appears both in uppercase and lowercase. For example, "abABB" is nice because 'A' and 'a' appear, and 'B' and 'b' appear. However, "abA" is not because 'b' appears, but 'B' does not.

// Given a string s, return the longest substring of s that is nice. If there are multiple, return the substring of the earliest occurrence. If there are none, return an empty string.

 // Example 1:

// Input: s = "YazaAay"
// Output: "aAa"
// Explanation: "aAa" is a nice string because 'A/a' is the only letter of the alphabet in s, and both 'A' and 'a' appear.
// "aAa" is the longest nice substring.
// Example 2:

// Input: s = "Bb"
// Output: "Bb"
// Explanation: "Bb" is a nice string because both 'B' and 'b' appear. The whole string is a substring.
// Example 3:

// Input: s = "c"
// Output: ""
// Explanation: There are no nice substrings.
// problem link-https://leetcode.com/problems/longest-nice-substring/

// approach we used string::npos its check whether  https://www.geeksforgeeks.org/stringnpos-in-c-with-examples/
// first we apply sliding window technique then pass the substring for the check of it prescence in String
// in tha fir() fun we converted to lower to upper if it is upper 


// my best approach

#include<bits/stdc++.h>
using namespace std;

bool fir(string s){
   for(int i=0;i<s.size();i++){
            char s1=s[i];
            s1=s1<=90 ? s1+32 : s1-32;
            if(s.find(s1)==string::npos)
                return false;
   }
               return true;
}
 string sassy(string stri)  {
    string res="";
    
    for(int i=0;i<stri.size();i++)
    {   string temp="";
        temp+=stri[i];
        for(int j=i+1;j<stri.size();j++)
          { 
            temp+=stri[j];
            if(fir(temp) && (temp.size()>res.size()))
                res=temp;
          }
    }
    return res;
 }         
            

    

int main(){
    string s="YazaAay",k;
    k=sassy(s);
    cout<<k;

    return 0;
}
