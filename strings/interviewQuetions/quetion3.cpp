//remove all vowels and spaces from string 
#include<bits/stdc++.h>
using namespace std;

int main(){
    string result = "This is a sample string with vowels.";
    unordered_map<char, bool> alphabets = {{'a', true}, {'e', true}, {'i', true}, {'o', true}, {'u', true}, {'A', true}, {'E', true}, {'I', true}, {'O', true}, {'U', true}};
    for(int i=0; i<result.size();){
        if(alphabets.find(result[i]) != alphabets.end()){
            result.erase(i, 1);
        }  
        else if(result[i] == ' '){
            result.erase(i,1);
        }
         else {
            i++;
        }
    } 
    cout << result << endl;
    return 0;
}