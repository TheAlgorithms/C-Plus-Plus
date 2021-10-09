#include<iostream>
using namespace std;

/*
    1. A faster way to check if a string has only unique characters or not using hashmaps.
    2. Worst case complexity O(string size).
*/

bool checkUnique(string s) {

    int* hash = new int[26]{};
    // This hash array stores the no. of instances of a character in the string.

    for (int i = 0; i < s.size(); i++) {
        // We should also change the case of all the alphabets to either lower or upper.
        s[i] = tolower(s[i]);
        hash[s[i] - 'a']++;
    }

    // If instantes of a character are more than 1 than the string is no longer of unique characters and we return false from out function.
    for (int i = 0; i < 26; i++) {
        if (hash[i] > 1) return false;
    }

    // If instances of characters are less than or equal to 1 (0 or 1) then we can say the string consists of unique characters and hence return true.
    return true;

}

int main() {

    string s = "Ebola";

    if (checkUnique(s))
        cout << "This string consists of Uniques characters." << endl;
    else
        cout << "This string has mulitple instances of character(s)." << endl;

    return 0;

}
