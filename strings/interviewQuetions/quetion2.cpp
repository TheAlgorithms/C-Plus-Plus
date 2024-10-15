//count number of vowels,consonants and spaces in a string 
#include<bits/stdc++.h>
using namespace std;

int main(){
    string testCase = "Abhiraj Tiwari";  
    int vowels = 0, consonants = 0, spaces = 0;
    unordered_map<char, bool> alphabets = {{'a', true}, {'e', true}, {'i', true}, {'o', true}, {'u', true}, {'A', true}, {'E', true}, {'I', true}, {'O', true}, {'U', true}};
    for(int i=0;i<testCase.size();i++){
        if(alphabets.find(testCase[i]) != alphabets.end()){
            vowels++;
        } 
        else if(testCase[i] == ' '){
            spaces++;
        } 
        else{
            consonants++;
        }  
    }
       cout<<vowels<<endl;
        cout<<consonants<<endl;
        cout<<spaces<<endl;

        return 0;
}