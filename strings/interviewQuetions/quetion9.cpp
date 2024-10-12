//check if 2 strings match where one string contains a wildcard character
#include<bits/stdc++.h>
using namespace std;

int main(){ 
        unordered_map<char, bool> alphabets = {{'*', true}, {'@', true}, {'#', true}, {'$', true}};
string result1 = "Abhiraj";
string result2 = "@Abhiraj";
     for(int i=0;i<result1.size();i++){
        for(int j=0;j<result2.size();j++){
            if(alphabets.find(result1[i]) != alphabets.end() || result1[i] == result2[j]){
                cout<<"Both strings are equal";
            }
        }
     }
     return 0;
}