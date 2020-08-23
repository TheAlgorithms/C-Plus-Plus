/**
 * @file Word Break 
 * 
 * @details
 * Given a valid sentence without any spaces between the words and 
 * a dictionary of valid English words, find all possible ways to 
 * break the sentence in individual dictionary words.
 *
 * @author [Anushka Verma](https://github.com/verma-anushka)
 */

#include <bits/stdc++.h>
using namespace std;

/**
 * Utility function
 */
void wordbreak(string s, vector<string>& dict, int i, string ans) {
    
    string word=s.substr(0, i+1);
    int ws=s.size();

    // search for word in the dictionary
    if(find(dict.begin(), dict.end(), word) != dict.end()) {

        if(i<ws-1)
            // recursive call
            wordbreak(s.substr(i+1, ws-i), dict, 0, ans+word+" ");
        else
            // print output
            cout << (ans+word) << endl;
    }
    if(i<ws-1)
        wordbreak(s, dict, i+1, ans);

}

/**
 * Main function
 */
int main() {

    vector<string> dict = { "mobile","samsung","sam","sung", 
                            "man","mango","icecream","and", 
                            "go","i","like","ice","cream" };
    string s = "ilikesamsung";
    wordbreak(s, dict, 0, "");
    return 0;
}

