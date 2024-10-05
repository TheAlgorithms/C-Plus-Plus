/**
* 3.Longest_Substring_Without_Repeating_Characters
* Problem link :- https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
* Intiuation :
  Intuition is strightforward and simple, we track the frequencey and as we know we can't use string to track longest substring without repeating characters, as poping a char from front of string is not in O(1) which could be optimized by deque approch.
* Approch :
    1) At first we initialize a unordered_map to track the frequncy and then.
    2) We initialize deque for pushing the characters and if temp > res we update our res deque to temp as we need longest substring here.
    3) And while loop is used to reduce the frequency from front doing i++ and removing charecters from temp deque as we no longer need them.
    4) return res.size() as we only need size not string.
* Time Complexity :
  O(N)
  
* Space Complexity :
  O(N)
* Examples:-
  testcase1:- s = "abcabcbb", o/p = 3.
  testcase2:- s = "bbbbb", o/p = 1.
  testcase3:- s = "pwwkew", o/p = 3.
* I hope this helps to understand.
* Thank you!!
**/

// ----------------- Header files ----------------------------------
#include <iostream> // for input and output read/write.
#include <unordered_map> // to use it for character frequency.
#include <deque> // for push and pop operations at O(1) time.
#include <string> // for taking string as input

using namespace std; // using the namspace standard to reduce the redundent usage of std:: when calling functions (basically reduicng an extra overhead).

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // if size of string is 1 then it will be the answer.
        if(s.size()==1) return 1;

        // map used to store the characters frequency.
        unordered_map<char,int>m;
        int n = s.length();

        // dequeue to remove from back if repeating charcters are present.
        deque<char>temp;
        deque<char>res;
        int i,j;
        for(i=0,j=0;i<n && j<n;) {
            m[s[j]]++;

            if(m[s[j]]>1) {
                if(temp.size()>res.size()) {
                    res = temp;
                }

                while(m[s[j]]>1) {
                    // as repeating charecter is present pop_front() is called.
                    temp.pop_front();
                    m[s[i]]--;
                    i++;
                }
            }

            temp.push_back(s[j]);
            j++;
        }

        if(temp.size()>res.size()) {
            res = temp;
        }

        return res.size();
    }
};

//-------------------- Main function -------------------------------
int main() {
  // object of class Solution created for function call.
  Solution soln;


  // user inputted string. 
  string s;
  cout<<"Enter the string : "<<endl;
  cin>>s;

  // function call to get the ans of length of longest substring without repeating characters.
  cout<<soln.lengthOfLongestSubstring(s)<<endl;

  return 0;
}
