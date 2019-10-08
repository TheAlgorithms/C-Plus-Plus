#include <bits/stdc++.h> 
using namespace std; 
  
// Print the first n term, say 10 of Golomb Sequence 

void printGolomb(int n) 
{ 
    int dp[n + 1]; 
  
    // base cases 
    dp[1] = 1; 
    cout << dp[1] << " "; 
  
    // Finding and printing first  
    // n terms of Golomb Sequence. 
    for (int i = 2; i <= n; i++)  
    { 
        dp[i] = 1 + dp[i - dp[dp[i - 1]]]; 
        cout << dp[i] << " "; 
    } 
} 


// Driver Code 
int main() 
{ 
    int n = 10; 
  
    printGolomb(n); 
    return 0; 
}
