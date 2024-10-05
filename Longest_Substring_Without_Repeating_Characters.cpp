/* Leetcode problem 
Author : Ashish Kumar Sahoo
3. Longest_Substring_Without_Repeating_Characters
Intiuation :
  Intuition is strightforward and simple, we track the frequencey and as we know we can't use string to track longest substring without repeating characters, as poping a char from front of string is not in O(1) which could be optimized by deque approch.
Approch :
    1) At first we initialize a unordered_map to track the frequncy and then.
    2) We initialize deque for pushing the characters and if temp > res we update our res deque to temp as we need longest substring here.
    3) And while loop is used to reduce the frequency from front doing i++ and removing charecters from temp deque as we no longer need them.
    4) return res.size() as we only need size not string.
Time Complexity :
  O(N)
Space Complexity :
  O(N)
I hope this helps to understand.
Thank you!!
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size()==1) return 1;

        unordered_map<char,int>m;
        int n = s.length();

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
