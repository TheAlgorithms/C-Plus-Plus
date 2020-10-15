// C++ program for implementation of KMP pattern searching
#include <iostream>   
#include <string>
#include <cstdio>
#include <cstdlib>
#include <array>

//Array to store longest prefix substring using KMP algorithm  
std::array<int,10000> lps;
  
// Prints occurrences of txt[] in pat[] 
void KMPSearch(std::string text, std::string pattern) 
{ 
    int M = pattern.length(); 
    int N = text.length(); 
  
    int i = 0; // index for text[] 
    int j = 0; // index for pattern[] 
    while (i < N) { 
        if (pattern[j] == text[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) { 
            std::cout << "Found pattern at index " << (i - j); 
            j = lps[j - 1]; 
        } 
  
        // mismatch after j matches 
        else if (i < N && pattern[j] != text[i]) { 
            // Do not match lps[0..lps[j-1]] characters, 
            // they will match anyway 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    } 
} 
 
// Driver program to test above function 
int main() 
{ 
    std::string text, pattern;
    //Input the string separated with pattern
    std::cin >> text >> pattern;

    //KMP Algorithm
    int len = 0; 
  
    lps[0] = 0; // lps[0] is always 0 
    int M = pattern.length();
    // the loop calculates lps[i] for i = 1 to M-1 
    int i = 1; 
    while (i < M) { 
        if (pattern[i] == pattern[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else // (pat[i] != pat[len]) 
        { 
            // This is tricky. Consider the example. 
            // AAACAAAA and i = 7. The idea is similar 
            // to search step. 
            if (len != 0) { 
                len = lps[len - 1]; 
  
                // Also, note that we do not increment 
                // i here 
            } 
            else // if (len == 0) 
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
    KMPSearch(text, pattern); 
    return 0; 
} 

