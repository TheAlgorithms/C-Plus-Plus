// Maximum length palindromic string
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// function to calculate palindromic length with respect to position character at i
int longestPalindrome(int center, int i, string str){
    if(center-i==-1 || center+i==str.length() || str[center-i]!=str[center+i]){
        return 0;
    }
    if(str[center-i]=='|'){
        return longestPalindrome(center, i+1, str);
    }
    return 1+longestPalindrome(center, i+1, str);
}

// longest palindromic string
string Manacher(string str){
    int length , max_length = 0, start;

    // new string, if str = "aba" than new_string = "a|b|a"
    string new_string  = "";
    // output string to be return
    string output = "";

    // add '|' after every character
    for(int i=0; i<str.length()-1; i++){
        new_string.push_back(str[i]);
        new_string.push_back('|');
    }
    new_string.push_back(str[str.length()-1]);

    // for each character in new_string find corresponding palindromic string
    for(int i=0; i<new_string.length(); i++){

        // find length from i as center but not include i character itself
        length = longestPalindrome(i, 1, new_string);

        // new max_length palindrome
        if(max_length<length){
            max_length = length;
            start = i;
        }
    }

    // create new string that to be returned
    for(int i=start - max_length*2; i<start + max_length*2 + 1; i++){
        if(new_string[i] != '|')
            output.push_back(new_string[i]);
    }

    return output;
}

int main(){
    string input;
    cin>>input;
    cout<<Manacher(input)<<endl;
    return 0;
}
