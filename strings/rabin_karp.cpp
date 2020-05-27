/*
 * file name : rabin_karp.cpp
 * author    : Amit Kumar 
 * Copyright : 2020 , Amit Kumar 
 * version   : 1.0
 */
#include<cassert>
#include<cmath>
#include<iostream>
#include<string>

using std::string;
using std::pow;

#define PRIME 5

int64_t create_hash(string s , int n) {
    int64_t result = 0;
    for ( int i = 0; i < n; ++i ) {
        result += (int64_t)(s[i] * (int64_t)pow(PRIME , i));
    }
    return result;
}

int64_t recalculate_hash(string s , int old_index ,
        int new_index , int64_t old_hash , int patLength) {
    int64_t new_hash = old_hash - s[old_index];
    new_hash /= PRIME;
    new_hash += (int64_t)(s[new_index]*(int64_t)pow(PRIME, patLength-1));
    return new_hash;
}

bool check_if_equal(string str1 , string str2 ,
                    int start1 , int end1 ,
                    int start2 , int end2) {
    if (end1-start1 != end2-start2) {
        return false;
    }
    while (start1 <= end1 && start2 <= end2) {
        if (str1[start1] != str2[start2]) {
            return false;
        }
        start1++;
        start2++;
    }
    return true;
}

/*
 *  @description : search pattern in the given text 
 *  @param : string str
 *  @param : string pat
 *  @return index of first occurrence of pattern or -1 if pattern not found
 */

int rabin_karp(const string &str , const string& pat) {
    int64_t pat_hash = create_hash(pat , pat.size());
    int64_t str_hash = create_hash(str , pat.size());
    for (int i=0;  i <= str.size()-pat.size(); ++i) {
        if (pat_hash == str_hash &&
            check_if_equal(str , pat , i , i+pat.size()-1 , 0 , pat.size()-1)) {
                return i;
        }
        if (i < str.size()-pat.size()) {
            str_hash =
                recalculate_hash(str, i, i+pat.size(), str_hash, pat.size());
        }
    }
    return -1;  // return -1 if given pattern not found
}

int main(void) {
    assert(rabin_karp("helloWorld", "world")    == -1);
    assert(rabin_karp("helloWorld", "World")    ==  5);
    assert(rabin_karp("this_is_c++" , "c++")   ==  8);
    assert(rabin_karp("happy_coding", "happy") ==  0);
    return 0;
}
