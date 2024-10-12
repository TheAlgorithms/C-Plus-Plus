//check if 2 strings are anagram of each other 

#include<bits/stdc++.h>
using namespace std;

int main(){
    string result1 = "mug";
    string result2 = "gum"; 
    sort(result1.begin(), result1.end());
    sort(result2.begin(), result2.end());
    if(result1 == result2){
        cout<<"Both strings are Anagrams"<<endl;
    } else {
        cout<<"Strings are not Anagrams"<<endl;
    }
    return 0;
}