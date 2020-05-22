/*
 *  This is implementation of Rabin Karp Algorithm. 
 *  
 *  Function : rabin_karp 
 *                      INPUT: 1. str -> your String 
 *                             2. pat -> your Pattern 
 *                             
 *                      OUTPUT:   index of first occurrence of pattern , if pattern is found 
 *                               -1 , if pattern not found 
 *
 */
#include<iostream>
#include<string>
#include<cassert>
#include<cmath>
using namespace std;

#define PRIME 5

long long create_hash(string s , int n){
    long long result = 0;
    for(int i=0; i<n; ++i){
        result+=(long long)(s[i] * (long long)pow(PRIME , i));
    }
    return result;
}

long long recalculate_hash(string s , int old_index , int new_index , long long old_hash , int patLength){
    long long new_hash = old_hash - s[old_index];
    new_hash/=PRIME;
    new_hash+=(long long)(s[new_index]*(long long)pow(PRIME,patLength-1));
    return new_hash;
}

bool check_if_equal(string str1 , string str2 , int start1 , int end1 , int start2 , int end2){
    if(end1-start1 != end2-start2){
        return false;
    }
    while(start1<=end1 and start2<=end2){
        if(str1[start1]!=str2[start2]){
            return false;
        }
        start1++;
        start2++;
    }
    return true;
}

int rabin_karp(const string &str , const string& pat){
    long long pat_hash = create_hash(pat , pat.size());
    long long str_hash = create_hash(str , pat.size());
    for(int i=0;  i<=str.size()-pat.size(); ++i){
        if(pat_hash==str_hash and check_if_equal(str , pat , i , i+pat.size()-1 , 0 , pat.size()-1)){
                return i;
        }
        if(i<str.size()-pat.size()){
            str_hash = recalculate_hash(str , i , i+pat.size() , str_hash , pat.size()); 
        }
    }
    return -1; // return -1 if given pattern not found 
}

int main(void){
    assert( rabin_karp("helloWorld","world")    == -1);
    assert( rabin_karp("helloWorld","World")    ==  5);
    assert( rabin_karp("this_is_c++" , "c++")   ==  8);
    assert( rabin_karp("happy_coding", "happy") ==  0);
    return 0;
}
