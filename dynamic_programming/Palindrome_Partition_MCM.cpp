/* 
Given a string, a partitioning of the string is a palindrome partitioning 
if every substring of the partition is a palindrome. 
For example, 
“aba|b|bbabb|a|b|aba” is a palindrome partitioning
of “ababbbabbababa”.
Determine the fewest cuts needed for a palindrome
partitioning of a given string. For example, minimum of 3 cuts are needed 
for “ababbbabbababa”.
The three cuts are “a|babbbab|b|ababa”. If a string
is a palindrome, then minimum 0 cuts are needed. If a string of length n 
containing all different characters, then minimum n-1 cuts are needed.

*/

#include <bits/stdc++.h>
using namespace std;

int dp[1001][1001];
int isPalindrome(string s,int i,int j){
    string temp="";
    
    for(int k=i;k<=j;k++){
        temp+=s[k];
    }
    //cout<<temp<<endl;
    int len1=0,len2=temp.length()-1;
    
    while(len1<len2){
        if(temp[len1++]!=temp[len2--]){
            return 0;
        }
    }
    return 1;
}

int PalindromePartition(string s,int i,int j){
    if(i>=j)return 0;
    if(isPalindrome(s,i,j)==1)return 0;
    
    if(dp[i][j]!=-1)return dp[i][j];
    int mn=INT_MAX;
    for(int k=i;k<=j-1;k++){
        int temp=1+PalindromePartition(s,i,k)+PalindromePartition(s,k+1,j);
        mn=min(mn,temp);
        
    }
    return dp[i][j]=mn;
    
}

int main() {
    memset(dp,-1,sizeof(dp));
  string str;
  cin>>str;
  int l=str.length();
  
  /*
Test Cases:
Input : str = “week”
Output : 2
We need to make minimum 2 cuts, i.e., “g ee k”

Input : str = “aaaa”
Output : 0
The string is already a palindrome.

Input : str = “abcde”
Output : 4 
*/
  
 cout<<PalindromePartition(str,0,l-1);
  
 return 0;
}
