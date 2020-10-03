// CPP program to generate power set in 
// lexicographic order. 
#include <bits/stdc++.h> 
using namespace std; 
  
// str : Stores input string 
// n : Length of str. 
// curr : Stores current permutation 
// index : Index in current permutation, curr 
void permuteRec(string str, int n, 
                int index = -1, string curr = "") 
{ 
    // base case 
    if (index == n) 
        return; 
  
    cout << curr << "\n"; 
    for (int i = index + 1; i < n; i++) { 
  
        curr += str[i]; 
        permuteRec(str, n, i, curr); 
  
        // backtracking 
        curr = curr.erase(curr.size() - 1); 
    } 
    return; 
} 
  
// Generates power set in lexicographic 
// order. 
void powerSet(string str) 
{ 
    sort(str.begin(), str.end()); 
    permuteRec(str, str.size()); 
} 
  
// Driver code 
int main() 
{ 
    string str = "gaurav"; 
    powerSet(str); 
    return 0; 
} 