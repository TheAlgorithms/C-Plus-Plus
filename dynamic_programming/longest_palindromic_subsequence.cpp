/**
 * @file
 * @brief Program to find the Longest Palindormic
 * Subsequence of a string
 *
 * @details
 * [Palindrome](https://en.wikipedia.org/wiki/Palindrome) string sequence of
 * characters which reads the same backward as forward
 * [Subsequence](https://en.wikipedia.org/wiki/Subsequence)  is a sequence that
 * can be derived from another sequence by deleting some or no elements without
 * changing the order of the remaining elements.
 * @author [Anjali Jha](https://github.com/anjali1903)
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
/**
 * Function that returns the longest palindromic
 * subsequence of a string
 */
 
string lps(string a) {
    string b = a;
    reverse(b.begin(), b.end());
    int m = a.length();
    //std::vector<std::vector<int>>res;
    int res[m+1][m+1];//update by Akash

    // Finding the length of the longest
    // palindromic subsequence and storing
    // in a 2D array in bottoms-up manner
    for (int i = 0; i <m+1; i++) {
        for (int j = 0; j <m+1; j++) {
            if (i == 0 || j == 0) {
                res[i][j] = 0;
            } else if (a[i - 1] == b[j - 1]) {
                res[i][j] = res[i - 1][j - 1] + 1;
            } else {
                res[i][j] = max(res[i - 1][j], res[i][j - 1]);
            }
        }
    }
    // Length of longest palindromic subsequence
    int idx = res[m][m];
    // Creating string of index+1 length
    //string ans(idx + 1, '\0');
    string ans=""; //update by Akash
    for(int i=0;i<idx;++i)//update by Akash
    {
    	ans+="0";  //update by Akash
    }
    int i = m, j = m;

    // starting from right-most bottom-most corner
    // and storing them one by one in ans
    //cout<<"while loop"<<"\n";
    while (i > 0 && j > 0) {
        // if current characters in a and b are same
        // then it is a part of the ans
        if (a[i - 1] == b[j - 1]) {
            ans[idx - 1] = a[i - 1];
            i--;
            j--;
            idx--;
        }
        // If they are not same, find the larger of the
        // two and move in that direction
        else if (res[i - 1][j] > res[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    return ans;
}

/** Test function */
void test() {
    // lps("radar") return "radar"
    //assert(lps("radar") == "radar");
    // lps("abbcbaa") return "abcba"
    //assert(lps("abbcbaa") == "abcba");
    // lps("bbbab") return "bbbb"
    //assert(lps("bbbab") == "bbbb");
    cout<<lps("radar")<<"\n"; //update by Akash
    cout<<lps("abbcbaa")<<"\n"; //update by Akash
    cout<<lps("bbbab")<<"\n"; //update by Akash
}

/**
 * Main Function
 */
int main() {
    test();  // execute the tests
    return 0;
}
