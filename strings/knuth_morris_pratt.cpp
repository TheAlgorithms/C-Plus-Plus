/*
    The Knuth-Morris-Pratt Algorithm for finding a pattern within a piece of text
    with complexity O(n + m)
    1) Preprocess pattern to identify any suffixes that are identical to prefixes
        This tells us where to continue from if we get a mismatch between a character in our pattern
        and the text.
    2) Step through the text one character at a time and compare it to a character in the pattern
        updating our location within the pattern if necessary
*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;
vector<int> getFailureArray(string pattern){
    int pattern_length=pattern.size();
    vector<int>failure(pattern_length+1);
    failure[0]=-1;
    int j=-1;
    for(int i=0; i<pattern_length; i++){
        while(j!=-1&&pattern[j]!=pattern[i]){
            j=failure[j];
        }
        j++;
        failure[i+1]=j;
    }
    return failure;
}
bool kmp(string pattern,string text){
    int text_length=text.size(),pattern_length=pattern.size();
    vector<int>failure=getFailureArray(pattern);
    int k=0;
    for(int  j=0; j<text_length; j++){
        while(k!=-1&&pattern[k]!=text[j]){
            k=failure[k];
        }
        k++;
        if(k==pattern_length)return true;
    }
    return false;
}

int main()
{   
   
    string text="alskfjaldsabc1abc1abc12k23adsfabcabc";
    string pattern="abc1abc12l";
    if(kmp(pattern,text)==true){
        cout<<"Found"<<endl;
    }
    else{
        cout<<"Not Found"<<endl;
    }
    text="abcabc";
    pattern="bca";
    if(kmp(pattern,text)==true){
        cout<<"Found"<<endl;
    }
    else{
        cout<<"Not Found"<<endl;
    }
    return 0;
}

