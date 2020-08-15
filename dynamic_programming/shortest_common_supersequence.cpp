// Shortest common supersequence - Dynamic Programming

/*
Definition: The Shortest Common Supersequence (SCS) is a string Z which is the shortest supersequence of two given strings
X and Y (which may not be continuously present in Z, but order must be maintained).

example 1: 
X: 'ABCXYZ', Y: 'ABZ' then Z will be 'ABCXYZ' (y is not continuous but in order)

example 2:
X: 'AGGTAB', Y: 'GXTXAYB' then Z will be 'AGGXTXAYB'
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string scs(string str1, string str2, int n1, int n2) {

    // creating lookup table
    vector <vector <int>> lookup(n1 + 1, vector <int> (n2 + 1, 0));
      
    for(int i=1; i <= n1; i++) {
        for(int j=1; j <= n2; j++) {
            if(str1[i-1] == str2[j-1]) {
                lookup[i][j] = lookup[i-1][j-1] + 1;
            }
            else {
                lookup[i][j] = max(lookup[i-1][j], lookup[i][j-1]);
            }
        }
    }

    // making supersequence
    int i=n1;
    int j=n2;
    string s;
      
    while(i>0 && j>0) {
            
        if(str1[i-1] == str2[j-1]) {
            s.push_back(str1[i-1]);
            i--;
            j--;
        }
        else {
            if(lookup[i-1][j] > lookup[i][j-1]) {
                s.push_back(str1[i-1]);
                i--;
            }
            else {
                s.push_back(str2[j-1]);
                j--;
            }
        }
    }

    // copying remaining elements
    while(i > 0) {
        s.push_back(str1[i-1]);
        i--;
    }
    while(j > 0) {
        s.push_back(str2[j-1]);
        j--;
    }
      
    reverse(s.begin(), s.end());
    return s;
}

int main() {

    string s1, s2;
    cin >> s1;
    cin >> s2;

    int n1 = s1.length();
    int n2 = s2.length();
    string ans;

    ans = scs(s1, s2, n1, n2);
    cout << ans;
    return 0;
}
