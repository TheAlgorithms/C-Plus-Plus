/* Copyright [2020] <Kalyani Kumari> */


#include<iostream>
#include<assert.h>
using namespace std;

/* Fuction to match the pattern and string
*/

bool pattern_matching(string str, string pattern, int n, int m) {
bool lookup[n+1][m+1];  // DP lookup table
lookup[0][0] = true;

/* handle empty string case */
for(int i = 1; i <= m; i++)
if(pattern[i-1] == '*')
lookup[0][i] = lookup[0][i-1];

/* Build lookup matrix in bottom-up manner */
for(int i = 1; i <= n; i++) {
for(int j = 1; j <= m; j++) {
if (pattern[j-1] == '*')
lookup[i][j] = lookup[i-1][j] || lookup[i][j-1];
else if (pattern[j-1] == '?' || str[i-1] == pattern[j-1])
lookup[i][j] = lookup[i-1][j-1];
}
}
return lookup[n][m];   // return the ans
}

static void test() {
assert(pattern_matching("xyxxzzy", "x**y", 7, 4) == true);
assert(pattern_matching("xyxxzzy", "x**x", 7, 4) == true);
assert(pattern_matching("xyxxzzy", "x**?", 7, 4) == true);
}

int main() {
test();
string str;
cout << "Enter string:";
cin >> str;              // input string
string pattern;
cout << "Enter pattern:";
cin >> pattern;          // input pattern

if (pattern_matching(str, pattern,
str.length(), pattern.length()))    // function call
cout << "Match\n";
else
cout << "No Match\n";
return 0;
}
